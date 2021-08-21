#pragma once

#include "BaseHandler.h"
#include "ErrorSerializer.h"


class ErrorRequestHandler : public BaseHandler {

private:
    int status;
    std::string msg;
public:
    ErrorRequestHandler(const int &_status, const std::string &_msg);

    ~ErrorRequestHandler();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

private:
    const std::string getErrorMessage() const;
};