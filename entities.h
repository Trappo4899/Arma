#ifndef ENTITIES_H
#define ENTITIES_H

#include "base class.h"
#include "visual state.h"
#include "entity type.h"
#include "realplayer.h"
#include "weapon.h"
#include "network manager.h"

class VisualState;
class EntityType;
class A3Vehicle;
class Weapon;
class PlayerIdentity;

enum ENTITY_TYPE
{
	INVALID,
	PLAYER,
	VEHICLE,
	WILDLIFE,
	PROJECTILE,
};

enum ENTITY_STANCE
{
	AISTANDING = 10,
	STANDING = 8,
	CROUCHING = 6,
	PRONE = 4,
};

class A3Entity : public BaseClass
{
protected:

	struct entity_data_t
	{
		union
		{
			DEFINE_MEMBER_N(UINT64,		CurrentVisualState,	0xD0);
			DEFINE_MEMBER_N(UINT64,		FutureVisualState,	0x190);

			DEFINE_MEMBER_N(UINT64,		EntityType, 0x150);
			DEFINE_MEMBER_N(UINT64,		ClassType, 0x158);

			DEFINE_MEMBER_N(UINT8,		IsDead,				0x504);
			DEFINE_MEMBER_N(BYTE,		ObjectHidden,		0x14C);
			DEFINE_MEMBER_N(UINT32,		Team,				0x340);
			DEFINE_MEMBER_N(UINT32,		NetworkID,			0xBB4);
			DEFINE_MEMBER_N(INT32,		WeaponIndex,		0xBEC);
			DEFINE_MEMBER_N(INT32,		WeaponListSize,		0xBD0);
		};
	};

protected:

	Address m_address;
	entity_data_t m_data;

public:

	A3Entity();
	A3Entity(Address address);

public:

	void Update();

	Address GetAddress();

	VisualState GetCurrentVisualState();
	VisualState GetFutureVisualState();

	EntityType GetEntityType();
	EntityType GetClassType();

	RealPlayer GetRealPlayer();

	bool IsDead();

	int GetHealth();

	void HideObject();
	bool IsObjectHidden();

	static void ChangeCollision(A3Entity target, Address localObject);

	bool IsCollisionEnabled(A3Entity target, Address localObject);

	UINT32 GetTeam();
	UINT32 GetNetworkID();

	Weapon GetActiveWeapon();

	UINT32 GetWeaponListSize();

	bool IsHoldingItem();

public:

	A3Vehicle GetVehicle();
};

class A3Player : public A3Entity
{

};

class A3Vehicle : public A3Entity
{
private:

	std::unordered_map<std::string, Vector3> head_positions = {

		/* blufor */
		{ "AH-9 Pawnee",{-0.302734,0.218747,1.23325} },
		{ "AH-99 Blackfoot",{0.03125,0.113494,3.83582} },
		{ "CH-67 Huron",{0.460938,-0.312252,6.4907} },
		{ "CH-67 Huron (Unarmed)",{0.458496,-0.313191,6.49192} },
		{ "MH-9 Hummingbird",{-0.302734,0.218869,1.23316} },
		{ "UH-80 Ghost Hawk",{-0.517578,-0.238793,5.14418} },
		{ "HEMTT",{-0.732422,0.484195,3.20634} },
		{ "HEMTT Ammo",{-0.755371,0.470943,4.00647} },
		{ "HEMTT Box",{-0.8125,0.0850735,4.17009} },
		{ "HEMTT Cargo",{-0.810547,0.0847096,4.86881} },
		{ "HEMTT Flatbed",{-0.733887,-0.305303,4.87718} },
		{ "HEMTT Fuel",{-0.730469,0.483295,3.82427} },
		{ "HEMTT Medical",{-0.916992,0.184648,4.07904} },
		{ "HEMTT Repair",{-0.805664,0.084034,4.17605} },
		{ "HEMTT Transport",{-0.78418,0.174357,4.03085} },
		{ "HEMTT Transport (Covered)",{-0.743652,0.171693,4.04595} },
		{ "Hunter",{-0.45752,0.226528,-1.41125} },
		{ "Hunter GMG",{-0.457031,-0.325842,-1.37607} },
		{ "Hunter HMG",{-0.491211,-0.326932,-1.39492} },
		{ "Prowler (AT)",{-0.652832,-0.143311,0.275825} },
		{ "Prowler (HMG)",{-0.682129,-0.457396,0.258488} },
		{ "Prowler (Unarmed)",{-0.617676,-0.45787,0.266443} },
		{ "Quad Bike",{0.0136719,0.278324,-0.0812217} },
		{ "Assault Boat",{0.38916,-0.282517,-1.28642} },
		{ "Rescue Boat",{0.430664,-0.282515,-1.30479} },
		{ "Speedboat Minigun",{0.195313,-0.357894,0.829717} },

		/* opfor */
		{"Mi-290 Taru", {-0.660645,-0.326407,4.00736}},
		{"Mi-290 Taru (Ammo)", {-0.660645,-0.0896692,4.00561}},
		{"Mi-290 Taru (Bench)", {-0.661133,-0.326394,4.00725}},
		{"Mi-290 Taru (Cargo)", {-0.660645,-0.0902448,4.00699}},
		{"Mi-290 Taru (Fuel)", {-0.661133,0.0557466,4.00789}},
		{"Mi-290 Taru (Medical)", {-0.660645,-0.0903482,4.00717}},
		{"Mi-290 Taru (Medical)", {-0.661133,-0.0900707,4.00659}},
		{"Mi-290 Taru (Repair)", {-0.661621,-0.0909109,4.00824}},
		{"Mi-290 Taru (Transport)", {-0.661621,-0.0909963,4.00848}},
		{"Mi-48 Kajman", {-0.0336914,0.3307,3.00349}},
		{"PO-30 Orca", {0.407715,-0.371259,3.37001}},
		{"PO-30 Orca (Unarmed)", {0.407715,-0.371264,3.36988}},
		{"Ifrit", {0.0239258,-0.00692272,-0.811817}},
		{"Ifrit GMG", {-0.027832,-0.356136,-0.810528}},
		{"Ifrit HMG", {-0.0424805,-0.354923,-0.821773}},
		{"Qilin (AT)", {-0.181152, -0.0466356, 0.534812}},
		{"Qilin (Minigun)", {-0.181152, -0.0466356, 0.534812}},
		{"Qilin (Unarmed)", {-0.181152, -0.0466356, 0.534812}},
		{"Tempest (Device)", {-0.737793,0.703078,2.25049}},
		{"Tempest Ammo", {-0.760254,0.704107,2.2344}},
		{"Tempest Fuel", {-0.745605,0.702507,2.32065}},
		{"Tempest Medical", {-0.634277,0.429929,2.5205}},
		{"Tempest Repair", {-0.700195,0.703941,2.23754}},
		{"Tempest Transport", {-0.671875,0.435176,2.52636}},
		{"Tempest Transport (Covered)", {-0.679688,0.435751,2.51474}},
		{"Zamak Ammo", {-0.639648,0.258454,2.89455}},
		{"Zamak Fuel", {-0.596191,0.258611,2.71802}},
		{"Zamak Medical", {-0.57373,0.258361,2.69842}},
		{"Zamak Repair", {-0.587891,0.258474,2.89691}},
		{"Zamak Transport", {-0.600098,0.258272,2.71579}},
		{"Zamak Transport (Covered)", {-0.612305,0.258296,2.70563}},
		{"Speedboat HMG", {0.0688477,1.71849,0.110171}},

		/* independant */
		{"CH-49 Mohawk",{0.748047,-1.10152,6.34361}},
		{"WY-55 Hellcat",{0.485352,0.320327,3.1578}},
		{"WY-55 Hellcat (Unarmed)",{0.484863,0.134992,3.15786}},
		{"Strider",{-0.0102539,0.132863,0.937112}},
		{"Strider GMG",{-0.0332031,-0.561211,0.923776}},
		{"Strider HMG",{-0.0253906,0.792559,-0.155429}},
		{"Zamak Ammo",{-0.587891,0.258534,2.89691}},
		{"Zamak Fuel",{-0.574707,0.258561,2.70008}},
		{"Zamak Medical",{-0.596191,0.258478,2.71813}},
		{"Zamak Repair",{-0.639648,0.258536,2.89451}},
		{"Zamak Transport",{-0.608887,0.258446,2.7094}},
		{"Zamak Transport (Covered)",{-0.568359,0.258439,2.71986}},

		/* civillian */
		{"M-900", {-0.309082,1.40305,2.04028}},
		{"Fuel Truck", {-0.506836, 0.473392, 0.0547505}},
		{"Hatchback", {-0.353516,-0.00777149,-0.0718043}},
		{"Hatchback (Sport)", {-0.355469,-0.00791693,-0.0681505}},
		{"Kart", {0.0522461, -0.0828342, -0.239975}},
		{"Kart (Bluking)", {0.0522461, -0.0828342, -0.239975}},
		{"Kart (Fuel)", {0.0522461, -0.0828342, -0.239975}},
		{"Kart (Redstone)", {0.0522461, -0.0828342, -0.239975}},
		{"Kart (Vrana)", {0.0522461, -0.0828342, -0.239975}},
		{"MB 4WD", {-0.366699,0.182532, -0.00230581}},
		{"Offroad", {-0.372559, 0.216817, 0.22662}},
		{"Offroad (Comms)", {-0.37207, 0.107836, 0.398185}},
		{"Offroad (Covered)", {-0.370605, 0.114599, 0.392483}},
		{"Offroad (Services)", {-0.372559, 0.216817, 0.22662}},
		{"SUV", {-0.384766,0.127804, -0.274392}},
		{"Tractor", {-0.0107422, 0.605633, -0.669401}},
		{"Truck", {-0.475586, 0.470151, 0.175949}},
		{"Truck Boxer", {-0.506836, 0.473392, 0.0547505}},
		{"Van (Ambulance)", {-0.489746, 0.192809, 2.16997}},
		{"Van (Cargo)", {-0.489746, 0.192809, 2.16997}},
		{"Van (Services)", {-0.489746, 0.192809, 2.16997}},
		{"Van Transport", {-0.489746, 0.192809, 2.16997}},
		{"Zamak Fuel", {-0.625488,0.257645,2.71889}},
		{"Zamak Repair", {-0.583008,0.25784,2.89282}},
		{"Zamak Transport", {-0.544434,0.258173,2.70477}},
		{"Zamak Transport (Covered)", {-0.571777,0.258175,2.72054}},
		{"RHIB", {-0.0761719, 0.985135, -1.27226}},
		{"Water Scooter", {0.00244141, 0.163588, 0.325972}},
	};

public:

	A3Vehicle();
	A3Vehicle(Address address);

public:

	bool HasDriver();

	A3Entity GetDriver();

public:

	Vector3 GetDriverHead(const std::string& vehName, VisualState visState);
};

class A3Projectile : public A3Entity
{

};

class LocalPlayer
{
public:

	A3Entity		m_local;
	VisualState		m_visual_state;
	CameraAngles	m_camera_angles;
	Weapon			m_active_weapon;

	ENTITY_STANCE	m_stance;

	int				m_health;

public:

	LocalPlayer();
	LocalPlayer(A3Entity local);

public:

	void Update();

	Vector3 GetViewangles();
	void SetViewangles(Vector3 viewangles);

	Vector3 GetGunPosition();
};

class Entity
{
public:

	A3Entity		m_entity;
	VisualState		m_visual_state;
	EntityType		m_entity_type;
	PlayerIdentity	m_player_identity;
	Weapon			m_active_weapon;

	Box				m_box;

	ENTITY_STANCE	m_stance;

	ImColor			m_color;
	
	int				m_distance;
	int				m_health;

	bool			m_invisible;
	bool			m_is_ai;

public:

	Entity();
	Entity(A3Entity entity);

	bool Update();
};

class Vehicle
{
public:

	A3Vehicle		m_vehicle;
	VisualState		m_visual_state;
	EntityType		m_entity_type;

	Entity			m_driver;

	Box				m_box;

	ImColor			m_color;

	int				m_distance;

	bool			m_inactive;

public:

	Vehicle();
	Vehicle(A3Vehicle vehicle);

	bool Update();
};

#endif