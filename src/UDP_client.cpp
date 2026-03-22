//
// Created by Hamza Nisar on 22/03/2026.
//

#include "../include/UDP_client.h"

void *UDP_Client::get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int UDP_Client::generate_listener() {
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;
    struct sockaddr_storage their_addr;
    char buf[100];
    char s[INET_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    if ((rv = getaddrinfo(nullptr, constants::PORT, &hints, &servinfo)) != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(rv) << std::endl;
        return 1;
    }

    for(p = servinfo; p != nullptr; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            std::cerr << "socket error: " << strerror(errno) << std::endl;
            continue;
        }


        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            std::cerr << "bind error: 1"  << std::endl;
            continue;
        }

        break;
    }

    if (p ==nullptr) {
        std::cerr << "bind error: 2"  << std::endl;
        return 2;
    }

    freeaddrinfo(servinfo);

    m_their_addr_len = sizeof their_addr;
    std::thread recieve(&UDP_Client::fill_buffer, this, sockfd);
    recieve.detach();

    //close(sockfd);

    return 0;
}

void UDP_Client::fill_buffer(int socket) {
    struct sockaddr_storage src_addr;

    while (true) {
        socklen_t src_addr_len = sizeof(src_addr);

        // 1. SYNC: Hunt for Header
        int checksum = 0;
        ssize_t sync_bytes = recvfrom(socket, &checksum, sizeof(int), 0, (struct sockaddr *)&src_addr, &src_addr_len);
        if (sync_bytes != sizeof(int) || checksum != 0xDEADBEEF) continue;

        // 2. DATA: Collect Grid with HARD bounds
        std::size_t currloc = 0;

        // Use a local copy of bufsize to ensure it doesn't change mid-loop
        const std::size_t target_size = entities::cellGrid.size() * sizeof(entities::Cell);

        while (currloc < target_size) {
            // Calculate remaining space to prevent overflow
            std::size_t remaining = target_size - currloc;
            std::size_t to_recv = std::min(remaining, (std::size_t)1200);

            src_addr_len = sizeof(src_addr); // Reset every time
            ssize_t bytes = recvfrom(socket, (char*)buffer + currloc, to_recv, 0,
                                    (struct sockaddr *)&src_addr, &src_addr_len);

            if (bytes <= 0) break; // Error or socket closed

            currloc += bytes;

            // EMERGENCY BREAK: If we somehow exceeded bounds
            if (currloc > target_size) {
                std::cerr << "Memory overwrite prevented!" << std::endl;
                break;
            }
        }

        // 3. ATOMIC UPDATE: Only copy if data is perfectly sized
        if (currloc == target_size) {
            // LOCK HERE: Use the same mutex your renderer uses!
            std::lock_guard<std::mutex> lock(grid_mutex);
            std::memcpy(entities::cellGrid.data(), buffer, target_size);
            std::cout << "Update successful" << std::endl;
        }
    }
}

std::mutex& UDP_Client::get_mutex() {
    return grid_mutex;
}