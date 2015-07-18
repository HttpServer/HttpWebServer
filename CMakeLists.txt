cmake_minimum_required(VERSION 2.6)

#Déclaration du projet

project(HttpWebServer)

add_executable(httpServer include/httpRequest.h include/httpResponse.h lib/httpRequest.c lib/httpResponse.c src/main.c)

TARGET_LINK_LIBRARIES(
httpServer
pthread
)


