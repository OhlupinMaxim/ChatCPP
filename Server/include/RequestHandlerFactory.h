#pragma once


#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>


#include "handlers/BaseHandler.h"


class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {

public:
    RequestHandlerFactory();

    ~RequestHandlerFactory();

    Poco::Net::HTTPRequestHandler * createRequestHandler(const Poco::Net::HTTPServerRequest& request);
};