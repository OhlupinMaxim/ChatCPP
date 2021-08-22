#include "include/handlers/WebSocketHandler.h"

WebSocketHandler::WebSocketHandler() {}

WebSocketHandler::~WebSocketHandler() = default;

void WebSocketHandler::SocketFunction(Poco::Net::WebSocket &ws,
                                      Poco::Net::HTTPServerResponse &response) const {
    try {
        char buffer[1024];
        int flags;
        int n;
        do {
            n = ws.receiveFrame(buffer, sizeof(buffer), flags);
            ws.sendFrame(buffer, n, flags);
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

    printLog(request, response);
    Poco::Net::WebSocket ws(request, response);
    SocketFunction(ws, response);

}
