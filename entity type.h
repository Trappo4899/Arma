#ifndef ENTITY_TYPE_H
#define ENTITY_TYPE_H

#include "movestype.h"

class EntityType : public BaseClass
{
private:

	struct entity_type_t
	{
		std::string name;
		std::string path;
		std::string className;
		std::string print;
		std::string type;
	};

private:

	Address m_address;
	entity_type_t m_data;

public:

	EntityType();
	EntityType(Address address);

public:

	std::string GetName();
	std::string GetPath();
	std::string GetClass();
	std::string GetPrint();
	std::string GetType();

	MovesType GetMovesType();

public:

	bool IsPlayer();
	bool IsVehicle();
	bool IsWildlife();
};

#endif