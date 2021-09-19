#include "include/handlers/FileHandler.h"

FileHandler::FileHandler(const std::string &_pathFile) : pathFile(_pathFile) {}

FileHandler::~FileHandler() = default;

void FileHandler::handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    Poco::Mutex mutex;
    Poco::ScopedLock<Poco::Mutex> lock(mutex);

    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    auto indexDot = pathFile.find_last_of(".");
    auto media_type = MIME_TYPE.at(pathFile.substr(indexDot + 1, pathFile.size() - indexDot));
    response.setContentType(media_type);

    try {
        LockGetFile();
        response.sendFile(pathFile, media_type);
        UnlockGetFile();
        printLog(request, response);
    } catch (Poco::FileNotFoundException &ex1) {
        throw Poco::NotFoundException(ex1.what());
    } catch (std::exception &e) {
        throw Poco::NotFoundException(e.what());
    }
}

void FileHandler::LockGetFile() const {
    try {
        files_mutex.at(pathFile);
        while (!files_mutex[pathFile]->tryLock()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    } catch (std::out_of_range &ex) {
        files_mutex.insert(std::make_pair(pathFile, std::make_unique<Poco::Mutex>()));
        files_mutex.at(pathFile);
        while (!files_mutex[pathFile]->tryLock()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
}

void FileHandler::UnlockGetFile() const {
    files_mutex.at(pathFile)->unlock();
}