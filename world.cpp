#include "includes.h"

World::World()
{
	m_address = { };
	m_data = { };
}

World::World(Address addr)
{
	m_address = addr;
	m_data = m_address.at<world_data_t>();
}

Address World::GetAddress()
{
	return m_address;
}

void World::Update()
{
	m_data = m_address.at<world_data_t>();
}

Camera World::GetCamera()
{
	return Camera(m_data.Camera);
}

List World::GetProjectileList()
{
	return List(m_data.ProjectileList, this->GetProjectileListCount());
}

UINT32 World::GetProjectileListCount()
{
	return m_data.ProjectileCount;
}

List World::GetCloseEntityList()
{
	return List(m_data.CloseEntityList, this->GetCloseEntityListCount());
}

UINT32 World::GetCloseEntityListCount()
{
	return m_data.CloseEntityListCount;
}

List World::GetMediumEntityList()
{
	return List(m_data.MediumEntityList, this->GetMediumEntityListCount());
}

UINT32 World::GetMediumEntityListCount()
{
	return m_data.MediumEntityListCount;
}

List World::GetFarEntityList()
{
	return List(m_data.FarEntityList, this->GetFarEntityListCount());
}

UINT32 World::GetFarEntityListCount()
{
	return m_data.FarEntityListCount;
}

List World::GetFarFarEntityList()
{
	return List(m_data.FarFarEntityList, this->GetFarFarEntityListCount());
}

UINT32 World::GetFarFarEntityListCount()
{
	return m_data.FarFarEntityListCount;
}

std::vector<A3Entity> World::GetEntities()
{
	std::vector<List> lists			= { };
	std::vector<A3Entity> out		= { };

	lists.push_back	(	this->GetCloseEntityList()		);
	lists.push_back	(	this->GetMediumEntityList()		);
	lists.push_back	(	this->GetFarEntityList()		);
	lists.push_back	(	this->GetFarFarEntityList()		);

	for (auto curr_list : lists)
	{
		auto list = curr_list.get_list();

		for (auto e : list)
		{
			if (!e || e.as<UINT_PTR>() == g_pClient->m_parent.GetAddress().as<UINT_PTR>())
			{
				continue;
			}

			auto ent = A3Entity(e);

			auto ent_type = ent.GetEntityType();

			if ( _stricmp(XOR("soldier"),			ent_type.GetClass().c_str()	)	!= 0 &&
				 _stricmp(XOR("carx"),				ent_type.GetClass().c_str()	)	!= 0 &&
				 _stricmp(XOR("tankx"),				ent_type.GetClass().c_str()	)	!= 0 &&
				 _stricmp(XOR("helicopterrtd"),		ent_type.GetClass().c_str()	)	!= 0 &&
				 _stricmp(XOR("shipx"),				ent_type.GetClass().c_str()	)	!= 0 &&
				 _stricmp(XOR("paraglide"),			ent_type.GetClass().c_str()	)	!= 0 &&
				 _stricmp(XOR("animal"),			ent_type.GetClass().c_str()	)	!= 0  )
			{
				continue;
			}

			auto visual_state = ent.GetFutureVisualState();

			if (g_pClient->m_parent.GetCurrentVisualState().GetOrigin().Distance(visual_state.GetOrigin()) > g_pClient->m_world.GetObjectViewDistance())
			{
				continue;
			}

			out.push_back(A3Entity(e));
		}
	}

	return out;
}

std::vector<A3Projectile> World::GetProjectiles()
{
	std::vector<A3Projectile> out = { };

	//auto list = this->GetProjectileList().get_list();

	//if (list.empty())
	//{
	//	return out;
	//}

	//for (auto curr : list)
	//{
	//	out.push_back(curr.as<A3Projectile>());
	//}

	return out;
}

A3Entity World::GetParent()
{
	return A3Entity(Address(m_data.CameraOn).at(0x8));
}

A3Entity World::GetLocal()
{
	return A3Entity(Address(m_data.LocalPlayer).at(0x8));
}

bool World::IsThirdperson()
{
	return g_pClient->m_camera.GetPosition().Distance(g_pClient->m_local.m_visual_state.GetHead()) > 1.f;
}

void World::ForceCamera(int mode)
{
	_CameraView cView = { mode, mode, mode, 0.f, 0.f, 0.f };
	this->m_address.at(UINT_PTR(Offsets::World::CameraView)).set(cView);
}

float World::GetOverallViewDistance()
{
	return m_data.OverallViewDistance;
}

float World::GetObjectViewDistance()
{
	return m_data.ObjectViewDistance;
}

float World::GetShadowViewDistance()
{
	return m_data.ShadowViewDistance;
}

float World::GetPIPViewDistance()
{
	return m_data.PIPViewDistance;
}