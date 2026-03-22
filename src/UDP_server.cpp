


#include "../include/UDP_server.h"
#include "../include/constants.h"
int UDP_Server::generate_socket() {
    struct addrinfo hints {0}, *servinfo, *p;



    //memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int rv {getaddrinfo("255.255.255.255", constants::PORT, &hints, &servinfo)};
        if (rv != 0) {
            std::cerr << "getaddrinfo error: " << gai_strerror(rv) << std::endl;
            return 1;
        }

    for (p = servinfo; p != nullptr; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            std::cerr << "socket error: " << std::endl;
            continue;
        }
        int yes {1};
        if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes)) == -1) {
            std::cerr << "setsockopt error: " << std::endl;
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == nullptr) {
        std::cerr << "socket creation error: " << std::endl;
        return 2;
    }

    std::thread sender(&UDP_Server::sendto_grid, this, sockfd, p);
    sender.detach();

    //freeaddrinfo(servinfo);

    //close(sockfd);

    return 0;
}

void UDP_Server::refresh_buffer(const std::vector<entities::Cell> &cellGrid) {
    std::lock_guard<std::mutex> lock(UDP_Client::getInstance().get_mutex());
    std::memcpy(buffer, cellGrid.data(), cellGrid.size() * sizeof(entities::Cell));
}

void UDP_Server::sendto_grid(int socket, const struct addrinfo *p) {

    while (true) {
        refresh_buffer(entities::cellGrid);
        int header = 0xDEADBEEF;
        sendto(socket, &header, sizeof(header), 0, p->ai_addr, p->ai_addrlen);

        std::size_t payload {bufsize};
        std::size_t transmission_size {1200};
        std::size_t currloc {0};
        std::size_t numbytes {0};
        while (payload > 0) {

            std::size_t to_send {std::min(payload, transmission_size)};
            if ((numbytes = sendto(socket, buffer + currloc, to_send, 0,
                p->ai_addr, p->ai_addrlen)) == -1) {
                std::cerr << "sendto error: " << std::endl;
                std::cerr << strerror(errno) << std::endl;
                exit(1);
                }
            currloc += numbytes;
            payload -= numbytes;
            std::cout << "bytes sent: " << numbytes << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}


