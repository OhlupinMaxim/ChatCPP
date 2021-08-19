#include "include/ErrorSerializer.h"

ErrorSerializer::ErrorSerializer(int _status) : BaseJson(_status) {}

ErrorSerializer::~ErrorSerializer() = default;

const std::string ErrorSerializer::serialize(const std::string &HTTP_ERR_MSG) {
    json["MESSAGE"] = HTTP_ERR_MSG;
    std::unique_ptr<std::string> result (new std::string);
    serializeJson(json, *result);
    return *result;
}