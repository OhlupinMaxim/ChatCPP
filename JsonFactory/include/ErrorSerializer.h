#include "BaseJson.h"

class ErrorSerializer : public BaseJson{
public:
    ErrorSerializer(int _status);
    ~ErrorSerializer();

    const std::string serialize(const std::string& HTTP_ERR_MSG);
};