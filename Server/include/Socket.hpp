#pragma once

#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/ServerSocketImpl.h>

class ServerSocketImpl : public Poco::Net::ServerSocketImpl {

public:
    using Poco::Net::ServerSocketImpl::init;

};

class Socket : public Poco::Net::Socket {

public:

    Socket(const std::string &_addres) : Poco::Net::Socket(new ServerSocketImpl()) {

        const Poco::Net::SocketAddress addres(_addres);
        ServerSocketImpl *socket = static_cast<ServerSocketImpl *>(impl());

        socket->init(addres.af());
        socket->setReuseAddress(true);
        socket->setReusePort(true);
        socket->bind(addres, false);
        socket->listen();
    }
};