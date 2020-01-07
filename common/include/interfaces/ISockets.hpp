#ifndef _ISOCKETS_H
#define _ISOCKETS_H

#include <iostream>
#include <cstring>
#include <sstream>
#include <memory>
#include <netinet/in.h>

class ISockets
{
public:

    virtual int accept(sockaddr_in &from, socklen_t &addrlen) = 0;
    virtual std::string recv(int) = 0;
    virtual void send(const std::string &) = 0;
	virtual const std::string getIp() = 0;
	virtual std::string getAddress(const sockaddr_in &addr) = 0;
	virtual int getSocket() = 0;
    virtual ~ISockets(){};
private:
    virtual void bind() = 0;
    virtual void listen(int) = 0;
};
#endif
