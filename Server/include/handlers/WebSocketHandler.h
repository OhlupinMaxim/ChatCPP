#pragma once

#include <Poco/Net/WebSocket.h>
#include <Poco/Net/NetException.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/LocalDateTime.h>
#include <Poco/Format.h>
#include <Poco/URI.h>

#include <map>

#include "BaseHandler.h"


struct Room {
public:
    size_t id;
    std::map<size_t, Poco::Net::WebSocket *> connections;

    Room(){
      connections = {};
    };

    Room(size_t _id) : id(_id) {
        connections = {};
    };

    ~Room() = default;

    size_t size() const {
        return connections.size();
    }

    void setID (const size_t _id){
        id = _id;
    }
};

static std::map<size_t, Room> Rooms = {};

class WebSocketHandler : public BaseHandler {

public:
    WebSocketHandler();

    ~WebSocketHandler();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

    void SocketFunction(Poco::Net::WebSocket &ws, Poco::Net::HTTPServerResponse &response, Room& room) const;
};
