#pragma once

class CameraAngles
{
private:

	struct camera_angles_t
	{
		union
		{
			DEFINE_MEMBER_N(Vector2, Viewangles, 0x4);
			DEFINE_MEMBER_N(Vector2, FreelookAngles, 0x10);
		};

		camera_angles_t()
		{

		}
	};

private:

	Address m_address;
	camera_angles_t m_data;

public:

	CameraAngles();
	CameraAngles(Address address);

public:

	void Update();

	Address GetAddress();

	Vector2 GetViewangles();
	Vector2 GetFreelookAngles();

	void SetPitch(float pitch);
	void SetViewangles(Vector2 va);
	void SetFreelookAngles(Vector2 va);
};