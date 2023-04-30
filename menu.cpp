#include "includes.h"

void CWindow::handle_movement()
{
	static float rel_x = 0.f;
	static float rel_y = 0.f;

	if (g_pInput->CursorInMenuRegion(0, 0, m_size.x, m_size.y) && !m_waiting)
	{
		if (g_pInput->WasKeyPressed(VK_LBUTTON))
		{
			m_moving = true;

			rel_x = (g_pInput->GetCursor().x - m_pos.x);
			rel_y = (g_pInput->GetCursor().y - m_pos.y);
		}
	}

	if (m_moving)
	{
		m_waiting = true;

		float mov_x = (g_pInput->GetCursor().x - rel_x);
		float mov_y = (g_pInput->GetCursor().y - rel_y);

		m_pos.x = mov_x;
		m_pos.y = mov_y;

		if (!g_pInput->IsKeyDown(VK_LBUTTON))
		{
			m_moving = false;
		}
	}
}

CWindow::CWindow()
{
	m_pos		= { };
	m_size		= { };
	m_accent	= { };
	m_open		= { };
}

void CWindow::think()
{
	g_pMenuRender->init(m_pos, m_accent);
}

void CMenu::menu_base()
{
	g_pMenuRender->rect_filled(-1, -1, m_size.x + 2, m_size.y + 2, ImColor(0, 0, 0));
	g_pMenuRender->rect_filled(0, 0, m_size.x, m_size.y, ImColor(25, 25, 25));
	g_pMenuRender->rect(0, 0, m_size.x, m_size.y, 1, ImColor(45, 45, 45));

	g_pMenuRender->rect(8, 8, m_size.x - 16, m_size.y - 16, 1, ImColor(0, 0, 0));
	g_pMenuRender->rect_filled(9, 9, m_size.x - 18, m_size.y - 18, ImColor(35, 35, 35));
	g_pMenuRender->rect(9, 9, m_size.x - 18, m_size.y - 18, 1, ImColor(45, 45, 45));

	g_pMenuRender->gradient(-1, -20, m_size.x + 1, 20, ImColor(45, 45, 45), ImColor(25, 25, 25));
	g_pMenuRender->rect(-1, -20, m_size.x + 2, 21, 1, ImColor(0, 0, 0));
	g_pMenuRender->rect(-1, -20, m_size.x + 1, 20, 1, ImColor(45, 45, 45));

	g_pMenuRender->text("Scouseware", 4, -15.f, g_pMiscSettings->m_accent->get_colour());

	g_pMenuRender->text(std::to_string((int)ImGui::GetIO().Framerate), m_size.x - 4, -14.f, g_pMiscSettings->m_accent->get_colour(), FONT_OUTLINED | FONT_RIGHT);
}

void CMenu::handle_tabs()
{
	const float men_width = m_size.x - 16;
	const float width = men_width / m_tabs.size();

	for (int i = 0; i < m_tabs.size(); i++)
	{
 		auto& tab = m_tabs.at(i);

		g_pMenuRender->rect(8 + (i * width), 8, width, 22.5f, 1, ImColor(0, 0, 0));
		g_pMenuRender->gradient(9 + (i * width), 9, width - 2, 20.5f, ImColor(45, 45, 45), ImColor(25, 25, 25));

		ImColor text_col = ImColor(150, 150, 150);

		if (tab.get_id() == m_selected_tab)
		{
			text_col = g_pMiscSettings->m_accent->get_colour();
		}
		else if (g_pInput->CursorInMenuRegion(8 + (i * width), 8, width, 22.5f))
		{
			text_col = ImColor(200, 200, 200);

			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_selected_tab = tab.get_id();
			}
		}

		g_pMenuRender->text(tab.get_name(), 8 + (i * width) + width / 2, 15, text_col, FONT_OUTLINED | FONT_CENTERED);

		if (tab.get_id() == m_selected_tab)
		{
			tab.think();
		}
	}
}

void CMenu::begin()
{
	g_pMenuRender->init(m_pos, g_pMiscSettings->m_accent->get_colour());
	menu_base();
}

void CMenu::end()
{
	handle_tabs();

	handle_movement();

	g_pMenu->m_hovering = false;
	g_pMenu->m_waiting = false;
	g_pMenuRender->render();
}

void CMenu::handle_movement()
{
	if (g_pMenu->m_hovering)
	{
		return;
	}

	static float rel_x = 0.f;
	static float rel_y = 0.f;

	if (g_pInput->CursorInMenuRegion(-4, -24, m_size.x + 8, m_size.y + 28) && !m_waiting)
	{
		if (g_pInput->WasKeyPressed(VK_LBUTTON))
		{
			m_moving = true;

			rel_x = (g_pInput->GetCursor().x - m_pos.x);
			rel_y = (g_pInput->GetCursor().y - m_pos.y);
		}
	}

	if (m_moving)
	{
		m_waiting = true;

		float mov_x = (g_pInput->GetCursor().x - rel_x);
		float mov_y = (g_pInput->GetCursor().y - rel_y);

		m_pos.x = mov_x;
		m_pos.y = mov_y;

		if (!g_pInput->IsKeyDown(VK_LBUTTON))
		{
			m_moving = false;
		}
	}
}

CMenu::CMenu()
{
	m_pos = { 250, 250 };
	m_size = { 650, 450 };
	m_accent = { 164, 146, 243, 255 };
	m_open = { false };
	m_tabs = { };
	m_selected_tab = { };
}

void CMenu::add_tab(const char* name)
{
	m_tabs.push_back(CTab(name, m_tabs_num));

	++m_tabs_num;
}

void CMenu::think()
{
	static bool init = false;

	if (!init)
	{
		g_pAimbotSettings->init();
		g_pEspSettings->init();
		g_pMiscSettings->init();

		init = true;
	}

	if (g_pMiscSettings->m_menu_key->IsActive())
	{
		this->begin();

		this->end();
	}
}