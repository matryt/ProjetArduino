let socket = io.connect(document.domain + ':' + location.port);
console.log(socket);

socket.on('connect', function(){
   console.log('Successfully connected!');
});
socket.on('reload', function(data) {
   console.log("Received reload request", data)
   window.location.reload();
});