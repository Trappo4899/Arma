#pragma once

class EntityList
{
public:

	std::vector<Entity> m_entities;
	std::vector<Entity> m_entities_waiting;

	std::vector<Vehicle> m_vehicles;
	std::vector<Vehicle> m_vehicles_waiting;

public:

	EntityList();

private:

	Entity init_entity(A3Entity entity);
	Vehicle init_vehicle(A3Entity vehicle);

	ImColor get_entity_colour(Entity& ent);

public:

	void SlowUpdate();
	void FastUpdate();

	const std::vector<Entity>& Get();
};