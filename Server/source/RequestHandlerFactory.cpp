#include "include/RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory() = default;

RequestHandlerFactory::~RequestHandlerFactory() = default;

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request) {
    return new ErrorRequestHandler(404);
}