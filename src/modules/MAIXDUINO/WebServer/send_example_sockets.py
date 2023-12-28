import network
import time
from machine import UART
from fpioa_manager import fm
from Maix import GPIO
import socket

# Configurez les informations de votre réseau WiFi
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

# Connectez-vous au WiFi

# Connectez-vous à votre réseau Wi-Fi
esp.connect(WIFI_SSID, WIFI_PASS)  # Remplacez "SSID" et "pwd" par votre SSID et mot de passe

while not esp.isconnected():
    time.sleep(1)

print("Adresse IP:", esp.ifconfig()[0])
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("192.168.137.1", 5000))
s.send("Hello \n")
s.send("COucou \n")
s.close()
