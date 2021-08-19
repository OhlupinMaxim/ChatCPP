#include "include/handlers/BaseHandler.h"

void BaseHandler::printLog(Poco::Net::HTTPServerRequest &request,
              Poco::Net::HTTPServerResponse &response) const {
    std::cout << "URI:\t" << request.getURI() << "\t" << "Status:\t" << response.getStatus() << std::endl;
}