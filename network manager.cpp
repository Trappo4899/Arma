#include "includes.h"

NetworkManager::NetworkManager()
{
    m_address = nullptr;
}

NetworkManager::NetworkManager(Address address)
{
    m_address = address;
    m_data = m_address.at<network_mgr_t>();
}

Address NetworkManager::GetAddress()
{
    return m_address;
}

NetworkClient NetworkManager::GetNetworkClient()
{
    return NetworkClient(m_address.at(Offsets::NetworkManager::NetworkClient));
}

NetworkClient::NetworkClient()
{
    m_address = nullptr;
    m_data = { };
}

NetworkClient::NetworkClient(Address address)
{
    m_address = address;
    m_data = { };

    if (m_address)
    {
        m_data = m_address.at<network_client_t>();

        map_name = g_pDriver->ReadString(m_address.at<UINT64>(Offsets::NetworkClient::MapName));
        mission_name = g_pDriver->ReadString(m_address.at<UINT64>(Offsets::NetworkClient::MissionName));

        std::vector<PlayerIdentity> player_identity_buffer = { };

        Address player_idents = m_address.at(Offsets::NetworkClient::PlayerIdentities);

        for (int i = 0; i < m_data.player_identities_size; i++)
        {
            player_identity_buffer.push_back(PlayerIdentity(player_idents.as(i * 0x2F8)));
        }

        player_identities = player_identity_buffer;
    }
}

PlayerIdentity NetworkClient::GetPlayerIdentity(UINT32 NetworkID)
{
    for (auto curr_identity : player_identities)
    {
        if (curr_identity.GetNetworkID() == NetworkID)
        {
            return curr_identity;
        }
    }

    return PlayerIdentity();
}

std::string NetworkClient::GetMapName()
{
    return map_name;
}

std::string NetworkClient::GetMissionName()
{
    return mission_name;
}

PlayerIdentity::PlayerIdentity()
{
    m_address = nullptr;
    m_data = { };
}

PlayerIdentity::PlayerIdentity(Address address)
{
    m_address = address;
    m_data = { };

    if (m_address)
    {
        m_data = m_address.at<player_identity_t>();

        name = g_pDriver->ReadString(m_address.at<UINT64>(Offsets::PlayerIdentity::Name));
    }
}

UINT32 PlayerIdentity::GetNetworkID()
{
    return m_data.network_id;
}

std::string PlayerIdentity::GetName()
{
    return name;
}

UINT64 PlayerIdentity::GetSteamID()
{
    return m_data.steam_id_1;
}
