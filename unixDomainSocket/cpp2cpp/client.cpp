#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_FILE "unix_socket"
#define MESSAGE "HELLO WORLD !"

int onError(const char* err, int socket_fd)
{
	if (socket_fd != -1)
		close(socket_fd);
	std::cerr << "TraceLog: server: "<< err << std::endl;
	return (-1);
}

int main(void)
{
	int		err(0);
	int		socket_fd(-1);
	int		cnt(0);
	size_t	res;
	char	rbuf[256];
	struct	sockaddr_un addr = {0};

	if ((socket_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		return (onError("socket_fd != 0", socket_fd));
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, SOCKET_FILE);
	if (connect(socket_fd, (struct sockaddr*) &addr, sizeof(struct sockaddr_un)) != 0)
		return (onError("connect failed.", socket_fd));
	while (cnt < 5)
	{
		if (write(socket_fd, MESSAGE, strlen(MESSAGE)) == -1)
			return (onError("write failed.", socket_fd));
		if ((res = read(socket_fd, rbuf, sizeof(rbuf))) == 0)
		  break ;
		if (res == -1)
			return (onError("write failed.", socket_fd));
		rbuf[res] = '\0';
		std::cout << rbuf << std::endl;
		cnt++;
	}
	close(socket_fd);
	return (0);
}
