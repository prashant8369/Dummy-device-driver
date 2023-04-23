#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buf[1024];

    fd = open("/dev/dummy", O_RDWR);
    if (fd < 0)
    {
        perror("Failed to open dummy device");
        exit(1);
    }

    printf("Enter a message to send to the dummy driver:\n");
    scanf("%[^\n]%*c", buf);

    if (write(fd, buf, sizeof(buf)) < 0)
    {
        perror("Failed to write to dummy device");
        exit(1);
    }

    printf("Press ENTER to read back from the dummy driver\n");
    getchar();

    if (read(fd, buf, sizeof(buf)) < 0)
    {
        perror("Failed to read from dummy device");
        exit(1);
    }

    printf("Message received from the dummy driver: %s\n", buf);

    close(fd);

    return 0;
}
