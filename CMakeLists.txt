
cmake_minimum_required(VERSION 3.22)

project("botris bot")
set(CMAKE_CXX_STANDARD 20)

if(UNIX AND NOT APPLE)
    option(USE_TLS "" ON)
    option(USE_WS "" ON)

    add_subdirectory("./modules/IXWebSocket")

    find_package(ixwebsocket)
else()
    find_package(ixwebsocket CONFIG REQUIRED)

endif()


set(main_sources
    "src/main.cpp"

    # this is where you put the rest of your sources
)

add_executable(main ${main_sources})

target_link_libraries(main PRIVATE ixwebsocket::ixwebsocket)
include_directories(include)