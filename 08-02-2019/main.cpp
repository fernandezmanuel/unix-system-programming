
// Title:  Ethernet Control Monitor
// Author: Manuel Fernandez
// Date:   Feb 08, 2019
// Run:    ./mainprog ens33
///////////////////////////////////////////////////////////////////////
// Description: Displays ethernet information for a provided interface.
// IP/MAC/Broadcast addresses are displayed along with Network mask.
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#define NAMESIZE 20

int main() {
    
    int file_desc;
    int data;
    int sel;
    struct ifreq intf_freq;
    char intf_name[NAMESIZE];
    unsigned char *mac = NULL;
    
    system("clear");
    
    std::cout << "\nName of the interface: ";
    std::cin >> intf_name;
    
    size_t intf_name_len = strlen(intf_name);
    
    if (intf_name_len < sizeof(intf_freq.ifr_name)) {
        memcpy(intf_freq.ifr_name, intf_name, intf_name_len);
        intf_freq.ifr_name[intf_name_len] = 0;
    } else {
        std::cout << "Interface name exceeds the limit" << std::endl;
        return -1;
    }
    
    file_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if (file_desc < 0) {
        std::cout << strerror(errno);
        return -1;
    }
    
    system("clear");
    
    do {
        std::cout << "\nPlease select an option: \n" << std::endl;
        std::cout << "1- MAC Address" << std::endl;
        std::cout << "2- IP Address" << std::endl;
        std::cout << "3- Network Mask" << std::endl;
        std::cout << "4- Broadcast Address" << std::endl;
        std::cout << "0- Exit" << std::endl << std::endl;
        std::cin >> sel;
        
        struct sockaddr_in* tmp;
        
        switch(sel) {
            case 1: {
                data = ioctl(file_desc, SIOCGIFHWADDR, &intf_freq);
                if(data < 0) {
                    std::cout << strerror(errno);
                } else if (intf_freq.ifr_hwaddr.sa_family != ARPHRD_ETHER) {
                    std::cout << "Invalid ethernet interface" << std::endl;
                } else {
                    mac = (unsigned char*)intf_freq.ifr_hwaddr.sa_data;
                    printf("\nHardware Address: %02X:%02X:%02X:%02X:%02X:%02X\n\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
                }
                break;
            }
            case 2: {
                data = ioctl(file_desc, SIOCGIFADDR, &intf_freq);
                if (data < 0) {
                    std::cout << strerror(errno) << std::endl;
                } else {
                    tmp = (struct sockaddr_in*)&intf_freq.ifr_addr;
                    std::cout << "\nIP Address: " << inet_ntoa(tmp->sin_addr) << std::endl << std::endl;
                }
                break;
            }
            case 3: {
                data = ioctl(file_desc, SIOCGIFNETMASK, &intf_freq);
                if (data < 0) {
                    std::cout << strerror(errno) << std::endl;
                } else {
                    tmp = (struct sockaddr_in*)&intf_freq.ifr_netmask;
                    std::cout << "\nNetwork Mask: " << inet_ntoa(tmp->sin_addr) << std::endl << std::endl;
                }
                break;
            }
            case 4: {
                data = ioctl(file_desc, SIOCGIFBRDADDR, &intf_freq);
                if (data < 0) {
                    std::cout << strerror(errno) << std::endl;
                } else {
                    tmp = (struct sockaddr_in*)&intf_freq.ifr_broadaddr;
                    std::cout << "\nBroadcast Address: " << inet_ntoa(tmp->sin_addr) << std::endl << std::endl;
                }
                break;
            }
        }
        if (sel != 0) {
            char letter;
            std::cout << "Press any key to continue.";
            std::cin >> letter;
            system("clear");
        }
    } while (sel != 0);
    close(file_desc);
    return 0;
}
