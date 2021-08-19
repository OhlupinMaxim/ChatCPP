#pragma once

#include <memory>
#include <iostream>

#include <Poco/DateTime.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/LocalDateTime.h>

#include "ArduinoJsonHeader.h"


class BaseJson {

private:
    int status;

protected:
    ArduinoJson::StaticJsonDocument<8 * 1024> json;

public:
    BaseJson(int _status = 200);

    ~BaseJson();
};