#include "include/handlers/RoomInfoHandler.h"

RoomInfoHandler::RoomInfoHandler() {}

RoomInfoHandler::~RoomInfoHandler() = default;

void RoomInfoHandler::handleRequest(Poco::Net::HTTPServerRequest &request,
                                    Poco::Net::HTTPServerResponse &response) {

    Poco::Mutex mutex;
    Poco::ScopedLock<Poco::Mutex> lock(mutex);

    size_t now_id_room = 0;
    std::unique_ptr<RoomInfoSerializer> serializer( new RoomInfoSerializer);

    std::unique_ptr<Poco::URI> uri (new Poco::URI(request.getURI()));

    for(const auto& x : uri->getQueryParameters()){
        if (x.first == "room_id") now_id_room = size_t (std::atoi(x.second.c_str()));
    }

    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    response.setContentType("application/json");

    if (now_id_room == 0){
        response.send() << serializer->serialize();
    }else{
        response.send() << serializer->serialize(now_id_room);
    }

    printLog(request, response);
}