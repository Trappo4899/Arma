#pragma once

class ActionMap
{
private:

	struct action_map_t
	{
		union
		{
			DEFINE_MEMBER_N(UINT32, ActionID, 0x48);
		};
	};

private:

	Address m_address;
	action_map_t m_data;

public:

	ActionMap();
	ActionMap(Address address);

public:

	UINT32 GetActionID();

};