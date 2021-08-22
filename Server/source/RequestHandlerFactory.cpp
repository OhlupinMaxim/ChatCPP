#include "include/RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory() = default;

RequestHandlerFactory::~RequestHandlerFactory() = default;

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request) {

    auto &uri = request.getURI();

    try {
        if (uri == "/") return new FileHandler(homePage);

        if (uri == "/room/") return new FileHandler(roomPage);

        if (uri == "/room/add/") return new FileHandler(addedRoomPage);

        if (uri == "/api/room/id/")

        if (request.find("Upgrade") != request.end()) {
            if (Poco::icompare(request["Upgrade"], "websocket") == 0) {
                return new WebSocketHandler();
            }
        }

        return new FileHandler(err404page);

    } catch (Poco::NotFoundException &ex1) {
        return new FileHandler(err404page);
    } catch (Poco::InvalidArgumentException &ex2) {
        return new FileHandler(err400page);
    } catch (Poco::UnhandledException &ex3) {
        return new FileHandler(err405page);
    } catch (Poco::ApplicationException &ex4) {
        return new FileHandler(err500page);
    }
}