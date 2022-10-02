cmake_minimum_required(VERSION 3.23)
project(SokuLobbies)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/pkgs)

if (CMAKE_BUILD_TYPE STREQUAL Debug)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		add_compile_options(-W -Wall -Wextra)
		if (NOT WIN32)
			add_compile_options(-fsanitize=address)
			link_libraries(asan)
		endif ()
	endif ()
	add_compile_definitions(_DEBUG=1)
else ()
	add_compile_definitions(NDEBUG=1)
endif ()

add_subdirectory(src/SokuMod/SokuLib)
include_directories(src/Common)
find_package(SFML REQUIRED)

add_executable(
	SokuLobbiesServer
	src/Server/main.cpp
	src/Common/Packet.hpp
	src/Common/Packet.cpp
	src/Server/Connection.cpp
	src/Server/Connection.hpp
	src/Server/Server.cpp
	src/Server/Server.hpp
)
target_include_directories(SokuLobbiesServer PRIVATE ${SFML_INCLUDE_DIRS})
target_link_libraries(SokuLobbiesServer ${SFML_NETWORK_LIBRARY} ${SFML_SYSTEM_LIBRARY})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	add_definitions(-DWINVER=0x0501 -D_WIN32_WINNT=0x0501)

	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /Brepro")
	set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /Brepro")
	set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /Brepro")

	add_library(
		"SokuLobbiesMod"
		MODULE
		src/SokuMod/main.cpp
		src/Common/Packet.hpp
		src/Common/Packet.cpp
	)
	target_compile_options(SokuLobbiesMod PRIVATE /Zi)
	target_compile_definitions("SokuLobbiesMod" PRIVATE DIRECTINPUT_VERSION=0x0800 _CRT_SECURE_NO_WARNINGS)
	target_link_directories("SokuLobbiesMod" PRIVATE lib)
	target_link_libraries(
		SokuLobbiesMod
		SokuLib
		shlwapi
		ws2_32
		d3dx9
	)
	if (CMAKE_BUILD_TYPE STREQUAL Debug)
	else ()
		target_compile_definitions(SokuLobbiesMod PRIVATE _LOBBYNOLOG=1)
	endif ()
endif()