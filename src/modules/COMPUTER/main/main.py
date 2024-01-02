from flask import Flask, render_template, send_from_directory
import threading
import socket
import datetime
import base64
from PIL import Image
import io
import os
from random import choice, randint
#from flask_socketio import SocketIO
import time

app = Flask(__name__)
images = []
app.config["TEMPLATES_AUTO_RELOAD"] = True
#socketio = SocketIO(app)

@app.route('/', methods=['GET'])
def home():
   return render_template('home.html', images=images)

@app.route('/image')
def serve_image():
   return send_from_directory('static', "image.JPG")

def recvall(sock):
  BUFF_SIZE = 1024 # 4 KiB
  fragments = []
  data = b''
  while True:
     chunk = sock.recv(BUFF_SIZE)
     if not chunk:
        break
     fragments.append(chunk)
     data = b''.join(fragments)
  return data

"""def receive_image(conn):
  data = recvall(conn)
  delimiter = data.find(b'\n\n\n')
  if delimiter != -1:
     image_data = data[:delimiter]
     text_data = data[delimiter+3:]
     image_filename = 'image.png'
     image = Image.open(io.BytesIO(image_data))
     image.save(os.path.join('static', image_filename))
     images.append({'image': image_filename, 'text': text_data.decode("utf-8"), 'timestamp': datetime.datetime.now().strftime("%H:%M:%S")})"""

"""def start_receiving_images():
 with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
  s.bind(('0.0.0.0', 5000))
  s.listen()
  while True:
      conn, addr = s.accept()
      print('Connected by', addr)
      threading.Thread(target=receive_image, args=(conn,)).start()"""

def random_content():
   global images
   image_filename = "image.png"
   texts = ["Good face ! Go ahead.", "Incorrect face. Danger !"]
   text = choice(texts)
   timestamp = datetime.datetime.now().strftime("%H:%M:%S")
   images = [{"image" : image_filename, "text" : text, "timestamp" : timestamp}] + images

def generate_random():
   for i in range(5):
      time.sleep(1)
      random_content()
      #socketio.emit('reload', {'message': 'New content added'})
      print("Content added")

if __name__ == "__main__":
   #threading.Thread(target=start_receiving_images).start()
   threading.Thread(target=generate_random).start()
   random_content()
   app.run(host='localhost', port=5005, debug=True)