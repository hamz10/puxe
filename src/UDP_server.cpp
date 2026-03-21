


#include "../include/UDP_server.h"
#include "../include/constants.h"
int UDP_Server::generate_socket() {
    struct addrinfo hints, *servinfo, *p;
    int rv;
    int numbytes;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    rv = getaddrinfo("255.255.255.255", constants::PORT, &hints, &servinfo);
        if (rv != 0) {
            std::cerr << "getaddrinfo error: " << gai_strerror(rv) << std::endl;
            return 1;
        }

    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            std::cerr << "socket error: " << std::endl;
            continue;
        }
        int yes = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes)) == -1) {
            std::cerr << "setsockopt error: " << std::endl;
            close(sockfd);
            continue;
        }

        break;
    }

    if (p == NULL) {
        std::cerr << "socket creation error: " << std::endl;
        return 2;
    }

    if ((numbytes = sendto(sockfd, "test", strlen("test"), 0,
        p->ai_addr, p->ai_addrlen)) == -1) {
        std::cerr << "sendto error: " << std::endl;
        exit(1);
        }

    std::cerr << "bytes sent: " << numbytes << std::endl;
    freeaddrinfo(servinfo);

    close(sockfd);

    return 0;
}
