from flask import Flask, render_template, send_from_directory, request, redirect, url_for
import threading
import socket
from flask_socketio import SocketIO
import sqlite3
import datetime
import asyncio
import websockets

app = Flask(__name__)
images = []
app.config["TEMPLATES_AUTO_RELOAD"] = True

connImages = sqlite3.connect('images.db')  # Create a new SQLite database
cImages = connImages.cursor()
connHistory = sqlite3.connect('history.db')  # Create a new SQLite database
cHistory = connHistory.cursor()

cImages.execute("DROP TABLE images")
cImages.execute('''CREATE TABLE images (id INTEGER PRIMARY KEY, timestamp TEXT, text TEXT, path TEXT)''')

connImages.commit()
connImages.close()


socketio = SocketIO(app)


@app.route('/', methods=['GET'])
def home():
    conn = sqlite3.connect('images.db')
    c = conn.cursor()
    images = c.execute('SELECT * FROM images ORDER BY id DESC').fetchall()
    conn.close()
    return render_template('home.html', images=images)


@app.route('/history', methods=['GET'])
def history():
    conn = sqlite3.connect('history.db')
    c = conn.cursor()
    history = c.execute('SELECT * FROM history ORDER BY id DESC').fetchall()
    conn.close()
    return render_template('history.html', history=history)


@app.route('/manage', methods=['GET'])
def manage():
    return render_template('manage.html')


@app.route('/image/<path>')
def serve_image(path):
    return send_from_directory('static/images', path)


@app.route("/manage_form", methods=["POST"])
def manage_form():
    data = request.form
    process_data(data)
    return redirect(url_for("history"))


def process_data(d):
    for c, v in d.items():
        if c == "history-all":
            suppress_all_history()
        elif c == "history-number":
            if "-" in v:
                l = v.split("-")
            else:
                l = [int(v) for i in range(2)]
            suppress_history_alerts(*l)


def suppress_history_alerts(start, end):
    connHistory = sqlite3.connect('history.db')
    cHistory = connHistory.cursor()
    cHistory.execute(f"DELETE FROM history WHERE id >={start} AND id<={end} ")
    connHistory.commit()
    connHistory.close()


def suppress_all_history():
    connHistory = sqlite3.connect('history.db')
    cHistory = connHistory.cursor()
    cHistory.execute("DELETE FROM history")
    connHistory.commit()
    connHistory.close()


def receive_data(conn):
    data = ''
    while True:
        print(data)
        try:
            chunk = conn.recv(1024)
            if not chunk:
                break
            data += chunk.decode("utf-8")
            lines = data.split('\n')
            for line in lines:
                if len(line) != 0:
                    global path
                    if line == "U":
                        path = "unknown.png"
                        text = "Unknown face. Danger !"
                    else:
                        line = int(line) // 2 + 1
                        print(line)
                        path = f"{line}.JPG"
                        text = "Good face ! Go ahead."
                    timestamp = datetime.datetime.now().strftime("%H:%M:%S")

                    connImages = sqlite3.connect('images.db')
                    cImages = connImages.cursor()
                    cImages.execute("INSERT INTO images VALUES (NULL, ?, ?, ?)", (timestamp, text, path))
                    connImages.commit()
                    connImages.close()

                    connHistory = sqlite3.connect('history.db')
                    cHistory = connHistory.cursor()
                    formatted_date = datetime.datetime.now().strftime("%d/%m/%Y")
                    cHistory.execute("INSERT INTO history VALUES (NULL, ?, ?, ?, ?)",
                                     (formatted_date, timestamp, text, path))

                    socketio.emit('reload', {'message': 'New content added'})
                    print("Content added !")
                    connHistory.commit()
                    connHistory.close()
        except Exception as e:
            print(f"Error: {e}")
            break


def start_receiving_images():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    s.bind(('0.0.0.0', 5000))
    s.listen()
    while True:
        conn, addr = s.accept()
        print('Connected by', addr)
        threading.Thread(target=receive_data, args=(conn,)).start()
    s.close()


if __name__ == "__main__":
    threading.Thread(target=start_receiving_images).start()
    """threading.Thread(target=generate_random).start()
    random_content()"""
    app.run(host='localhost', port=5005, debug=True)
