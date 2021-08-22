#pragma once

#include "BaseHandler.h"
#include "RoomInfoSerializer.h"

#include <Poco/URI.h>

class RoomInfoHandler : public BaseHandler {

public:
    RoomInfoHandler();

    ~RoomInfoHandler();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

};