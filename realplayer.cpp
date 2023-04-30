#include "includes.h"

RealPlayer::RealPlayer()
{
    m_address = nullptr;
    m_data = { };
}

RealPlayer::RealPlayer(Address address)
{
    m_address = address;
    m_data = m_address.at<real_player_t>();
}

void RealPlayer::Update()
{
    m_data = m_address.at<real_player_t>();
}

Address RealPlayer::GetAddress()
{
    return m_address;
}

CameraAngles RealPlayer::GetCameraAngles()
{
    return CameraAngles(m_address.at(Offsets::RealPlayer::CameraAngles));
}