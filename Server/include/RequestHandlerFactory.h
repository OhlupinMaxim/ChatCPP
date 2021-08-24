#pragma once

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>

#include "handlers/RoomInfoHandler.h"
#include "handlers/WebSocketHandler.h"
#include "handlers/ErrorRequestHandler.h"
#include "handlers/FileHandler.h"
#include "handlers/StaticPath.hpp"



class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

public:
    RequestHandlerFactory();

    ~RequestHandlerFactory();

    Poco::Net::HTTPRequestHandler *createRequestHandler(const Poco::Net::HTTPServerRequest &request);
private:
    bool concatURI (const std::string& URI, const std::string& apiURI) const;
};