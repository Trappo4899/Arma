#pragma once

#include "camera angles.h"

class RealPlayer
{
private:

	struct real_player_t
	{
		union
		{
			
		};

		real_player_t()
		{

		}
	};

private:

	Address m_address;
	real_player_t m_data;

public:

	RealPlayer();
	RealPlayer(Address address);

public:

	void Update();

	Address GetAddress();

	CameraAngles GetCameraAngles();
};