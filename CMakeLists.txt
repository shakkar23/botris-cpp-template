
cmake_minimum_required(VERSION 3.22)

project("botris bot")
set(CMAKE_CXX_STANDARD 20)

set(USE_TLS ON)
set(USE_WS ON)

add_subdirectory("./modules/IXWebSocket")

find_package(ixwebsocket)

set(main_sources
    "src/main.cpp"

    # this is where you put the rest of your sources
)

add_executable(main ${main_sources})

target_link_libraries(main PRIVATE ixwebsocket::ixwebsocket)
