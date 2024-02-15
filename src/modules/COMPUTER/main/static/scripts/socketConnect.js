const socket = new WebSocket('ws://localhost:8765');

socket.addEventListener('open', function (event) {
    socket.send('Hello Server!');
});

socket.addEventListener('message', function (event) {
    const message = JSON.parse(event.data);
    if (message.action === 'reload') {
        console.log("Received reload request");
        window.location.reload();
    }
});
