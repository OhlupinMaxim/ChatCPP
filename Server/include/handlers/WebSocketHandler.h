#pragma once

#include <Poco/Net/WebSocket.h>
#include <Poco/Net/NetException.h>

#include "BaseHandler.h"

class WebSocketHandler : public BaseHandler {

public:
    WebSocketHandler();

    ~WebSocketHandler();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

    void SocketFunction(Poco::Net::WebSocket &ws, Poco::Net::HTTPServerResponse &response) const;
};
