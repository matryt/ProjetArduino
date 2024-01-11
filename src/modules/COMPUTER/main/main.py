from flask import Flask, render_template, send_from_directory
import threading
import socket
import datetime
import base64
from PIL import Image
import os
from random import choice, randint
from flask_socketio import SocketIO
import time
import redis
r = redis.Redis()

app = Flask(__name__)
images = []
app.config["TEMPLATES_AUTO_RELOAD"] = True

import sqlite3

conn = sqlite3.connect('images.db') # Create a new SQLite database
c = conn.cursor()

# Create a new table named 'images'
c.execute("DROP TABLE images")
c.execute('''CREATE TABLE images (id INTEGER PRIMARY KEY, timestamp TEXT, text TEXT, path TEXT)''')

conn.commit()

conn.close()


socketio = SocketIO(app)

@app.route('/', methods=['GET'])
def home():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    images = c.execute('SELECT * FROM images ORDER BY id DESC').fetchall()
    conn.close()
    return render_template('home.html', images=images)


@app.route('/image/<path>')
def serve_image(path):
    print(path)
    return send_from_directory('static', path)


def receive_data(conn):
    global path
    data = conn.recv(1024)
    data = data.decode("utf-8")
    if data == "U":
        path = "unknown.png"
        text = "Unknown face. Danger !"
    else:
        path = f"{data}.JPG"
        text = "Good face ! Go ahead."
    timestamp = datetime.datetime.now().strftime("%H:%M:%S")
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    c.execute("INSERT INTO images VALUES (NULL, ?, ?, ?)", (timestamp, text, path))
    conn.commit()
    print(c.execute('SELECT * FROM images ORDER BY id DESC').fetchall())
    c.close()
    socketio.emit('reload', {'message': 'New content added'})


def start_receiving_images():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind(('0.0.0.0', 5000))
        s.listen()
        while True:
            conn, addr = s.accept()
            print('Connected by', addr)
            threading.Thread(target=receive_data, args=(conn,)).start()


def random_content():
   global images
   images = ["unknown.png"] + [f"{i}.JPG" for i in range(1, 3)]
   image_filename = choice(images)
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
    threading.Thread(target=start_receiving_images).start()
    """threading.Thread(target=generate_random).start()
    random_content()"""
    app.run(host='localhost', port=5005, debug=True)
