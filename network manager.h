#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

class PlayerIdentity : public BaseClass
{
private:

	std::string name;

	struct player_identity_t
	{
		union
		{
			DEFINE_MEMBER_N(UINT32, network_id, 0x8);
			DEFINE_MEMBER_N(UINT64, steam_id_1, 0x18);
			DEFINE_MEMBER_N(UINT64, steam_id_2, 0xD0);
			DEFINE_MEMBER_N(UINT64, steam_id_3, 0xD8);
		};
	};

private:

	Address m_address;
	player_identity_t m_data;

public:

	PlayerIdentity();
	PlayerIdentity(Address address);

public:

	UINT32 GetNetworkID();
	std::string GetName();
	UINT64 GetSteamID();
};

class NetworkClient : public BaseClass
{
private:

	std::vector<PlayerIdentity> player_identities;
	std::string map_name;
	std::string mission_name;

	struct network_client_t
	{
		union
		{
			DEFINE_MEMBER_N(UINT32, player_identities_size, 0x40);
		};
	};

private:

	Address m_address;
	network_client_t m_data;

public:

	NetworkClient();
	NetworkClient(Address address);

public:

	PlayerIdentity GetPlayerIdentity(UINT32 NetworkID);

	std::string GetMapName();
	std::string GetMissionName();
};

class NetworkManager : public BaseClass
{
private:

	struct network_mgr_t
	{
		union
		{

		};
	};

private:

	Address m_address;
	network_mgr_t m_data;

public:

	NetworkManager();
	NetworkManager(Address address);

public:

	Address GetAddress();

public:

	NetworkClient GetNetworkClient();
};

#endif