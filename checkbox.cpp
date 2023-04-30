#include "includes.h"

CCheckbox::CCheckbox(const char* name, bool def)
{
	m_padding = { 0, m_size.y + 16 };
	m_size = { 6, 6 };
	m_name = name;
	m_on = def;
}

bool CCheckbox::active()
{
	return m_on;
}

void CCheckbox::think(Vector2 pos, Vector2 size)
{
	pos.x += 15;
	pos.y += 15;

	g_pMenuRender->rect(pos.x - 1, pos.y - 1, m_size.x + 2, m_size.y + 2, 1, ImColor(0, 0, 0));
	g_pMenuRender->rect_filled(pos.x, pos.y, m_size.x, m_size.y, m_on ? g_pMiscSettings->m_accent->get_colour() : ImColor(60, 60, 60));

	ImColor text_col = ImColor(150, 150, 150);

	if (g_pInput->CursorInMenuRegion(pos.x - 4, pos.y - 5, m_size.x + ((size.x / 2) - 8), m_size.y + 10) && !g_pMenu->m_waiting)
	{
		g_pMenu->m_hovering = true;

		text_col = ImColor(200, 200, 200);

		if (g_pInput->WasKeyPressed(VK_LBUTTON))
		{
			m_on = !m_on;
		}
	}

	g_pMenuRender->text(m_name, pos.x + m_size.x + 10, pos.y - 2, text_col, FONT_DROPSHADOW);
}