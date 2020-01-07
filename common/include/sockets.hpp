#ifndef _SOCKETS_H
#define _SOCKETS_H

#if defined(_WIN32)
#include <winsock2.h>
#elif defined(__linux__) || defined(__APPLE__)
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include <string>
#include <fcntl.h>
#include "interfaces/ISockets.hpp"

class Sockets : public ISockets
{
public:
	Sockets(std::string const &ip, int port, std::string const &type = "UDP");
	Sockets(int port, int queue_limit = 4, std::string const &type = "UDP");
	Sockets(int socket_ref, struct sockaddr_in const &client_sin, std::string const &ip);

	int accept(sockaddr_in &from, socklen_t &addrlen);
	int getSocket();
	void send(const std::string &);
	void send(char *buffer, size_t size);
	const std::string getIp();
	std::string getAddress(const sockaddr_in &addr);
	std::string recv(int);
	~Sockets();

private:
	int m_socket;						// Return value of socket()
	int m_socketType;					// UDP: SOCK_DGRAM or TCP: SOCK_DGRAM
	struct sockaddr_in m_sin;			// Socket struct
	struct sockaddr_in m_client_socket; // Client socket
	const std::string m_ip;				// Client IP
	void bind();						// Bind Socket
	void listen(int);					// Listen for clients (TCP only)
};
#endif
