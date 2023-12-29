import socket

# Créez un socket TCP/IP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Liez le socket à l'adresse et au port
server_address = ('0.0.0.0', 5000)
sock.bind(server_address)

# Écoutez les connexions entrantes
sock.listen(1)

while True:
   # Attendez une connexion
   print('En attente d\'une connexion')
   connection, client_address = sock.accept()

   try:
       print('Connexion de', client_address)
       total_data = b''
       # Réceptionnez les données en petites tranches et les imprimez
       while True:
           data = connection.recv(16)
           total_data += data
           if not data:
               break
   finally:
       # Nettoyez la connexion
       print(total_data)
       connection.close()