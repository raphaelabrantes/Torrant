cmake_minimum_required(VERSION 3.24)
project(torrant)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIRS} )

add_executable(torrant
        src/main.cpp
        src/bencode/BencodeParser.cpp
        src/bencode/BencodeParser.h
        src/bencode/BencodeObject.cpp
        src/bencode/BencodeObject.h
        src/bencode/BencodeDict.h
        src/bencode/BencodeList.h
        src/bencode/BencodeList.cpp
        src/bencode/BencodeDict.cpp
        src/AnnounceSynchronizer.cpp
        src/AnnounceSynchronizer.h
        src/PieceManager.cpp
        src/PieceManager.h
        src/TrackerClient.cpp
        src/TrackerClient.h
        src/Piece.h
        src/Server.cpp
        src/Server.h
)

target_link_libraries(torrant Boost::headers)
target_link_options(torrant PUBLIC -lcryptopp)
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/tests ${CMAKE_CURRENT_BINARY_DIR}/tests
)
add_dependencies(torrant copy_assets)