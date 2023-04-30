#ifndef WORLD_H
#define WORLD_H

#undef FAR

#include "list.h"
#include "entities.h"
#include "camera.h"

struct _CameraView
{
	INT32 CameraView1;
	INT32 CameraView2;
	INT32 CameraView3;
	FLOAT CameraFade1;
	FLOAT CameraFade2;
	FLOAT CameraFade3;
};

enum class ListDistance
{
	CLOSE = 0,
	MEDIUM = 100,
	FAR = 1800,
	FARFAR = 2400,
};

class World : public BaseClass
{
private:

	struct world_data_t
	{
		union
		{
			/* downside to this macro is it needs to be a compile time constant for the offset passed in
				so we cannot use our reversals namespace and have to hardcode the values */

			DEFINE_MEMBER_N(UINT64,			Camera,						 0xC10);

			DEFINE_MEMBER_N(UINT64,			ProjectileList,				0x1A40);
			DEFINE_MEMBER_N(UINT32,			ProjectileCount,			0x1A48);

			DEFINE_MEMBER_N(UINT64,			CloseEntityList,			0x1B10);
			DEFINE_MEMBER_N(UINT32,			CloseEntityListCount,		0x1B18);

			DEFINE_MEMBER_N(UINT64,			MediumEntityList,			0x1BD8);
			DEFINE_MEMBER_N(UINT32,			MediumEntityListCount,		0x1BE0);

			DEFINE_MEMBER_N(UINT64,			FarEntityList,				0x1CA0);
			DEFINE_MEMBER_N(UINT32,			FarEntityListCount,			0x1CA8);

			DEFINE_MEMBER_N(UINT64,			FarFarEntityList,			0x1D68);
			DEFINE_MEMBER_N(UINT32,			FarFarEntityListCount,		0x1D70);

			DEFINE_MEMBER_N(_CameraView,	CameraView,					0x2C20);

			DEFINE_MEMBER_N(FLOAT,			OverallViewDistance,		0x1538);
			DEFINE_MEMBER_N(FLOAT,			ShadowViewDistance,			0x14D0);
			DEFINE_MEMBER_N(FLOAT,			ObjectViewDistance,			0x1544);
			DEFINE_MEMBER_N(FLOAT,			PIPViewDistance,			0x14EC);

			DEFINE_MEMBER_N(UINT64,			CameraOn,					0x2B10);
			DEFINE_MEMBER_N(UINT64,			LocalPlayer,				0x2B30);

			DEFINE_MEMBER_N(UINT8,			thirdperson,				0x2C23);
		};
	};

private:

	Address m_address;
	world_data_t m_data;

public:

	World();
	World(Address addr);

public:

	Address GetAddress();

	void Update();

	Camera GetCamera();

	List GetProjectileList();
	UINT32 GetProjectileListCount();

	List GetCloseEntityList();
	UINT32 GetCloseEntityListCount();

	List GetMediumEntityList();
	UINT32 GetMediumEntityListCount();

	List GetFarEntityList();
	UINT32 GetFarEntityListCount();

	List GetFarFarEntityList();
	UINT32 GetFarFarEntityListCount();

	std::vector<A3Entity>		GetEntities();
	std::vector<A3Projectile>	GetProjectiles();

	A3Entity GetParent();
	A3Entity GetLocal();

	bool IsThirdperson();

	void ForceCamera(int mode);

	float GetOverallViewDistance();
	float GetObjectViewDistance();
	float GetShadowViewDistance();
	float GetPIPViewDistance();
};

#endif