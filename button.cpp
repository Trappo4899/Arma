#include "includes.h"

CButton::CButton(const char* name, tButtonRoutine routine)
{
	m_name = name;
	m_routine = routine;
	m_padding = { 0.f, 30.5f };
}

void CButton::think(Vector2 pos, Vector2 size)
{
	pos.x += 32;
	pos.y += 15;

	static const float width = (size.x / 2.f);
	static const float height = 20.f;

	g_pMenuRender->rect(pos.x - 1, pos.y - 1, width + 2, height + 2, 1, ImColor(0, 0, 0));
	g_pMenuRender->gradient(pos.x, pos.y, width, height, ImColor(35, 35, 35), ImColor(50, 50, 50));
	g_pMenuRender->rect(pos.x, pos.y, width, height, 1, ImColor(45, 45, 45));

	ImColor textCol = ImColor(150, 150, 150);

	if (g_pInput->CursorInMenuRegion(pos.x - 4, pos.y - 2, width + 8, height + 4) && !g_pMenu->m_waiting)
	{
		g_pMenu->m_hovering = true;

		textCol = ImColor(200, 200, 200);

		if (g_pInput->WasKeyPressed(VK_LBUTTON))
		{
			if (m_routine != nullptr)
			{
				m_routine();
			}
		}
	}

	g_pMenuRender->text(m_name, pos.x + (width / 2), pos.y + 5, textCol, FONT_CENTERED | FONT_DROPSHADOW);
}
