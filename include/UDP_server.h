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
#include <thread>
#include "entities.h"
#include "constants.h"
#include "UDP_client.h"

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
    entities::Cell buffer[constants::WIDTH_PIXEL_COUNT * constants::HEIGHT_PIXEL_COUNT];
    std::size_t bufsize {constants::WIDTH_PIXEL_COUNT * constants::HEIGHT_PIXEL_COUNT * sizeof(entities::Cell)};


    public:
    UDP_Server(UDP_Server const&) = delete;
    void operator=(UDP_Server const&) = delete;
    int generate_socket();
    void refresh_buffer(const std::vector<entities::Cell> &cellGrid);
    void sendto_grid(int sockfd, const struct addrinfo *p);


};

#endif //GRIDRAY_UDP_SERVER_H