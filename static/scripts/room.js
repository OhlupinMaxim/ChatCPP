function main() {
    if ("WebSocket" in window) {

        const getRoomId = new XMLHttpRequest();
        getRoomId.open("GET", "http://localhost:8080/api/room/", false);
        getRoomId.send();

        console.log(getRoomId.status);

        let inputSend = document.getElementById("chat-sendArea");
        let button = document.querySelector("#chat-sendButton");

        if (getRoomId.status === 200) {
            let json = JSON.parse(getRoomId.responseText);
            const room_id = json["RESPONSE"]["ROOM_ID"];

            const ws = new WebSocket(`ws://localhost:8080/ws/?room_id=${room_id}`);

            let chatArea = document.querySelector("#chat-area");

            ws.onopen = function () {
                console.log("WebSocket Opened");
            };

            ws.onclose = function () {
                console.log("WebSocket closed.");
            };

            ws.onmessage = function (evt) {
                const msg = evt.data;
                chatArea.value += msg;
            };

            function sendMessage() {
                ws.send(inputSend.value);
            }

            button.addEventListener('click', sendMessage);

            let addedHref = document.querySelector("#chat-addHref");
            addedHref.href = `http://localhost:8080/room/add/?room_id=${room_id}`;
            addedHref.textContent = `http://localhost:8080/room/add/?room_id=${room_id}`;

        } else {
            console.log("Get Room Id Failed");
        }

    } else {
        alert("This browser does not support WebSockets.");
    }
}