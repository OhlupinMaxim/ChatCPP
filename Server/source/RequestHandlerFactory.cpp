#include "include/RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory() = default;

RequestHandlerFactory::~RequestHandlerFactory() = default;

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request) {
    auto &uri = request.getURI();

    try {

        if (uri == "/") return new FileHandler(homePage);

        if (uri == "/chats/") return new FileHandler(roomPage);

        return new FileHandler(err404page);

    } catch (Poco::NotFoundException &ex1) {
        return new FileHandler(err404page);
    } catch (Poco::InvalidArgumentException &ex2) {
        return new FileHandler(err400page);
    } catch (Poco::ApplicationException &ex3) {
        return new FileHandler(err500page);
    }
}