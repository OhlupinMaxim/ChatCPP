#include "include/BaseJson.h"

BaseJson::BaseJson(int _status) : status(_status) {
    std::unique_ptr<Poco::LocalDateTime> localTime( new Poco::LocalDateTime);
    std::unique_ptr<Poco::DateTimeFormatter> formatter( new Poco::DateTimeFormatter);
    json["Content Type"] = "application/json";
    json["DateTime"] = formatter->format(localTime->timestamp(), "%Y.%n.%d - %H:%M:%S");
    json["Status"] = status;
}

BaseJson::~BaseJson() = default;

const std::string BaseJson::toString() const {
    std::unique_ptr<std::string> result (new std::string);
    serializeJson(json, *result);
    return *result;
}

