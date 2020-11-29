#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_FILE "unix_socket"

int onError(const char* err, int socket_fd)
{
	if (socket_fd != -1)
		close(socket_fd);
	std::cerr << "TraceLog: server: "<< err << std::endl;
	return (-1);
}

int main(void)
{
	int socket_fd = -1;
	int fd;
	size_t size;
	char buffer[256];
	struct sockaddr_un addr = { 0 }; // 0 init.

	if ((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		return (onError("socket_fd != 0", socket_fd));
	addr.sun_family = AF_UNIX; // Fixed.
	strcpy(addr.sun_path, SOCKET_FILE); // Common socket file.
	remove(addr.sun_path);
	if (bind(socket_fd, (struct sockaddr*) &addr, sizeof(struct sockaddr_un)) != 0)
		return (onError("bind failed.", socket_fd));
	if (listen(socket_fd, 1) != 0)
		return (onError("listen failed.", socket_fd));
	while(1)
	{
		if ((fd = accept(socket_fd, NULL, NULL)) == -1)
			return (onError("accept failed.", socket_fd));
		while((size = read(fd, buffer, sizeof(buffer) - 1)))
		{
			if (size == -1)
				return (onError("read failed.", socket_fd));
			buffer[size] = '\0';
			std::cout << "Received: " << buffer << std::endl;
		}
		close(fd);
	}
	close(socket_fd);
	std::cout << "The Server is Terminated" << std::endl;
	return 0;
}

