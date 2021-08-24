//
// Created by maxim on 21.08.2021.
//

#pragma once

#include <fstream>

#include "Mims.hpp"
#include "BaseHandler.h"

class FileHandler : public BaseHandler {

private:
    std::string pathFile;
public:
    FileHandler(const std::string &_pathFile);

    ~FileHandler();

    void handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response);

};


