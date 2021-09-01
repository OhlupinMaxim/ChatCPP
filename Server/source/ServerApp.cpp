#include "include/ServerApp.h"

int ServerApplication::main(const std::vector<std::string>& args) {
    if (!args.empty()){
        std::cerr << errorArgsStarted << std::endl;
        throw Poco::ApplicationException();
    }

    createStaticFolder();

    auto * params = new Poco::Net::HTTPServerParams;
    params->setKeepAlive(true);
    params->setMaxThreads(std::thread::hardware_concurrency()
                          * std::thread::hardware_concurrency() * 1000);
    params->setThreadPriority(Poco::Thread::PRIO_NORMAL);
    params->setMaxKeepAliveRequests(std::thread::hardware_concurrency()
                                                * std::thread::hardware_concurrency() * 1000);
    params->setKeepAliveTimeout(Poco::Timespan(0,0,10,0,0));
    std::unique_ptr<Socket> socket (new Socket("localhost:8080"));

    std::unique_ptr<Poco::Net::HTTPServer> server(
            new Poco::Net::HTTPServer(
                    new RequestHandlerFactory(),
                    *socket,
                    params
            ));

    server->start();

    printServerParamsStarted(params);

    waitForTerminationRequest();

    server->stopAll();

    return EXIT_SUCCESS;
}