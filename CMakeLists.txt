cmake_minimum_required(VERSION 3.15)

project(pong C)

set(SOURCES
        pong.c
)

add_executable(${PROJECT_NAME} ${SOURCES})