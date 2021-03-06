#pragma once

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/ScopedLock.h>
#include <Poco/Mutex.h>
#include <Poco/Exception.h>
#include <Poco/UUIDGenerator.h>

#include "StaticPath.hpp"

class BaseHandler : public Poco::Net::HTTPRequestHandler {

protected:
    void printLog(Poco::Net::HTTPServerRequest &request,
                  Poco::Net::HTTPServerResponse &response) const;
};