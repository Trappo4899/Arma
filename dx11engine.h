#pragma once

class DX11Engine
{
private:

	struct dx11_engine_t
	{
		union
		{
			DEFINE_MEMBER_N(INT32, ScreenWidth, 0xC4);
			DEFINE_MEMBER_N(INT32, ScreenHeight, 0xC8);
			DEFINE_MEMBER_N(float, FovTop, 0x9C);
			DEFINE_MEMBER_N(float, FovLeft, 0xA0);
		};
	};

private:

	Address m_address;
	dx11_engine_t m_data;

public:

	DX11Engine();
	DX11Engine(Address address);

public:

	void Update();

	Address GetAddress();

	void SetFov(float width, float height, float Fov);
	float GetFov();

	INT32 GetScreenWidth();
	INT32 GetScreenHeight();

public:

	void Handle();
};