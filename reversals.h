#ifndef REVERSALS_H
#define REVERSALS_H

namespace Offsets
{
	namespace Process
	{
		constexpr UINT_PTR World = 0x26733A0;				// IsSever -> qword_xxxxx + xxxxx									- 48 8B 05 ? ? ? ? 83 B8 ? ? ? ? ? 75 13 33 D2 48 8B CB E8 ? ? ? ? 48 8B C3 48 83 C4 20 5B C3
		constexpr UINT_PTR NetworkManager = 0x26305E8;		// IsSever -> sub_xxx -> return qword_xxx							- 48 8B 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC C7 01 ? ? ? ? 48 8B C1 C3 
		constexpr UINT_PTR Landscape = 0x269B3C0;			// getPos -> vXX = sub_xxxx(qword_xxxxx)							- 48 8B 0D ? ? ? ? 48 8B 1B 41 0F 28 D1 0F 28 CE E8 ? ? ? ? 48 8B 0D ? ? ? ? 41 0F 28 D0 0F 28 CF 33 C0 45 33 C9 0F 28 F0 48 89 44 24 ? 48 89 44 24 ? E8 ? ? ? ? 
		constexpr UINT_PTR DlcManager = 0x2561350 + 0xA8;	// getDlcs -> vXX = sub_xxxx -> return qword_xxxxx + 0xA8			- 8B 05 ? ? ? ? A8 01 75 2D 83 C8 01 48 8D 1D ? ? ? ? 48 8B CB 89 05 ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B C3 48 83 C4 20 5B C3 48 8D 05 ? ? ? ? 48 83 C4 20 5B C3 CC 
		constexpr UINT_PTR DX11Engine = 0x26411E0;			// worldToScreen -> if vXX > 0.0 -> vXX = qword_xxxxx				- 48 8B 05 ? ? ? ? F3 0F 10 45 ? 48 8B 4D 8F 48 89 B4 24 ? ? ? ? F2 0F 10 88 ? ? ? ? F2 0F 11 4D ? 0F 29 BC 24 ? ? ? ? F3 0F 10 3D ? ? ? ? 0F 28 D7 
	}

	namespace World
	{
		constexpr UINT_PTR	Camera = 0xC10;

		constexpr UINT_PTR	ProjectileList = 0x1A40;
		constexpr UINT_PTR	ProjectileListCount = 0x1A48;

		constexpr UINT_PTR  CloseEntityList = 0x1B10;
		constexpr UINT_PTR	CloseEntityListCount = 0x1B18;

		constexpr UINT_PTR	MediumEntityList = 0x1BD8;
		constexpr UINT_PTR	MediumEntityListCount = 0x1BE0;

		constexpr UINT_PTR	FarEntityList = 0x1CA0;
		constexpr UINT_PTR	FarEntityListCount = 0x1CA8;

		constexpr UINT_PTR	FarFarEntityList = 0x1D68;
		constexpr UINT_PTR	FarFarEntityListCount = 0x1D70;

		constexpr UINT_PTR	CameraOn = 0x2B10;
		constexpr UINT_PTR	LocalPlayer = 0x2B30;

		constexpr UINT_PTR	CollisionDisabled = 0x2AC0;

		constexpr UINT_PTR	CameraView = 0x2C20;

		constexpr UINT_PTR	OverallViewDistance = 0x1538;
		constexpr UINT_PTR	ShadowViewDistance = 0x14D0;
		constexpr UINT_PTR	ObjectViewDistance = 0x1544;
		constexpr UINT_PTR	PIPViewDistance = 0x14EC;
	}

	namespace NetworkManager
	{
		constexpr UINT_PTR NetSession = 0x8;
		constexpr UINT_PTR NetworkServer = 0x40;
		constexpr UINT_PTR NetworkClient = 0x48;
	}

	namespace NetworkClient
	{
		constexpr UINT_PTR PlayerIdentities = 0x38;
		constexpr UINT_PTR PlayerIdentitiesSize = 0x40;
		constexpr UINT_PTR MapName = 0x60;
		constexpr UINT_PTR MissionName = 0x68;
	}

	namespace PlayerIdentity
	{
		constexpr UINT_PTR Padding = 0x2F0;

		constexpr UINT_PTR NetworkID = 0x8;
		constexpr UINT_PTR Name = 0x188;

		constexpr UINT_PTR SteamID1 = 0x18;
		constexpr UINT_PTR SteamID2 = 0xD0;
		constexpr UINT_PTR SteamID3 = 0xD8;
	}

	namespace Landscape
	{

	}

	namespace DlcManager
	{
		constexpr UINT_PTR	DlcTable = 0x30;
		constexpr UINT_PTR	DlcTableCount = 0x38;

		/* dlc item */
		constexpr UINT_PTR	IsOwned = 0x1C;
		constexpr UINT_PTR	Name = 0x20;
	}

	namespace DX11Engine
	{
		constexpr UINT_PTR	ScreenWidth = 0xC4;
		constexpr UINT_PTR	ScreenHeight = 0xC8;

		constexpr UINT_PTR	FovTop = 0x9C;
		constexpr UINT_PTR	FovLeft = 0xA0;
	}

	namespace Entity
	{
		/* vehicle -> 0x1088 -> 0xC8 - turret rotation amount? */
		/* visual states */
		constexpr UINT_PTR	CurrentVisualState = 0xD0;
		constexpr UINT_PTR	FutureVisualState = 0x190;

		/* entity types */
		constexpr UINT_PTR	EntityType = 0x150;
		constexpr UINT_PTR	ClassType = 0x158;

		/* classes */
		constexpr UINT_PTR	RealPlayer = 0x1090;

		/* health */
		constexpr UINT_PTR	Dammage = 0xF0;
		constexpr UINT_PTR	IsDead = 0x504;

		/* collision */
		constexpr UINT_PTR	Collision = 0x470;
		constexpr UINT_PTR	ObjectHidden = 0x14C;

		/* identity */
		constexpr UINT_PTR	Team = 0x340;
		constexpr UINT_PTR	NetworkID = 0xBC4;

		/* vehicle */
		constexpr UINT_PTR	DriverEntityLink = 0xDF8;

		/* weapons */
		constexpr UINT_PTR	WeaponTypeList = 0xBC8;
		constexpr UINT_PTR	WeaponListSize = 0xBD0;
		constexpr UINT_PTR	ActiveWeaponIndex = 0xBEC;
		constexpr UINT_PTR	WeaponTable = 0xCF8;
		constexpr UINT_PTR	WeaponTableSize = 0xCE0;
	}

	namespace VisualState
	{
		/* positions */
		constexpr UINT_PTR	Origin = 0x2C;
		constexpr UINT_PTR	Head = 0x168;
		constexpr UINT_PTR	Chest = 0x174;
		constexpr UINT_PTR	InversePos = 0xB8;

		/* rotation matrixes */
		constexpr UINT_PTR	Rotation = 0x8;
		constexpr UINT_PTR	InverseRotation = 0x94;

		/* speed */
		constexpr UINT_PTR	Velocity = 0x54;
		constexpr UINT_PTR	Acceleration = 0x60;

		/* indexes */
		constexpr UINT_PTR	MoveInfoTableIndex1 = 0xC8;
		constexpr UINT_PTR	MoveInfoTableIndex2 = 0xE8;

		constexpr UINT_PTR	AnimationCompletion = 0x10C;

		constexpr UINT_PTR	Inaccuracy = 0x194;
	}

	namespace EntityType
	{
		constexpr UINT_PTR	Name = 0x68;
		constexpr UINT_PTR	Path = 0x80;
		constexpr UINT_PTR	Class = 0xD0;
		constexpr UINT_PTR	Print = 0x12D0;
		constexpr UINT_PTR	Type = 0x12E8;

		constexpr UINT_PTR	MovesType = 0x1E88;
	}

	namespace RealPlayer
	{
		constexpr UINT_PTR	CameraAngles = 0x1A0;
	}

	namespace CameraAngles
	{
		constexpr UINT_PTR	ViewAngles = 0x4;
		constexpr UINT_PTR	FreeLook = 0x10;
	}

	namespace Camera
	{
		constexpr UINT_PTR Viewmatrix = 0x8;
		constexpr UINT_PTR Position = 0x2C;
		constexpr UINT_PTR ScreenCenter = 0x58;
		constexpr UINT_PTR ProjectionMatrix = 0xD0;
		constexpr UINT_PTR ZoomMultiplier = 0x70;
	}

	namespace MovesType
	{
		constexpr UINT_PTR Skeleton = 0xC8;
		constexpr UINT_PTR MoveInfoTable = 0xF8;
	}

	namespace MoveInfo
	{
		constexpr UINT_PTR ActionMap = 0x18;
	}

	namespace ActionMap
	{
		constexpr UINT_PTR ActionID = 0x48;
	}

	namespace Weapon
	{
		constexpr UINT_PTR WeaponMode = 0x0;
		constexpr UINT_PTR WeaponType = 0x8;
		constexpr UINT_PTR MuzzleType = 0x10;
		constexpr UINT_PTR MuzzleState = 0x18;
	}

	namespace WeaponMode
	{
		constexpr UINT_PTR Firerate = 0x20;
	}

	namespace WeaponType
	{
		constexpr UINT_PTR	Name = 0x38;
		constexpr UINT_PTR	Type = 0x40;
		constexpr UINT_PTR	Family = 0xC0;
		constexpr UINT_PTR	ScopeInSpeed = 0x4EC;
		constexpr UINT_PTR	Inertia = 0x4F0;
		constexpr UINT_PTR	InitialSpeed = 0x4F4;
	}

	namespace MuzzleType
	{

	}

	namespace MuzzleState
	{
		constexpr UINT_PTR Magazine = 0x48;
	}

	namespace Magazine
	{
		constexpr UINT_PTR MagazineType = 0x48;
		constexpr UINT_PTR Name = 0x50;
		constexpr UINT_PTR Print = 0x58;
		constexpr UINT_PTR ShootDelay = 0x70;
	}

	namespace MagazineType
	{
		constexpr UINT_PTR AmmoType = 0x28;
		constexpr UINT_PTR Print = 0x40;
		constexpr UINT_PTR Type = 0x60;
		constexpr UINT_PTR MaxLeadSpeed = 0x80;
		constexpr UINT_PTR InitialSpeed = 0x84;
		constexpr UINT_PTR MaxThrowHoldTime = 0xA8;
		constexpr UINT_PTR MinThrowIntensityCoef = 0xAC;
		constexpr UINT_PTR MaxThrowIntensityCoef = 0xB0;
	}

	namespace AmmoType
	{
		constexpr UINT_PTR Name = 0x68;
		constexpr UINT_PTR Type = 0xD0;
		constexpr UINT_PTR MaxControlRange = 0x398;
		constexpr UINT_PTR ThrustTime = 0x3C4;
		constexpr UINT_PTR Thrust = 0x3C8;
		constexpr UINT_PTR Caliber = 0x404;
		constexpr UINT_PTR TimeToLive = 0x410;
		constexpr UINT_PTR AirFriction = 0x418;
		constexpr UINT_PTR WaterFriction = 0x41C;
		constexpr UINT_PTR GravityCoefficient = 0x420;
		constexpr UINT_PTR TypicalSpeed = 0x424;
	}
}

#endif