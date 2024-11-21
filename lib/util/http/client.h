#pragma once

#include <map>
#include <string>

#include <cpr/cpr.h>
#include <jsoncpp/json/json.h>


const int RETRY_COUNT = 3;
const int RETRY_DELAY_MS = 1000;

class THttpClient {
public:
    THttpClient(const std::string& endpoint);
    ~THttpClient();

    void SetHeader(const std::string& name, const std::string& value);
    void RemoveHeader(const std::string& name);
    void ClearHeaders();

    Json::Value Get(const std::string& url);
    Json::Value Post(
        const std::string& url,
        const Json::Value& body = Json::Value(Json::ValueType::objectValue)
    );
    Json::Value PostMultipart(
        const std::string& url,
        const cpr::Multipart& multipart
    );

private:
    std::map<std::string, std::string> headers_;
    std::string endpoint;
};
