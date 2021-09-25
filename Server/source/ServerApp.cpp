#include "include/ServerApp.h"

int ServerApplication::main(const std::vector<std::string>& args) {

    createStaticFolder();

    auto * params = new Poco::Net::HTTPServerParams;

    params->setMaxThreads(std::thread::hardware_concurrency());
    params->setThreadPriority(Poco::Thread::PRIO_NORMAL);
    params->setKeepAliveTimeout(Poco::Timespan(0,0,10,0,0));

    auto getHost = [&](const std::string& argument){
        if (argument == "local")
            return "localhost";
        if (argument == "docker")
            return "172.17.0.2";
        throw Poco::ApplicationException("False Argument on Start");
    };

    std::string host = getHost(args.at(0));

    std::cout << "Server start on " + host + ":8080";

    std::unique_ptr<Socket> socket (new Socket(host + ":8080"));

    std::unique_ptr<Poco::Net::HTTPServer> server(
            new Poco::Net::HTTPServer(
                    new RequestHandlerFactory(),
                    *socket,
                    params
            ));

    server->start();

    waitForTerminationRequest();

    server->stopAll();

    return EXIT_SUCCESS;
}