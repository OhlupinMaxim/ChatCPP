#include "include/RoomInfoSerializer.h"

RoomInfoSerializer::RoomInfoSerializer(int _status) : BaseJson(_status) {}

RoomInfoSerializer::~RoomInfoSerializer() = default;

const std::string RoomInfoSerializer::serialize() {
    room_id ++;
    json["RESPONSE"]["ROOM_ID"] = room_id;
    return toString();
}

const std::string RoomInfoSerializer::serialize(const size_t id) {
    json["RESPONSE"]["ROOM_ID"] = id;
    return toString();
}
