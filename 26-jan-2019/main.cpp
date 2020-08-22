// Title:  I/O Control CD ROM
// Author: Manuel Fernandez
// Date:   Jan 26, 2019
// Run:    ./mainprog
///////////////////////////////////////////////////////////////////////
// Description: I/O Control Device manipulation of CD ROM tray
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include "ctrlUtil.h"

int main (int argc, char *argv[]) {
    int flag = 0;
    int fd = open("/dev/cdrom", O_RDONLY | O_NONBLOCK);
    
    if (fd < 0) {
        std::cout << "fd is not open" << std::endl;
        return(-1);
    }
    
    while (flag != -1) {
        int event = 0;
        // Displays menu options in the screen
        std::cout << "\nPlease make a selection:\n"
        << "\n1. Eject the CD Rom tray\n"
        << "2. Close the CD Rom tray\n"
        << "3. Get the tray position\n"
        << "0. Exit\n" << std::endl;
        
        std::cin >> event;
        
        switch (event) {
            case 1: {
                std::cout << "\nEjecting..." << std::endl;
                ejectTray(fd);
                break;
            }
            case 2: {
                std::cout << "\nClosing..." << std::endl;
                closeTray(fd);
                break;
            }
            case 3: {
                std::cout << "\nTray position: ";
                tPosition(fd);
                break;
            }
            case 0: {
                flag = -1;
                std::cout << "\nExiting..." << std::endl;
                break;
            }
            default: {
                std::cout << "\nPlease introduce a valid option:" << std::endl;
            }
        }
    }
    return (0);
}


