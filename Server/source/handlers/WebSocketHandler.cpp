#include "include/handlers/WebSocketHandler.h"

WebSocketHandler::WebSocketHandler() {}

WebSocketHandler::~WebSocketHandler() = default;

void WebSocketHandler::SocketFunction(Poco::Net::WebSocket &ws,
                                      Poco::Net::HTTPServerResponse &response, Room &room) const {
    try {

        char buffer[8 * 1024];
        int flags;
        int n;
        do {
            // time gen
            std::unique_ptr<Poco::LocalDateTime> localTime(new Poco::LocalDateTime);
            std::unique_ptr<Poco::DateTimeFormatter> formatter(new Poco::DateTimeFormatter);
            auto time = formatter->format(localTime->timestamp(), "%Y.%n.%d - %H:%M:%S");

            // get Message
            n = ws.receiveFrame(buffer, sizeof(buffer), flags);

            // generate Message
            std::string buff_str(buffer);
            buff_str = time + "\t" + buff_str + "\n";
            char *msg = (char *) buff_str.c_str();

            // send All guest's and Me
            for (auto &x : room.connections) {
                x.second->sendFrame(msg, strlen(msg), Poco::Net::WebSocket::FRAME_TEXT);
            }
        } while (n > 0 && (flags & Poco::Net::WebSocket::FRAME_OP_BITMASK) != Poco::Net::WebSocket::FRAME_OP_CLOSE);
    }
    catch (Poco::Net::WebSocketException &exc) {
        switch (exc.code()) {
            case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_UNSUPPORTED_VERSION:
                response.set("Sec-WebSocket-Version", Poco::Net::WebSocket::WEBSOCKET_VERSION);
            case Poco::Net::WebSocket::WS_ERR_NO_HANDSHAKE:
            case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_VERSION:
            case Poco::Net::WebSocket::WS_ERR_HANDSHAKE_NO_KEY:
                response.setStatusAndReason(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                response.setContentLength(0);
                response.send();
                break;
        }
    }
}

void WebSocketHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                     Poco::Net::HTTPServerResponse &response) {

    Poco::URI uri(request.getURI());
    size_t id_room = 0;

    for (const auto &x : uri.getQueryParameters()) {
        if (x.first == "room_id") id_room = size_t(std::atoi(x.second.c_str()));
    }

    if (!Rooms.empty()) {
        Poco::Net::WebSocket *ws = new Poco::Net::WebSocket(request, response);
        ws->setKeepAlive(true);
        Rooms[id_room].connections.insert(std::make_pair(Rooms[id_room].size() + 1, ws));
        SocketFunction(*ws, response, Rooms[id_room]);
    } else {
        Room room(id_room);
        Rooms.insert(std::make_pair(id_room, room));
        Poco::Net::WebSocket *ws = new Poco::Net::WebSocket(request, response);
        ws->setKeepAlive(true);
        Rooms[id_room].connections.insert(std::make_pair(Rooms[id_room].size() + 1, ws));
        SocketFunction(*ws, response, Rooms[id_room]);
    }
}
