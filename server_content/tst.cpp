#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int
main(void)
{
	int fd = open("helloworld.txt///", O_RDONLY);
	std::cout << "fd: " << fd << '\n';
	close(fd);
	return 0;
}
