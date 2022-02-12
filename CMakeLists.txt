cmake_minimum_required (VERSION 3.8)

project ("rtype")
project (rtype_client)
project (rtype_server)

if (WIN32)
	find_program(conan_path conan)
	message(${conan_path})
	execute_process(COMMAND ${conan_path} "install" "${PROJECT_SOURCE_DIR}" "-s" "compiler=Visual Studio" "-s" "compiler.version=16" "-s" "build_type=Debug" WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
else()
	add_definitions("-fPIC")
endif()
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# rtype Client
Set(Boost_INSTALL_DIR ${CONAN_BOOST_ROOT})
find_package(Boost REQUIRED COMPONENTS system filesystem date_time serialization)
include_directories(${CMAKE_INCLUDE_PATH} Include/Client/ Include/GameEngine/ Include/GameEngine/Entity/ Include/GameEngine/Objet/ Include/GameEngine/Scenes/ ${CONAN_INCLUDE_DIRS_BOOST})
set(CLIENT_BUILD_DIR "${CMAKE_BINARY_DIR}/bin/")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable (rtype_client
"Client/main.cpp"
"Client/Client.cpp"
"Client/ConnectionServer.cpp"

# Game Engine
"GameEngine/ManageScene.cpp"
"GameEngine/ManageElement.cpp"

# Scenes
"GameEngine/Scenes/Menu.cpp"
"GameEngine/Scenes/Lobby.cpp"
"GameEngine/Scenes/Game.cpp"

# Objet
"GameEngine/Objet/Buttons.cpp"
"GameEngine/Objet/Icons.cpp"
"GameEngine/Objet/Input.cpp"
"GameEngine/Objet/Text.cpp"
"GameEngine/Objet/Background.cpp"

# Entity
"GameEngine/Entity/Player.cpp"
"GameEngine/Entity/Obstacles.cpp"
"GameEngine/Entity/Bullet.cpp"
)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
target_link_libraries(rtype_client Threads::Threads)
target_link_libraries(rtype_client sfml-graphics sfml-window sfml-system sfml-audio)
target_link_libraries(rtype_client -lboost_serialization)

# rtype Server
include_directories(${CMAKE_INCLUDE_PATH} Include/Server/ Include/Server/Map)
set(SERVER_BUILD_DIR "${CMAKE_BINARY_DIR}/bin/")

add_executable (rtype_server
"Server/main.cpp"
"Server/Server.cpp"
"Server/GameInstance.cpp")

target_link_libraries(rtype_server ${CONAN_LIBS} ${CONAN_LIB_DIRS_BOOST} -lboost_serialization)
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set_target_properties(rtype_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${SERVER_BUILD_DIR}")
set_target_properties(rtype_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${SERVER_BUILD_DIR}")
set_target_properties(rtype_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${SERVER_BUILD_DIR}")
