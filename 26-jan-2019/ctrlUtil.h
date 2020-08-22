#pragma once

// Function to determine the tray position
void tPosition(int fd);

// Function to eject the CDROM tray
void ejectTray(int fd);

// Function to close the CDROM tray
void closeTray(int fd);
