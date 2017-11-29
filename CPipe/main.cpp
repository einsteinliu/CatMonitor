#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
    int fd;
    char* myfifo = "/pipes/mypipe";
    int result = mkfifo(myfifo,0666);
    fd = open(myfifo,O_WRONLY);
    write(fd,"hello world\n",sizeof("hellow world\n"));
    close(fd);
    unlink(myfifo);
    cout<<"hello word\n";
    return 1;
}
