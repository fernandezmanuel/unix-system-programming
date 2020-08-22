// Title:  Memory Usage Monitoring 
// Author: Manuel Fernandez
// Date:   Jan 21, 2019
// Run:    ./mainprog /proc
///////////////////////////////////////////////////////////////////////
// Description: Scans and displays a report of running processes using 
// more than 10Mbytes of resident memory.
///////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    struct dirent *de = NULL;
    DIR *d = NULL;
    
    // Displays an error message if there are not enough input parameters
    if (argc != 2) {
        fprintf(stderr, "Usage: %s dirname\n", argv[0]);
        return(1);
    }
    
    // Opens the directory using the input argument
    d = opendir(argv[1]);
    
    if (d == NULL) {
        perror("Couldn't open directory");
        return(2);
    }
    
    // Loop while not NULL
    while (de = readdir(d)) {
        
        // Verifies that each directory name is a digit
        if (isdigit(de->d_name[0])) {
            char directory[40] = "/proc/";
            strcat(directory, de->d_name);
            strcat(directory, "/status");
            
            // Opens directory
            FILE* fp = fopen(directory, "r");
            
            // Variables needed to find rows within the status file
            char name[15] = "Name:";
            char pid[15] = "Pid:";
            char memo[15] = "VmRSS:";
            
            // Variables need to store row values
            char str[230] = "\0";
            char line[50] = "\0";
            int res_mem = 0;
            int id = 0;
            
            // Scans and compares every line in the status file with the declared variables
            // in order to find, store, and display the requested rows and values to the screen.
            if (fp != NULL) {
                while (fscanf(fp, "%s %s", line, str) != EOF) {
                    if (strncmp(line, name, 5) == 0) { // Finds Name
                        while (fscanf(fp, "%s %d", line, &id) != EOF) {
                            if (strncmp(line, pid, 2) == 0) { // Finds Pid
                                while (fscanf(fp, "%s %d", line, &res_mem) != EOF) {
                                    if (strncmp(line, memo, 3) == 0 && res_mem > 10000) { // Finds RM
                                        printf(" Name: %-16s | Pid: %-4d | Resident Memory: %-18d\n", str, id, res_mem);
                                    }
                                }
                            }
                        }
                    }
                }
                fclose(fp);
            } else {
                printf("Failed to open file\n");
            }
        }
    }
    closedir(d);
    return(0);
}
