#include "include/handlers/FileHandler.h"

FileHandler::FileHandler(const std::string &_pathFile) : pathFile(_pathFile) {}

FileHandler::~FileHandler() = default;

void FileHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    Poco::Mutex mutex;
    Poco::ScopedLock<Poco::Mutex> lock(mutex);

    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    response.setContentType("text/html; charset=utf-8");

    try {

        std::ifstream in(pathFile);
        std::ostream &out = response.send();

        char *c = new char[1];
        *c = in.get();
        while (in.good()) {
            out << c;
            *c = in.get();
        }
        out.flush();
        in.close();

        printLog(request, response);

    } catch (std::exception &e) {
        throw Poco::NotFoundException(e.what());
    }
}