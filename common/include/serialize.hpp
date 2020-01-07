#include "interfaces/ISerialize.hpp"

class Serialize : public ISerialize
{
public:
	void serialize(char *buffer, std::string const args...);
	void deserialize(char *buffer, void *stru, std::string const &type);
};
