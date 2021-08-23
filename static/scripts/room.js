function main() {
    if ("WebSocket" in window) {
        const ws = new WebSocket("ws://localhost:8080/ws/chat");

        let chatArea = document.querySelector("");

        ws.onopen = function () {
            alert("WebSocket Opened");
        };

        ws.onclose = function () {
            alert("WebSocket closed.");
        };

        ws.onmessage = function (evt) {
            const msg = evt.data;
            chatArea.insertAdjacentText("afterbegin", msg);
        };


        function sendMessage() {
            ws.send(inputSend.textContent);
        }

        let inputSend = document.querySelector("#chat-sendArea");
        let button = document.querySelector("#chat-sendButton");

        button.addEventListener('click', sendMessage);


    } else {
        alert("This browser does not support WebSockets.");
    }
}