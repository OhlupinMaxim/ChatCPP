#pragma once

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "handlers/RoomInfoHandler.h"
#include "handlers/WebSocketHandler.h"
#include "handlers/ErrorRequestHandler.h"
#include "handlers/FileHandler.h"


class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

public:
    RequestHandlerFactory();

    ~RequestHandlerFactory();

    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request);

};