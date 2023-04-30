#ifndef CLIENT_H
#define CLIENT_H

#include "world.h"
#include "dlc manager.h"
#include "network manager.h"
#include "landscape.h"
#include "dx11engine.h"
#include "entitylist.h"

#define SLEEP(amount) (std::this_thread::sleep_for(std::chrono::milliseconds(amount)))

class Process;
class World;
class DlcManager;

class Client
{
public:

	Process							m_arma;

public:

	World							m_world;
	NetworkManager					m_network_manager;
	Landscape						m_landscape;
	DlcManager						m_dlc_manager;
	DX11Engine						m_dx11_engine;
	Camera							m_camera;

	A3Entity						m_parent;
	LocalPlayer						m_local;

public:

	EntityList						m_entity_list;

public:

	Vector2							m_screen_size;
	std::mutex						m_mutex;

public:

	Client();

	bool init();

	static void slow_cache();
	static void fast_cache();
	static void other();
	static void input_update();
};

extern std::unique_ptr<Client>		g_pClient;

#endif