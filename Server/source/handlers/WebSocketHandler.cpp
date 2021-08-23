#include "include/handlers/WebSocketHandler.h"

WebSocketHandler::WebSocketHandler() {}

WebSocketHandler::~WebSocketHandler() = default;

void WebSocketHandler::SocketFunction(Poco::Net::WebSocket &ws,
                                      Poco::Net::HTTPServerResponse &response, size_t id) const {
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
            char * msg = (char * ) buff_str.c_str();
            for(auto & x : socketMap){
                if (x.first != id){

                    // send Message
                    x.second->sendFrame(msg, strlen(msg), Poco::Net::WebSocket::FRAME_TEXT);
                }
            }
            // send Message
            ws.sendFrame(msg, strlen(msg), Poco::Net::WebSocket::FRAME_TEXT);


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
    socketIndex ++;
    printLog(request, response);
    Poco::Net::WebSocket *ws = new Poco::Net::WebSocket(request, response);
    ws->setKeepAlive(true);
    socketMap.insert(std::make_pair(socketIndex, ws));
    SocketFunction(*ws, response, socketIndex);
}
