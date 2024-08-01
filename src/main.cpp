
#include "botris.hpp"

int main() {
    auto secrets = botris::get_secrets();

    botris::wss_connect(secrets);

    int s;
    std::cin >> s;

    return 0;
}