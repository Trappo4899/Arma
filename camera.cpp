#include "includes.h"

Camera::Camera()
{
	m_address = nullptr;
	m_data = { };
}

Camera::Camera(Address address)
{
	m_address = address;
	m_data = m_address.at<camera_t>();
}

void Camera::Update()
{
	m_data = m_address.at<camera_t>();
}

Address Camera::GetAddress()
{
	return Address();
}

Vector3 Camera::GetPosition()
{
	return m_data.Position;
}

bool Camera::WorldToScreen(Vector3 world, Vector2& screen)
{
	bool return_value = true;

	auto relative = world - m_data.Position;

	auto x = relative.Dot(m_data.Viewmatrix[0]); /*	aside		*/
	auto y = relative.Dot(m_data.Viewmatrix[1]); /*	up			*/
	auto z = relative.Dot(m_data.Viewmatrix[2]); /*	direction	*/

	/* make sure the entity we are rendering on isnt behind us */
	if (z < 0.1f)
	{
		return_value = false; /* dont return here because of some use cases were we might still want to get the 2d space of an 
									object that isnt on our screen */
	}

	/* translate to camera space */
	Vector3 ndc = { };

	ndc.x = ((x / z) / m_data.Projection[0].x);
	ndc.y = ((y / z) / m_data.Projection[1].y);

	/* if confused use this to visualize */
	//printf("[X] %f\n", x);
	//printf("[Y] %f\n", y);
	//printf("----------------\n");
	//printf("[X / Z] %f\n", x / z);
	//printf("[Y / Z] %f\n", y / z);
	//printf("----------------\n");
	//printf("[X / P / Z] %f\n", x / m_data.Projection[0].x / z);
	//printf("[Y / P / Z] %f\n", y / m_data.Projection[1].y / z);
	//printf("----------------\n");
	//printf("[1 + X / P / Z] %f\n", (1 + (ndc.x)));
	//printf("[1 - Y / P / Z] %f\n", (1 - (ndc.y)));
	//printf("----------------\n");
	//printf("[SCREEN-X] %f\n", m_data.ScreenCenter.x);
	//printf("[SCREEN-Y] %f\n", m_data.ScreenCenter.y);
	//printf("----------------\n");
	//printf("[RESULT] %f\n", (m_data.ScreenCenter.x * (1 + (ndc.x))));
	//printf("[RESULT] %f\n\n\n\n", (m_data.ScreenCenter.y * (1 - (ndc.y))));

	/* map position id 2d space */
	screen.x = (m_data.ScreenCenter.x * (1.f + (ndc.x)));
	screen.y = (m_data.ScreenCenter.y * (1.f - (ndc.y)));

	return return_value;
}

float Camera::GetZoomMultiplier()
{
	return m_data.ZoomMultiplier;
}
