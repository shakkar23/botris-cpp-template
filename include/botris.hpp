#pragma once
#include <cstdlib>
#include <iostream>
#include <string>

#include "./json.hpp"

#ifdef _WIN32
#include <IXNetSystem.h>
#include <IXUserAgent.h>
#include <IXWebSocket.h>
#else
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXUserAgent.h>
#include <ixwebsocket/IXWebSocket.h>
#endif

using namespace std;

namespace botris {
ix::WebSocket webSocket;

struct Secrets {
    string API_TOKEN;
    string ROOM_KEY;
};

const Secrets get_secrets() {
    string api_token, room_key;

    if (const char* env_p = std::getenv("BOTRIS_API_TOKEN")) {
        std::cout << "Your TOKEN is: " << env_p << std::endl;
        api_token = env_p;
    } else {
        std::cout << "Set the path to the environment variable before running!" << std::endl;
        exit(1);
    }
    std::cout << "Room key: ";
    cin >> room_key;
    std::cout << std::endl;

    const Secrets SECRETS{api_token, room_key};
    return SECRETS;
}

bool wss_connect(Secrets SECRETS) {
#ifdef _WIN32
    //! Required on Windows
    ix::initNetSystem();
#endif

    string url("wss://botrisbattle.com/ws?token=" + SECRETS.API_TOKEN + "&roomKey=" + SECRETS.ROOM_KEY);
    webSocket.setUrl(url);
    webSocket.start();

    webSocket.setOnMessageCallback([&](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            nlohmann::json message = nlohmann::json::parse(msg->str);
            std::cout << "received message: " << msg->str << std::endl;

            if (message["type"].dump() == "\"request_move\"") {
                nlohmann::json action;
                action["type"] = "action";

                nlohmann::json commands = nlohmann::json::array();

                commands.push_back("sonic_drop");

                action["payload"] = commands;

                // webSocket.send("{type:'action'; payload: {commands: ['sonic_drop']}}");
                webSocket.send(action.dump());
            }

        } else if (msg->type == ix::WebSocketMessageType::Open) {
            std::cout << "Connection established" << std::endl;
            std::cout << "> " << std::flush;
        } else if (msg->type == ix::WebSocketMessageType::Error) {
            // Maybe SSL is not configured properly
            std::cout << "Connection error: " << msg->errorInfo.reason << std::endl;
            std::cout << "> " << std::flush;
        }
    });

    return true;
}

}  // namespace botris
