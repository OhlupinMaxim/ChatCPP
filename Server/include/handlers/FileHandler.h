//
// Created by maxim on 21.08.2021.
//

#pragma once

#include <thread>
#include <chrono>

#include "Mims.hpp"
#include "BaseHandler.h"

static std::map<std::string, std::unique_ptr<Poco::Mutex>> files_mutex = {};

class FileHandler : public BaseHandler {

private:
    std::string pathFile;
public:
    FileHandler(const std::string &_pathFile);

    ~FileHandler();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

private:
    void LockGetFile() const;
    void UnlockGetFile() const;
};


