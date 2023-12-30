from flask import Flask, render_template
import threading
import socket
import datetime

app = Flask(__name__)
images = []

@app.route('/', methods=['GET'])
def home():
 return render_template('home.html', images=images)

def recvall(sock):
   BUFF_SIZE = 4096 # 4 KiB
   fragments = []
   data = b''
   while True:
      chunk = sock.recv(BUFF_SIZE)
      if not chunk:
         break
      fragments.append(chunk)
      data = b''.join(fragments)
   return data

def receive_image(conn):
   data = recvall(conn)
   delimiter = data.find(b'\n\n\n')
   print(delimiter)
   if delimiter != -1:
      image_data = data[:delimiter]
      text_data = data[delimiter+1:]
      print(text_data)
      images.append({'image': image_data, 'text': text_data.decode("utf-8"), 'timestamp': datetime.datetime.now().strftime("%H:%M:%S")})
      print(images)

def start_receiving_images():
 with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
   s.bind(('0.0.0.0', 5000))
   s.listen()
   while True:
       conn, addr = s.accept()
       print('Connected by', addr)
       threading.Thread(target=receive_image, args=(conn,)).start()

if __name__ == "__main__":
 threading.Thread(target=start_receiving_images).start()
 app.run(host='localhost', port=5005)
