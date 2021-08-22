#pragma once

#include "BaseJson.h"

static size_t room_id = 0;

class RoomInfoSerializer: public BaseJson {

public:
    RoomInfoSerializer(int _status = 200);

    ~RoomInfoSerializer();

    const std::string serialize();

    const std::string serialize(const size_t id);
};