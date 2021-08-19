#pragma once

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPResponse.h>

#include <iostream>


class BaseHandler : public Poco::Net::HTTPRequestHandler {

protected:
    void printLog(Poco::Net::HTTPServerRequest &request,
                  Poco::Net::HTTPServerResponse &response) const;
};