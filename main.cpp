#include "includes.h"

std::unique_ptr<Driver>					g_pDriver(new Driver);
std::unique_ptr<Client>					g_pClient(new Client);
std::unique_ptr<Rendering>				g_pRender(new Rendering);
std::unique_ptr<CRender>				g_pMenuRender(new CRender(g_pRender.get()));
std::unique_ptr<CInput>					g_pInput(new CInput);
std::unique_ptr<CMenu>					g_pMenu(new CMenu);
std::unique_ptr<CAimbotSettings>		g_pAimbotSettings(new CAimbotSettings);
std::unique_ptr<CEspSettings>			g_pEspSettings(new CEspSettings);
std::unique_ptr<CMiscSettings>			g_pMiscSettings(new CMiscSettings);
std::unique_ptr<CVisuals>				g_pVisuals(new CVisuals);
std::unique_ptr<CAimbot>				g_pAimbot(new CAimbot);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	//AllocConsole();
	//FILE* f;
	//freopen_s(&f, "CONOUT$", "w", stdout);

	if (!g_pRender->init(nCmdShow))
	{
		printf("Failed to initialize rendering!\n");
		return 1;
	}

	if (!g_pClient->init())
	{
		printf("[X] Failed to initialize!\n");
		return 1;
	}

	while (true)
	{
		g_pRender->begin_render();

		g_pInput->update();

		if (g_pClient->m_parent.GetAddress().as<UINT_PTR>())
		{
			g_pClient->m_camera = g_pClient->m_world.GetCamera();

			if (g_pAimbot->m_pred.x || g_pAimbot->m_pred.y)
			{
				/* do this here because render thread + cached value so no flickering */

				g_pRender->background.rect_filled(g_pAimbot->m_pred.x - 8.f, g_pAimbot->m_pred.y - 8.f, 4.f, 4.f, ImColor(0.f, 0.f, 0.f, g_pAimbotSettings->m_visualize_col->get_colour().Value.w));
				g_pRender->background.rect_filled(g_pAimbot->m_pred.x - 8.f + 1.f, g_pAimbot->m_pred.y - 8.f + 1.f, 2.f, 2.f, g_pAimbotSettings->m_visualize_col->get_colour());
			}

			if (g_pClient->m_mutex.try_lock())
			{
				g_pClient->m_entity_list.FastUpdate();

				g_pClient->m_mutex.unlock();
			}

			g_pVisuals->think(g_pClient->m_entity_list);
		}

		g_pMenu->think();

		g_pRender->end_render();
	}
	
	return 0;
}
