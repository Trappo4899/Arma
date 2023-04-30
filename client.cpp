#include "includes.h"

Client::Client()
{
	m_arma = Process(L"Arma3_x64.exe");
	m_world = World( );
}

bool Client::init()
{
	if (!g_pDriver->IsLoaded())
	{
		printf("[X] Driver is not mapped!\n");
		system("PAUSE");
		return false;
	}
	
	if (!Process::init(m_arma))
	{
		return false;
	}

	m_world						= World					( m_arma.get_address().at(Offsets::Process::World			));
	m_network_manager			= NetworkManager		( m_arma.get_address().at(Offsets::Process::NetworkManager	));
	m_landscape					= Landscape				( m_arma.get_address().at(Offsets::Process::Landscape		));
	m_dlc_manager				= DlcManager			( m_arma.get_address().at(Offsets::Process::DlcManager		 ).at(0x30));
	m_dx11_engine				= DX11Engine			( m_arma.get_address().at(Offsets::Process::DX11Engine		));

	printf("[ARMA]		-> 0x%p\n",				m_arma.get_address().as<void*>());
	printf("[WORLD]		-> 0x%p\n",				m_world.GetAddress().as<void*>());
	printf("[NET MANAGER]	-> 0x%p\n",			m_network_manager.GetAddress().as<void*>());
	printf("[LANDSCAPE]	-> 0x%p\n",				m_landscape.GetAddress().as<void*>());
	printf("[DLC MANAGER]	-> 0x%p\n",			m_dlc_manager.GetAddress().as<void*>());
	printf("[DX11 ENGINE]	-> 0x%p\n",			m_dx11_engine.GetAddress().as<void*>());

	m_dlc_manager.UnlockDlcs();

	m_screen_size.x = m_dx11_engine.GetScreenWidth();
	m_screen_size.y = m_dx11_engine.GetScreenHeight();

	std::thread(fast_cache).detach();
	std::thread(slow_cache).detach();
	std::thread(other).detach();

	return true;
}

void Client::slow_cache()
{
	while (true)
	{
		g_pClient->m_mutex.lock();

		g_pClient->m_entity_list.SlowUpdate();

		g_pClient->m_mutex.unlock();

		SLEEP(250);
	}
}

void Client::fast_cache()
{
	while (true)
	{
		g_pClient->m_world.Update();
		g_pClient->m_dx11_engine.Update();

		g_pClient->m_parent = g_pClient->m_world.GetParent();
		g_pClient->m_local = g_pClient->m_world.GetLocal();

		g_pClient->m_local.Update();

		SLEEP(35);
	}
}

void Client::other()
{
	while (true)
	{
		if (g_pClient->m_local.m_local.GetAddress() && !g_pClient->m_local.m_local.IsDead())
		{
			if (g_pAimbot->think())
			{
				continue;
			}

			/* do fov changer */
			g_pClient->m_dx11_engine.Handle();

			if (g_pAimbotSettings->m_instant_scope->active())
			{
				g_pClient->m_local.m_active_weapon.GetWeaponType().SetScopeInSpeed(100.f);
			}
			else
			{
				g_pClient->m_local.m_active_weapon.GetWeaponType().SetScopeInSpeed(1.f);
			}

			if (g_pAimbotSettings->m_weapon_inertia->get() > 0.f)
			{
				g_pClient->m_local.m_active_weapon.GetWeaponType().SetInertia(g_pAimbotSettings->m_weapon_inertia->get());
			}

			static bool once = false;

			if (g_pAimbotSettings->m_weapon_caliber->get() > 0.f)
			{
				g_pClient->m_local.m_active_weapon.GetMuzzleState().GetMagazine().GetMagazineType().GetAmmoType().SetCaliber(g_pAimbotSettings->m_weapon_caliber->get());
				once = true;
			}
			else if (!once)
			{
				g_pClient->m_local.m_active_weapon.GetMuzzleState().GetMagazine().GetMagazineType().GetAmmoType().ResetCaliber();
			}
		}

		SLEEP(35);
	}
}