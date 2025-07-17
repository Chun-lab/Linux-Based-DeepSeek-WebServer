#include "ChatBot.h"
#include <stdexcept>

// 实现时移除默认参数（只在头文件声明中保留）
std::string Bot::getChatResponse(
    const std::string& question, 
    bool includeSystemPrompt,  // 无默认值
    const std::string& model   // 无默认值
) {
    CURL* curl = nullptr;
    CURLcode res;
    std::string readBuffer;
    std::string response;

    try {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if (!curl) { 
            throw std::runtime_error("Failed to initialize CURL");
        }

        struct curl_slist* headers = nullptr;
        std::string apiKey = "your-API Key"; // 替换为你的真实 API Key
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // 构建消息列表
        json messages;
        if (includeSystemPrompt) {
            messages.push_back({{"role", "system"}, {"content", "You are a helpful assistant."}});
        }
        messages.push_back({{"role", "user"}, {"content", question}});

        json requestBody = {
            {"model", model},
            {"messages", messages},
            {"stream", false},
            {"temperature", 0.7},
            {"max_tokens", 2048}
        };
        std::string data = requestBody.dump();

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.deepseek.com/chat/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            throw std::runtime_error(std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));
        }

        // 解析响应
        json jsonResponse = json::parse(readBuffer);
        if (jsonResponse.contains("choices") && !jsonResponse["choices"].empty() &&
            jsonResponse["choices"][0].contains("message") &&
            jsonResponse["choices"][0]["message"].contains("content")) {
            response = jsonResponse["choices"][0]["message"]["content"];
        } else {
            throw std::runtime_error("Unexpected JSON structure: " + jsonResponse.dump());
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        response = "";
    }

    // 清理资源
    if (curl) {
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return response;
}

// 静态回调函数实现
size_t Bot::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}