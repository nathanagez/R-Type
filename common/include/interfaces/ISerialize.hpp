#ifndef _ISERIALIZE_H
#define _ISERIALIZE_H

#include "IPackets.hpp"
#include <string>

class ISerialize
{
public:
	virtual void serialize(char *buffer, std::string const args...) = 0;
	virtual void deserialize(char *buffer, void *stru, std::string const &type) = 0;
	virtual ~ISerialize(){};
};

#endif
