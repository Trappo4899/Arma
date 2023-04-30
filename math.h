#ifndef MATH_H
#define MATH_H

#define PI std::numbers::pi_v<float>
#define G_CONST 9.8066f

class Vector2
{
public:

	float x, y;

public:

	Vector2()
	{
		x = 0.f;
		y = 0.f;
	}

	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vector2 operator*(Vector2 vec)
	{
		return {
			x * vec.x,
			y * vec.y
		};
	}

	Vector2 operator*(float vec)
	{
		return {
			x * vec,
			y * vec
		};
	}

	Vector2 operator+(Vector2 vec)
	{
		return {
			x + vec.x,
			y + vec.y
		};
	}

	Vector2 operator+(float vec)
	{
		return {
			x + vec,
			y + vec
		};
	}

	void print()
	{
		printf("%f | %f \n", x, y);
	}

	float size()
	{
		return sqrtf((
			powf(x, 2) +
			powf(y, 2)
			));
	}
};

class Vector3
{
public:

	float x, y, z;

	Vector3()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3 operator*(Vector3 vec)
	{
		return {
			x * vec.x,
			y * vec.y,
			z * vec.z
		};
	}

	Vector3 operator*(float vec)
	{
		return {
			x * vec,
			y * vec,
			z * vec
		};
	}

	Vector3 operator-(Vector3 vec)
	{
		return {
			x - vec.x,
			y - vec.y,
			z - vec.z
		};
	}

	Vector3 operator+(Vector3 vec)
	{
		return {
			x + vec.x,
			y + vec.y,
			z + vec.z
		};
	}

	Vector3 operator+(float vec)
	{
		return {
			x + vec,
			y + vec,
			z + vec
		};
	}

	Vector3 operator/(Vector3 vec)
	{
		return {
			x / vec.x,
			y / vec.y,
			z / vec.z
		};
	}

	Vector3 operator/(float vec)
	{
		return {
			x / vec,
			y / vec,
			z / vec
		};
	}

	bool operator==(Vector3 vec)
	{
		return {
			x == vec.x &&
			y == vec.y &&
			z == vec.z
		};
	}

	bool operator==(float vec)
	{
		return {
			x == vec &&
			y == vec &&
			z == vec
		};
	}

	float Dot(Vector3 vec)
	{
		return ((x * vec.x) + (y * vec.y) + (z * vec.z));
	}

	float Distance(Vector3 vec)
	{
		return sqrtf(( 
			powf(x - vec.x, 2) +
			powf(y - vec.y, 2) +
			powf(z - vec.z, 2)
			));
	}

	bool Zero()
	{
		return (x == 0.f || y == 0.f || z == 0.f);
	}

	void Normalize()
	{
		float magnitude = sqrtf(this->Dot(*this));

		*this = *this / magnitude;
	}

	void print()
	{
		printf("%f | %f | %f\n", x, y, z);
	}

	float size()
	{
		return sqrtf((
			powf(x, 2) +
			powf(y, 2) +
			powf(z, 2)
			));
	}
};

class Vector4
{
public:

	float x, y, z, w;

	Vector4()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
		w = 0.f;
	}

	Vector4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
};

class Box
{
public:

	int x, y, w, h;
};

class Matrix3x3
{
public:

	Vector3 m_mat[3];

public:

	Matrix3x3();
	Matrix3x3(Vector3 x, Vector3 y, Vector3 z);

	Vector3 operator[](int idx);

	Vector3 operator*(const Vector3& v) const
	{
		Vector3 result;
		result.x = m_mat[0].x * v.x + m_mat[1].x * v.y + m_mat[2].x * v.z;
		result.y = m_mat[0].y * v.x + m_mat[1].y * v.y + m_mat[2].y * v.z;
		result.z = m_mat[0].z * v.x + m_mat[1].z * v.y + m_mat[2].z * v.z;
		return result;
	}

	static Matrix3x3 CreateRotationX(float angle)
	{
		float cos_angle = cos(angle);
		float sin_angle = sin(angle);

		return Matrix3x3(
			Vector3(1.0f, 0.0f, 0.0f),
			Vector3(0.0f, cos_angle, -sin_angle),
			Vector3(0.0f, sin_angle, cos_angle)
		);
	}

	Matrix3x3 operator*(const Matrix3x3& mat)
	{
		return {
			m_mat[0] * mat.m_mat[0],
			m_mat[1] * mat.m_mat[1],
			m_mat[2] * mat.m_mat[2]
		};
	}

	void print()
	{
		m_mat[0].print();
		m_mat[1].print();
		m_mat[2].print();
	}
};

namespace Math
{
	float deg_to_rad(float rad);
	float rad_to_deg(float rad);
	Vector3 model_to_world(Vector3 model, Matrix3x3 roation, Vector3 position);
	float length(Vector3 vec);
	Matrix3x3 transpose(Matrix3x3 mat);
	std::pair<int, int> get_fraction(float ratio);
}

#endif