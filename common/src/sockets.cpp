#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include "sockets.hpp"

// Client socket
Sockets::Sockets(std::string const &ip, int port, std::string const &socket_type)
{
#if defined(_WIN32)
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
#endif
	m_socketType = (socket_type == "UDP" ? SOCK_DGRAM : SOCK_STREAM); // UDP or TCP
	m_sin.sin_addr.s_addr = inet_addr(ip.c_str());					  // HOST IP | INADDR_ANY means any ip addresses
	m_sin.sin_family = AF_INET;										  // Always AF_INET
	m_sin.sin_port = htons(port);									  // Port number

	// CREATE SOCKET HERE with socket() - http://manpagesfr.free.fr/man/man7/ip.7.html
	try
	{
		if ((m_socket = socket(PF_INET, m_socketType, 0)) == -1)
			throw std::strerror(errno);
		std::cout << "Client socket created" << std::endl;
		if (m_socketType == SOCK_STREAM) {
			::connect(m_socket, (sockaddr *)&m_sin, sizeof(m_sin));
		}
	}
	catch (const char *exception)
	{
		std::cerr << "Error [Client Socket Creation]: " << exception << std::endl;
	}
}

// Server socket
Sockets::Sockets(int port, int limit, std::string const &socket_type)
{
#if defined(_WIN32)
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 2), &WSAData);
#endif
	m_socketType = (socket_type == "UDP" ? SOCK_DGRAM : SOCK_STREAM); // UDP or TCP
	m_sin.sin_addr.s_addr = htonl(INADDR_ANY);						  // HOST IP | INADDR_ANY means any ip addresses
	m_sin.sin_family = AF_INET;										  // Always AF_INET
	m_sin.sin_port = htons(port);									  // Port number

	try
	{
		if ((m_socket = socket(PF_INET, m_socketType, 0)) == -1)
			throw std::strerror(errno);
		bind();							// Assing socket addr
		if (m_socketType != SOCK_DGRAM) // If Server is TCP mode
			listen(limit);				// Listen for clients
		else
			std::cout << "[UDP] Socket created" << std::endl;
	}
	catch (const char *exception)
	{
		std::cerr << "Error [Server Socket Creation]: " << exception << '\n';
	}
}

// Constructor used for new clients socket
Sockets::Sockets(int socket_ref, struct sockaddr_in const &client_sin, std::string const &ip)
	: m_socket(socket_ref), m_sin(client_sin), m_ip(ip){};

// https://stackoverflow.com/questions/27014955/socket-connect-vs-bind
void Sockets::bind()
{
	try
	{
		if (::bind(m_socket, (sockaddr *)&m_sin, sizeof(m_sin)) == -1)
			throw std::strerror(errno);
		std::cout << (m_socketType == SOCK_STREAM ? "[TCP] " : "[UDP] ") << "Socket bind" << std::endl;
	}
	catch (const char *exception)
	{
		std::cerr << "Error [bind]: " << exception << std::endl;
	}
}

void Sockets::listen(int limit)
{
	std::cout << "[TCP] Socket created" << std::endl;
	try
	{
		if (::listen(m_socket, limit) == -1) // Limit maximal connection to 4 clients
			throw std::strerror(errno);
		std::cout << "[TCP] Listening..." << std::endl;
	}
	catch (const char *exception)
	{
		std::cerr << "Error [listen]: " << exception << std::endl;
	}
}

std::string Sockets::getAddress(const sockaddr_in &addr)
{
	char buff[INET6_ADDRSTRLEN] = {0};
	return inet_ntop(addr.sin_family, (void *)&(addr.sin_addr), buff, INET6_ADDRSTRLEN);
}

int Sockets::getSocket()
{
	return m_socket;
}

int Sockets::accept(sockaddr_in &from, socklen_t &addrlen)
{
	return ::accept(m_socket, (struct sockaddr *)(&from), &addrlen);
}

std::string Sockets::recv(int len)
{
	char *buffer = new char[len];
	int size;

	if (m_socketType == SOCK_DGRAM) // If UDP
	{
		socklen_t client_sin_size = sizeof(m_client_socket);
		try
		{
			if ((size = ::recvfrom(m_socket, buffer, len, 0, (struct sockaddr *)&m_client_socket, &client_sin_size)) == -1)
				throw std::strerror(errno);

			char buff[INET6_ADDRSTRLEN] = {0};
			std::string clientAddress = inet_ntop(m_client_socket.sin_family, (void *)&(m_client_socket.sin_addr), buff, INET6_ADDRSTRLEN);
			std::cout << "[UDP] from " << clientAddress.c_str() << std::endl;
		}
		catch (const char *exception)
		{
			std::cerr << "Error [UDP Receive]: " << exception << '\n';
		}
	}
	else // if TCP
	{
		try
		{
			if ((size = ::read(m_socket, buffer, len)) == -1)
				throw std::strerror(errno);
		}
		catch (const char *exception)
		{
			std::cerr << "Error [TCP Receive]: " << exception << '\n';
		}
	}

	std::string data(buffer, size);
	return (data);
}

void Sockets::send(const std::string &data)
{
	if (m_socketType == SOCK_DGRAM)
	{
		try
		{
			socklen_t to_client_size = sizeof(m_sin);

			::sendto(m_socket, data.c_str(), data.size(), 0, (struct sockaddr *)&m_sin, to_client_size);

			std::cout << "Sent" << std::endl;
		}
		catch (const char *exception)
		{
			std::cerr << "Error [UDP Send]: " << exception << '\n';
		}
	}
	else
	{
		try
		{
			if ((::send(m_socket, data.c_str(), data.size(), 0)) == -1)
				throw std::strerror(errno);
		}
		catch (const char *exception)
		{
			std::cerr << "Error [TCP Send]: " << exception << '\n';
		}
	}
}

void Sockets::send(char *buffer, size_t size)
{
	if (m_socketType == SOCK_DGRAM)
	{
		try
		{
			socklen_t to_client_size = sizeof(m_sin);

			ssize_t pute = ::sendto(m_socket, buffer, size, 0, (struct sockaddr *)&m_sin, to_client_size);

			std::cout << "Sent " << pute << "\n" << std::endl;
		}
		catch (const char *exception)
		{
			std::cerr << "Error [UDP Send]: " << exception << '\n';
		}
	}
	else
	{
		try
		{
			std::cout << "BUFFER SIZE: " << size << std::endl;
			if ((::send(m_socket, buffer, size, 0)) == -1)
				throw std::strerror(errno);
		}
		catch (const char *exception)
		{
			std::cerr << "Error [TCP Send]: " << exception << '\n';
		}
	}
}

const std::string Sockets::getIp()
{
	return m_ip;
}

Sockets::~Sockets()
{
	try
	{
		if (close(m_socket) == -1)
			throw std::strerror(errno);
		std::cout << "Socket Close" << std::endl;
	}
	catch (const char *exception)
	{
		std::cerr << "Error [destructor]: " << exception << '\n';
	}
#if defined(_WIN32)
	WSACleanup();
#endif
}
