#ifndef CHATBOT_H
#define CHATBOT_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Bot {
public:
    Bot() {}

    // 声明：包含 includeSystemPrompt 参数和默认值
    std::string getChatResponse(
        const std::string& question, 
        bool includeSystemPrompt = false,  // 默认 false
        const std::string& model = "deepseek-chat"  // 默认模型
    );

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

#endif // CHATBOT_H