#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void)
{
    const char *msg = "Hello World\n";

    // int pid = fork();
    /* -------- write() -------- */
    int fd = open("write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // int fd = open("write.txt", O_WRONLY | O_CREAT | O_APPEND , 0644);
    write(fd, msg, strlen(msg));
    // printf("%d sleep 10 seconds\n", getpid());
    // sleep(10);
    // printf("%d close fd\n", getpid());
    close(fd);

    /* -------- fwrite() -------- */
    FILE *fp = fopen("fwrite.txt", "w");
    fwrite(msg, 1, strlen(msg), fp);
    // fflush(fp);
    // printf("%d sleep 10 seconds\n", getpid());
    // sleep(10);
    // printf("%d close fp\n", getpid());
    fclose(fp);

    return 0;
}
