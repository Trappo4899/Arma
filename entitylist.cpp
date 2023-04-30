#include "includes.h"

EntityList::EntityList()
{
	m_entities = { };
}

Entity EntityList::init_entity(A3Entity entity)
{
	Entity ent = { };

	ent.m_entity = entity;

	ent.m_is_ai = ent.m_entity.GetNetworkID() == 1;

	if (!ent.m_is_ai)
	{
		ent.m_player_identity = g_pClient->m_network_manager.GetNetworkClient().GetPlayerIdentity(ent.m_entity.GetNetworkID());
	}

	ent.m_color = get_entity_colour(ent);

	return ent;
}

Vehicle EntityList::init_vehicle(A3Entity vehicle)
{
	Vehicle veh = { };

	veh.m_vehicle = A3Vehicle(vehicle.GetAddress());

	veh.m_driver = init_entity(veh.m_vehicle.GetDriver());

	if (get_entity_colour(veh.m_driver) != ImColor(150, 150, 150, 175))
	{
		veh.m_color = ImColor(230, 117, 78, 175);
	}
	else
	{
		veh.m_color = ImColor(150, 150, 150, 175);
	}

	veh.m_inactive = false;

	if (!veh.m_driver.m_entity.GetAddress() || veh.m_driver.m_entity.IsDead())
	{
		veh.m_inactive = true;
	}

	return veh;
}

ImColor EntityList::get_entity_colour(Entity& ent)
{
	ImColor retCol = { };

	switch (ent.m_entity.GetTeam())
	{
	case 0:		// opfor
		retCol = ImColor(213, 82, 82, 255);
		break;

	case 1:		// blufor
		retCol = ImColor(136, 181, 255, 255);
		break;

	case 2:		// independant
		retCol = ImColor(83, 200, 81, 255);
		break;

	case 3:		// civ
		retCol = ImColor(223, 87, 205, 255);
		break;
	}

	if (ent.m_is_ai)
	{
		retCol = ImColor(254, 193, 214, 200);
	}

	if (!ent.m_entity.GetAddress() || ent.m_entity.IsDead())
	{
		retCol = ImColor(150, 150, 150, 175);
	}

	return retCol;
}

void EntityList::SlowUpdate()
{
	std::vector<Entity> ents = { };
	std::vector<Vehicle> vehicles = { };

	for (auto& e : g_pClient->m_world.GetEntities())
	{
		auto type = e.GetEntityType();

		if (type.IsPlayer())
		{
			Entity ent = init_entity(e);

			ent.m_entity_type = type;

			ents.emplace_back(ent);
		}
		else if (type.IsVehicle())
		{
			Vehicle veh = init_vehicle(e);

			veh.m_entity_type = type;

			vehicles.emplace_back(veh);
		}
		//else if (type.IsWildlife())
		//{
		//	continue;

		//	Entity ent = init_entity(e);

		//	ent.m_entity_type = type;

		//	ents.emplace_back(ent);
		//}
		else
		{
			continue;
		}
    }

	m_entities_waiting = ents;
	m_vehicles_waiting = vehicles;
}

void EntityList::FastUpdate()
{

	std::vector<Entity> ents = m_entities_waiting;
	std::vector<Entity> ents_buffer = { };

	for (auto& e : ents)
	{
		if (e.Update())
		{
			ents_buffer.push_back(e);
		}
	}

	m_entities = ents_buffer;



	std::vector<Vehicle> vehicles = m_vehicles_waiting;
	std::vector<Vehicle> vehicles_buffer = { };

	for (auto& v : vehicles)
	{
		if (v.Update())
		{
			vehicles_buffer.push_back(v);
		}
	}

	m_vehicles = vehicles_buffer;

}

const std::vector<Entity>& EntityList::Get()
{
    return m_entities;
}