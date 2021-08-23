#pragma once

#include <Poco/Net/WebSocket.h>
#include <Poco/Net/NetException.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/LocalDateTime.h>
#include <Poco/Format.h>

#include <map>

#include "BaseHandler.h"


class WebSocketHandler : public BaseHandler {

public:
    WebSocketHandler();

    ~WebSocketHandler();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

    void SocketFunction(Poco::Net::WebSocket &ws, Poco::Net::HTTPServerResponse &response, size_t id) const;
};

static size_t socketIndex = 0;
static std::map<size_t, Poco::Net::WebSocket * > socketMap = {};
