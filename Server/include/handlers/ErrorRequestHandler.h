#pragma once

#include "BaseHandler.h"
#include "ErrorSerializer.h"


class ErrorRequestHandler : public BaseHandler {

private:
    int status;

public:
    ErrorRequestHandler(int _status);

    ~ErrorRequestHandler();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

private:
    const std::string getErrorMessage() const;
};