//
// Created by Hamza Nisar on 21/03/2026.
//
#ifndef GRIDRAY_UDP_CLIENT_H
#define GRIDRAY_UDP_CLIENT_H
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
#include <mutex>
#include "entities.h"
#include "constants.h"

class UDP_Client {
    public:
    static UDP_Client& getInstance() {
        static UDP_Client instance;
        return instance;
    }
    private:
    UDP_Client() : sockfd{-1} {

    };



    int sockfd;
    struct sockaddr *m_their_addr;
    socklen_t m_their_addr_len;
    entities::Cell buffer[sizeof(entities::Cell) * constants::WIDTH_PIXEL_COUNT * constants::HEIGHT_PIXEL_COUNT];
    std::size_t bufsize {constants::WIDTH_PIXEL_COUNT * constants::HEIGHT_PIXEL_COUNT * sizeof(entities::Cell)};
    std::mutex grid_mutex;

    public:
    UDP_Client(UDP_Client const&) = delete;
    void operator=(UDP_Client const&) = delete;
    void *get_in_addr(struct sockaddr *sa);
    int generate_listener();
    void fill_buffer(int socket);
    std::mutex& get_mutex();




};

#endif //GRIDRAY_UDP_CLIENT_H