cmake_minimum_required(VERSION 3.16)

project(segvc-parser
	VERSION 1.0.0
	LANGUAGES C CXX
)

option(IS_SHARED "Build shared library" ON)

if(IS_SHARED)
	add_library(segvc-parser SHARED)
else()
	add_library(segvc-parser STATIC)
endif()

file(GLOB_RECURSE SEGVC_PARSER_SOURCES
	CONFIGURE_DEPENDS
	src/*.c
	src/*.cpp
	src/*.cxx
)

target_sources(segvc-parser
	PRIVATE
		${SEGVC_PARSER_SOURCES}
)

target_include_directories(segvc-parser
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
