let socket = io.connect('http://' + document.domain + ':' + location.port);
socket.on('reload', function() {
   window.location.reload();
});