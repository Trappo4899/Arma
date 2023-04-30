#ifndef VISUAL_STATE_H
#define VISUAL_STATE_H

class VisualState : public BaseClass
{
private:

	struct visual_state_data_t
	{
		union
		{
			DEFINE_MEMBER_N( Matrix3x3,		Rotation,				0x8		);
			DEFINE_MEMBER_N( Vector3,		Origin,					0x2C	);
			DEFINE_MEMBER_N( Vector3,		Velocity,				0x54	);
			DEFINE_MEMBER_N( Vector3,		Acceleration,			0x60	);
			DEFINE_MEMBER_N( Matrix3x3,		InverseRotation,		0x94	);
			DEFINE_MEMBER_N( Vector3,		Chest,					0x174	);
			DEFINE_MEMBER_N( Vector3,		Head,					0x168	);
			DEFINE_MEMBER_N( INT32,			MoveInfoTableIndex1,	0xC8	);
			DEFINE_MEMBER_N( INT32,			MoveInfoTableIndex2,	0xE8	);
			DEFINE_MEMBER_N( FLOAT,			AnimationCompletion,	0x10C	);
			DEFINE_MEMBER_N( Vector3,		InversePos,				0xB8	);
			DEFINE_MEMBER_N( Vector3,		Inaccuracy,				0x198	);
		};

		visual_state_data_t()
		{

		}
	};

private:

	Address m_address;
	visual_state_data_t m_data;

public:

	VisualState();
	VisualState(Address address);

public:

	void Update();

	Address GetAddress();

	Matrix3x3 GetRotationMatrix();
	Matrix3x3 GetInverseRotationMatrix();

	void SetRotationMatrix(Matrix3x3 rot);
	void SetInverseRotationMatrix(Matrix3x3 rot);
	void SetRotation(float angle);

	Vector3 GetOrigin();
	Vector3 GetChest();
	Vector3 GetHead();
	Vector3 GetInversePos();

	Vector3 GetVelocity();
	Vector3 GetAcceleration();

	void SetVelocity(Vector3 velocity);

	INT32 GetMoveInfoTableIndex1();
	INT32 GetMoveInfoTableIndex2();
	
	FLOAT GetAnimationCompletion();

	Vector3 GetInaccuracy();
};

#endif