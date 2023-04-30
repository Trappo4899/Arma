#include "includes.h"

VisualState::VisualState()
{
	m_address = nullptr;
	m_data = { };
}

VisualState::VisualState(Address address)
{
	m_address = address;
	m_data = m_address.at<visual_state_data_t>();
}

void VisualState::Update()
{
	m_data = m_address.at<visual_state_data_t>();
}

Address VisualState::GetAddress()
{
	return m_address;
}

Matrix3x3 VisualState::GetRotationMatrix()
{
	return m_data.Rotation;
}

Matrix3x3 VisualState::GetInverseRotationMatrix()
{
	return m_data.InverseRotation;
}

void VisualState::SetRotationMatrix(Matrix3x3 rot)
{
	m_address.set<Matrix3x3>(Offsets::VisualState::Rotation, rot);
}

void VisualState::SetInverseRotationMatrix(Matrix3x3 rot)
{
	m_address.set<Matrix3x3>(Offsets::VisualState::InverseRotation, rot);
}

void VisualState::SetRotation(float angle)
{
	Vector3 oldVel = m_address.at<Vector3>(Offsets::VisualState::Velocity);

	float sinAngle = sinf(angle);
	float cosAngle = cosf(angle);

	Matrix3x3 newRotation = {
		{  cosAngle,  0.f,  -sinAngle	},
		{      0.f,   1.f,      0.f		},
		{ sinAngle,  0.f,  cosAngle	}
	};

	Matrix3x3 newInverse = {
		{  cosAngle,  0.f, sinAngle	},
		{      0.f,   1.f,      0.f		},
		{  -sinAngle,  0.f,  cosAngle	}
	};

	this->SetRotationMatrix(newRotation);
	this->SetInverseRotationMatrix(newInverse);

	this->SetVelocity(oldVel);
}

Vector3 VisualState::GetOrigin()
{
	return m_data.Origin;
}

Vector3 VisualState::GetChest()
{
	return m_data.Chest;
}

Vector3 VisualState::GetHead()
{
	return m_data.Head;
}

Vector3 VisualState::GetInversePos()
{
	return m_data.InversePos;
}

Vector3 VisualState::GetVelocity()
{
	return m_data.Velocity;
}

Vector3 VisualState::GetAcceleration()
{
	return m_data.Acceleration;
}

void VisualState::SetVelocity(Vector3 velocity)
{
	m_address.set<Vector3>(Offsets::VisualState::Velocity, velocity);
}

INT32 VisualState::GetMoveInfoTableIndex1()
{
	return m_data.MoveInfoTableIndex1;
}

INT32 VisualState::GetMoveInfoTableIndex2()
{
	return m_data.MoveInfoTableIndex2;
}

FLOAT VisualState::GetAnimationCompletion()
{
	return m_data.AnimationCompletion;
}

Vector3 VisualState::GetInaccuracy()
{
	return m_data.Inaccuracy;
}
