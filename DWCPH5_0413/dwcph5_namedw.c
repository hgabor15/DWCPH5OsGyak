// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
  
int main()
{
    int fd;
  
    // FIFO file path
    char * DWCPH5 = "/tmp/DWCPH5";
  
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(DWCPH5, 0666);
  
    char arr1[80], arr2[80];
    while (1)
    {
        // Open FIFO for write only
        fd = open(DWCPH5, O_WRONLY);
  
        // Take an input arr2ing from user.
        // 80 is maximum length
        fgets(arr2, 80, stdin);
  
        // Write the input arr2ing on FIFO
        // and close it
        write(fd, arr2, strlen(arr2)+1);
        close(fd);
  
        // Open FIFO for Read only
        fd = open(DWCPH5, O_RDONLY);
  
        // Read from FIFO
        read(fd, arr1, sizeof(arr1));
  
        // Print the read message
        printf("User2: %s\n", arr1);
        close(fd);
    }
    return 0;
}
