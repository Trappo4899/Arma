#include "includes.h"

Matrix3x3::Matrix3x3()
{
	m_mat[0] = { };
	m_mat[1] = { };
	m_mat[2] = { };
}

Matrix3x3::Matrix3x3(Vector3 x, Vector3 y, Vector3 z)
{
	m_mat[0] = x;
	m_mat[1] = y;
	m_mat[2] = z;
}

Vector3 Matrix3x3::operator[](int idx)
{
	return m_mat[idx];
}

float Math::deg_to_rad(float rad)
{
	return (rad * (PI / 180.f));
}

float Math::rad_to_deg(float rad)
{
	return ((rad * 180.f) / PI);
}

Vector3 Math::model_to_world(Vector3 model, Matrix3x3 rotation, Vector3 position)
{
	Vector3 out = { };

	out.x = model.Dot(rotation[0]) + position.x;
	out.y = model.Dot(rotation[1]) + position.y;
	out.z = model.Dot(rotation[2]) + position.z;

	return out;
}

float Math::length(Vector3 vec)
{
	return sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

Matrix3x3 Math::transpose(Matrix3x3 mat)
{
	Matrix3x3 t = { };

	t.m_mat[0].x = mat.m_mat[0].x;
	t.m_mat[0].y = mat.m_mat[1].x;
	t.m_mat[0].z = mat.m_mat[2].x;
	t.m_mat[1].x = mat.m_mat[0].y;
	t.m_mat[1].y = mat.m_mat[1].y;
	t.m_mat[1].z = mat.m_mat[2].y;
	t.m_mat[2].x = mat.m_mat[0].z;
	t.m_mat[2].y = mat.m_mat[1].z;
	t.m_mat[2].z = mat.m_mat[2].z;

	return t;
}

std::pair<int, int> Math::get_fraction(float ratio)
{
	/* chat gpt */

	const int precision = 1000000;
	int denominator = precision;

	int numerator = static_cast<int>(ratio * denominator + 0.5);

	int gcf = std::gcd(numerator, denominator);

	numerator /= gcf;
	denominator /= gcf;

	return { numerator, denominator };
}
