from random import randint, choice
import sqlite3

texts = ["Valid face, go ahead !", "Invalid face, danger!"]

def generate_history_line():
    d = randint(1, 30)
    m = randint(1, 12)
    y = 2024
    date = f"{d}/{m}/{y}"
    hour = randint(0, 23)
    minutes = randint(0, 59)
    seconds = randint(0, 59)
    timestamp = f"{hour}:{minutes}:{seconds}"
    text = choice(texts)
    path = str(randint(1, 2))+".JPG"
    return date, timestamp, text, path

def generate_history():
   connHistory = sqlite3.connect('history.db')
   cHistory = connHistory.cursor()
   for i in range(randint(5, 15)):
      print(i)
      date, timestamp, text, path = generate_history_line()
      cHistory.execute("INSERT INTO history VALUES (NULL, ?, ?, ?, ?)", (date, timestamp, text, path))
      connHistory.commit()
   connHistory.close()

def clean_history():
   connHistory = sqlite3.connect('history.db')
   cHistory = connHistory.cursor()
   cHistory.execute("DELETE FROM history")
   connHistory.commit()
   connHistory.close()

clean_history()
generate_history()