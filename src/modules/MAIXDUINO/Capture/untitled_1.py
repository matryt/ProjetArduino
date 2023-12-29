### Imports

import sensor
import image
import lcd
import KPU as kpu
import time
from Maix import FPIOA, GPIO
import gc
from fpioa_manager import fm
from board import board_info
import utime
from machine import UART
import network
import socket

### Variables globales

task_fd = kpu.load(0x300000)
task_ld = kpu.load(0x400000)
task_fe = kpu.load(0x500000)

clock = time.clock()

fm.register(board_info.BOOT_KEY, fm.fpioa.GPIOHS0)
fm.register(board_info.PIN2, fm.fpioa.UART1_TX)
fm.register(board_info.PIN3, fm.fpioa.UART1_RX)
key_gpio = GPIO(GPIO.GPIOHS0, GPIO.IN)
start_processing = False

BOUNCE_PROTECTION = 50

record_ftr = []
record_ftrs = []
names = ['Mr.1', 'Mr.2', 'Mr.3', 'Mr.4', 'Mr.5',
         'Mr.6', 'Mr.7', 'Mr.8', 'Mr.9', 'Mr.10']

anchor = (1.889, 2.5245, 2.9465, 3.94056, 3.99987, 5.3658, 5.155437,
          6.92275, 6.718375, 9.01025)  # anchor for face detect
dst_point = [(44, 59), (84, 59), (64, 82), (47, 105),
             (81, 105)]  # standard face key point position
a = kpu.init_yolo2(task_fd, 0.5, 0.3, 5, anchor)
img_lcd = image.Image()
img_face = image.Image(size=(128, 128))
a = img_face.pix_to_ai()
ACCURACY = 80

WIFI_SSID = "DESKTOP-M5RI8E3"
WIFI_PASS = "OrdiMat2005!"
fm.register(25,fm.fpioa.GPIOHS10)#cs
fm.register(8,fm.fpioa.GPIOHS11)#rst
fm.register(9,fm.fpioa.GPIOHS12)#rdy
print("Use Hareware SPI for other maixduino")
fm.register(28,fm.fpioa.SPI1_D0, force=True)#mosi
fm.register(26,fm.fpioa.SPI1_D1, force=True)#miso
fm.register(27,fm.fpioa.SPI1_SCLK, force=True)#sclk
esp = network.ESP32_SPI(cs=fm.fpioa.GPIOHS10, rst=fm.fpioa.GPIOHS11, rdy=fm.fpioa.GPIOHS12, spi=1)

### Fonctions

def set_key_state(*_):
    global start_processing
    start_processing = True
    utime.sleep_ms(BOUNCE_PROTECTION)

def init_all():
    lcd.init()
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)
    sensor.set_hmirror(1)
    sensor.set_vflip(1)
    sensor.run(1)
    gateway = wifi_connection()
    key_gpio.irq(set_key_state, GPIO.IRQ_RISING, GPIO.WAKEUP_NOT_SUPPORT)
    return gateway


def points_ref(i, plist):
    return ((i.x() + int(plist[0] * i.w() - 10), i.y() + int(plist[1] * i.h())),
    (i.x() + int(plist[2] * i.w()), i.y() + int(plist[3] * i.h())),
    (i.x() + int(plist[4] * i.w()), i.y() + int(plist[5] * i.h())),
    (i.x() + int(plist[6] * i.w()), i.y() + int(plist[7] * i.h())),
    (i.x() + int(plist[8] * i.w()), i.y() + int(plist[9] * i.h())))

def draw_refs(a):
    a = img.draw_circle(le[0], le[1], 4)
    a = img.draw_circle(re[0], re[1], 4)
    a = img.draw_circle(nose[0], nose[1], 4)
    a = img.draw_circle(lm[0], lm[1], 4)
    a = img.draw_circle(rm[0], rm[1], 4)
    return a

def process_face():
    global start_processing
    if start_processing:
        record_ftr = feature
        record_ftrs.append(record_ftr)
        start_processing = False

def display_result(a, max_score):
    if int(time.time()) % 10 == 0:
        if max_score > ACCURACY:
            a = img.draw_string(i.x(), i.y(), ("%s :%2.1f" % (
                    names[index], max_score)), color=(0, 255, 0), scale=2)
            print("Good face")
        else:
            a = img.draw_string(i.x(), i.y(), ("X :%2.1f" % (
                    max_score)), color=(255, 0, 0), scale=2)
            print("Sending image...")
        send_image_via_socket(a, gateway)
    return a

def wifi_connection():
    esp.connect(WIFI_SSID, WIFI_PASS)
    while not esp.isconnected():
        print("Connecting to WiFi...")
        time.sleep(1)
    return esp.ifconfig()[2]

def send_image_via_socket(img, gateway):
    try:
       s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
       s.connect((gateway, 5000))
       img_jpeg = img.to_bytes(format='jpeg')
       s.write(img_jpeg)
       s.close()
    except Exception as e:
       pass

### Code principal

gateway = init_all()


while (1):
    img = sensor.snapshot()
    clock.tick()
    code = kpu.run_yolo2(task_fd, img)
    if code:
        for i in code:
            # Cut face and resize to 128x128
            a = img.draw_rectangle(i.rect())
            face_cut = img.cut(i.x(), i.y(), i.w(), i.h())
            face_cut_128 = face_cut.resize(128, 128)
            a = face_cut_128.pix_to_ai()
            # Landmark for face 5 points
            fmap = kpu.forward(task_ld, face_cut_128)
            plist = fmap[:]
            le, re, nose, lm, rm = points_ref(i, plist)
            a = draw_refs(a)
            # align face to standard position
            src_point = [le, re, nose, lm, rm]
            T = image.get_affine_transform(src_point, dst_point)
            a = image.warp_affine_ai(img, img_face, T)
            a = img_face.ai_to_pix()

            del (face_cut_128)
            # calculate face feature vector
            fmap = kpu.forward(task_fe, img_face)
            feature = kpu.face_encode(fmap[:])
            reg_flag = False
            scores = []
            process_face()
            for j in range(len(record_ftrs)):
                score = kpu.face_compare(record_ftrs[j], feature)
                scores.append(score)
            if len(scores) > 0:
                max_score = max(scores)
                index = scores.index(max_score)
                a = display_result(a, max_score)


            break

    a = lcd.display(img)
    gc.collect()
    # kpu.memtest()
