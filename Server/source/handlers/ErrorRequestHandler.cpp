#include "include/handlers/ErrorRequestHandler.h"

ErrorRequestHandler::ErrorRequestHandler(const int &_status, const std::string &_msg) : status(_status), msg(_msg) {};

ErrorRequestHandler::~ErrorRequestHandler() = default;

void ErrorRequestHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                        Poco::Net::HTTPServerResponse &response) {
    Poco::Mutex mutex;
    Poco::ScopedLock<Poco::Mutex> lock(mutex);

    response.setStatus(std::to_string(status));
    auto &send = response.send();

    std::unique_ptr<ErrorSerializer> serializer(new ErrorSerializer(status));
    send << serializer->serialize(getErrorMessage() + "\n" + msg);

    printLog(request, response);
}

const std::string ErrorRequestHandler::getErrorMessage() const {

    std::unique_ptr<std::string> message(new std::string);

    switch (status) {
        case Poco::Net::HTTPResponse::HTTP_BAD_REQUEST:
            *message = "Bad Request";
            break;
        case Poco::Net::HTTPResponse::HTTP_NOT_FOUND:
            *message = "Not Found";
            break;
        case Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR:
            *message = "Internal Server Error";
            break;
        default:
            *message = "Internal Server Error";
            break;
    }

    return *message;
}