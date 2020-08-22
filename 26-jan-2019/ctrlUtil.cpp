#include <iostream>
#include <linux/cdrom.h>
#include <sys/ioctl.h>
#include <string.h>
#include "ctrlUtil.h"

// Function to determine the tray position
void tPosition(int fd) {
	int slot = 0;
	int ret = ioctl(fd, CDROM_DRIVE_STATUS, slot);

	switch (ret) {
		case CDS_NO_INFO: {
			std::cout << "No information\n";
			break;
		}
		case CDS_NO_DISC: {
			std::cout << "No disc\n";
			break;
		}
		case CDS_TRAY_OPEN: {
			std::cout << "Tray is open\n";
			break;
		}
		case CDS_DRIVE_NOT_READY: {
			std::cout << "Drive not ready\n";
			break;
		}
		case CDS_DISC_OK: {
			std::cout << "Disk Ok\n";
			break;
		}
		case -1: {
			std::cout << strerror(errno) << std::endl;
			break;
		}
		default: {
			std::cout << "Unexpected error\n";
		}
	}
}

// Function to eject the CDROM tray
void ejectTray(int fd) {
	int err = 0;
	err = ioctl(fd, CDROMEJECT, 0);
	if (err < 0) {
		std::cout << strerror(errno) << std::endl;
	}
}

// Function to close the CDROM tray
void closeTray(int fd) {
	int err = ioctl(fd, CDROMCLOSETRAY, 0);
        if (err < 0) {
		std::cout << strerror(errno) << std::endl;
        }
}
