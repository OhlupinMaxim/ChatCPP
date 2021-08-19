#pragma once

#include <thread>

#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServer.h>

#include "Socket.hpp"
#include "RequestHandlerFactory.h"
#include "Preloader.hpp"


const std::string errorArgsStarted = "Данному процессу при запуске не нужны аргументы, \n"
                                     "Выполните перезапуск без аргументов \n";

class ServerApplication : public Poco::Util::ServerApplication {

private:
    int main(const std::vector<std::string> &args) override;

};