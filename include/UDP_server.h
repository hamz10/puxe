//
// Created by Hamza Nisar on 21/03/2026.
//
#ifndef GRIDRAY_UDP_SERVER_H
#define GRIDRAY_UDP_SERVER_H
#include <iostream>
#include <memory>
#include <unistd.h>
#include <cerrno>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

class UDP_Server {
    public:
    static UDP_Server& getInstance() {
        static UDP_Server instance;
        return instance;
    }
    private:
    UDP_Server() : sockfd{-1} {

    };


    int sockfd;
    char buffer[1024];


    public:
    UDP_Server(UDP_Server const&) = delete;
    void operator=(UDP_Server const&) = delete;
    int generate_socket();



};

#endif //GRIDRAY_UDP_SERVER_H