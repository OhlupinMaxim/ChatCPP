#include "include/RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory() = default;

RequestHandlerFactory::~RequestHandlerFactory() = default;

bool RequestHandlerFactory::concatURI (const std::string& URI, const std::string& apiURI) const {
    auto indexSlash = URI.find_last_of("/");
    return URI.substr(0, indexSlash+1) == apiURI;
}

Poco::Net::HTTPRequestHandler *RequestHandlerFactory::createRequestHandler(
        const Poco::Net::HTTPServerRequest &request) {

    auto &uri = request.getURI();

    try {
        if (concatURI(uri, homeURL)) return new FileHandler(homePage);

        if (concatURI(uri, roomURL)) return new FileHandler(roomPage);

        if (concatURI(uri, addRoomURL)) return new FileHandler(addedRoomPage);

        if (concatURI(uri, apiRoomURL)) return new RoomInfoHandler();

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