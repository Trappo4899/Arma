#pragma once

class Camera
{
private:

	struct camera_t
	{
		union
		{
			DEFINE_MEMBER_N(Matrix3x3, Viewmatrix, 0x8);
			DEFINE_MEMBER_N(Vector3, Position, 0x2C);
			DEFINE_MEMBER_N(Vector2, ScreenCenter, 0x58);
			DEFINE_MEMBER_N(Matrix3x3, Projection, 0xD0);
			DEFINE_MEMBER_N(FLOAT, ZoomMultiplier, 0x70);
		};

		camera_t()
		{

		}
	};

private:

	Address m_address;
	camera_t m_data;

public:

	Camera();
	Camera(Address address);

public:

	void Update();

	Address GetAddress();

public:

	Vector3 GetPosition();

	bool WorldToScreen(Vector3 world, Vector2& screen);

	float GetZoomMultiplier();
};