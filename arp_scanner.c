// arp_scanner.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>

#define INTERFACE "en0"  // Change to your network interface
#define IP_BASE "192.168.12."  // Base IP to scan
#define START 1
#define END 254

void get_mac(const char *iface, uint8_t *mac) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct ifreq ifr;
    strncpy(ifr.ifr_name, iface, IFNAMSIZ);
    ioctl(fd, SIOCGIFHWADDR, &ifr);
    memcpy(mac, ifr.ifr_hwaddr.sa_data, 6);
    close(fd);
}

void get_ip(const char *iface, struct in_addr *ip) {
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct ifreq ifr;
    strncpy(ifr.ifr_name, iface, IFNAMSIZ);
    ioctl(fd, SIOCGIFADDR, &ifr);
    *ip = ((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr;
    close(f
