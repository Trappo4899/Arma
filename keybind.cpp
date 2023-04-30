#include "includes.h"

CKeybind::CKeybind(INT_PTR defKey, KeybindType defType, bool canChange)
{
	m_key = defKey;
	m_type = defType;
	m_can_change_type = canChange;
}

bool CKeybind::IsActive()
{
	switch (m_type)
	{
	case HOLD:
		return g_pInput->IsKeyDown(m_key);
	case TOGGLE:
		return g_pInput->GetState(m_key);
	case ALWAYS_ON:
		return true;
	case OFF_KEYBIND:
		return !g_pInput->IsKeyDown(m_key);
	}

	return false;
}

void CKeybind::think(Vector2 pos, Vector2 size)
{
	int textlen = strlen(m_str_key.c_str()) * 2;

	pos.x += (size.x - (40 + textlen));
	pos.y += 15;

	g_pMenuRender->rect(pos.x - 1, pos.y - 1, 30 + textlen, 17, 1, ImColor(0, 0, 0));
	g_pMenuRender->rect_filled(pos.x, pos.y, 27 + textlen, 15, ImColor(20, 20, 20));
	g_pMenuRender->rect(pos.x, pos.y, 27 + textlen, 15, 1, ImColor(45, 45, 45));

	ImColor textCol = ImColor(150, 150, 150);

	static bool should_skip = false;

	if (g_pInput->CursorInMenuRegion(pos.x - 1, pos.y - 1, 27, 17) && !g_pMenu->m_waiting)
	{
		textCol = ImColor(200, 200, 200);

		if (g_pInput->WasKeyPressed(VK_LBUTTON))
		{
			m_waiting_for_key = true;
			should_skip = true;
		}

		if(g_pInput->WasKeyPressed(VK_RBUTTON))
		{
			m_change_type = true;
		}
	}

	if (m_change_type && m_can_change_type)
	{
		g_pMenuRender->rect(pos.x - 1, pos.y + 20 - 1, 100 + 2, 80 + 2, 1, ImColor(0, 0, 0), CRender::ZPanel::Z_One);
		g_pMenuRender->rect_filled(pos.x, pos.y + 20, 100, 80, ImColor(25, 25, 25), CRender::ZPanel::Z_One);
		g_pMenuRender->rect(pos.x, pos.y + 20, 100, 80, 1, ImColor(45, 45, 45), CRender::ZPanel::Z_Two);

		ImColor holdTextCol = ImColor(150, 150, 150);
		ImColor toggleTextCol = ImColor(150, 150, 150);
		ImColor alwaysTextCol = ImColor(150, 150, 150);
		ImColor offTextCol = ImColor(150, 150, 150);

		if (g_pInput->CursorInMenuRegion(pos.x, pos.y + 20, 100, 20))
		{
			holdTextCol = ImColor(200, 200, 200);

			g_pMenuRender->rect_filled(pos.x, pos.y + 20, 100, 20, ImColor(15, 15, 15), CRender::ZPanel::Z_One);

			if(g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_type = HOLD;
			}
		}

		if (g_pInput->CursorInMenuRegion(pos.x, pos.y + 40, 100, 20))
		{
			toggleTextCol = ImColor(200, 200, 200);

			g_pMenuRender->rect_filled(pos.x, pos.y + 40, 100, 20, ImColor(15, 15, 15), CRender::ZPanel::Z_One);

			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_type = TOGGLE;
			}
		}

		if (g_pInput->CursorInMenuRegion(pos.x, pos.y + 60, 100, 20))
		{
			alwaysTextCol = ImColor(200, 200, 200);

			g_pMenuRender->rect_filled(pos.x, pos.y + 60, 100, 20, ImColor(15, 15, 15), CRender::ZPanel::Z_One);

			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_type = ALWAYS_ON;
			}
		}

		if (g_pInput->CursorInMenuRegion(pos.x, pos.y + 80, 100, 20))
		{
			offTextCol = ImColor(200, 200, 200);

			g_pMenuRender->rect_filled(pos.x, pos.y + 80, 100, 20, ImColor(15, 15, 15), CRender::ZPanel::Z_One);

			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_type = OFF_KEYBIND;
			}
		}

		switch (m_type)
		{
		case OFF_KEYBIND:
			offTextCol = g_pMenu->m_accent;
			break;

		case ALWAYS_ON:
			alwaysTextCol = g_pMenu->m_accent;
			break;

		case TOGGLE:
			toggleTextCol = g_pMenu->m_accent;
			break;

		case HOLD:
			holdTextCol = g_pMenu->m_accent;
			break;
		}

		g_pMenuRender->text("hold", pos.x + 50.f, pos.y + 25.f, holdTextCol, FONT_CENTERED | FONT_DROPSHADOW, CRender::ZPanel::Z_One);
		g_pMenuRender->text("toggle", pos.x + 50.f, pos.y + 45.f, toggleTextCol, FONT_CENTERED | FONT_DROPSHADOW, CRender::ZPanel::Z_One);
		g_pMenuRender->text("always on", pos.x + 50.f, pos.y + 65.f,alwaysTextCol, FONT_CENTERED | FONT_DROPSHADOW, CRender::ZPanel::Z_One);
		g_pMenuRender->text("off hotkey", pos.x + 50.f, pos.y + 85.f, offTextCol, FONT_CENTERED | FONT_DROPSHADOW, CRender::ZPanel::Z_One);

		if (g_pInput->WasKeyPressed(VK_LBUTTON))
		{
			m_change_type = false;
		}
	}

	if (m_waiting_for_key)
	{
		g_pMenu->m_waiting = true;

		m_str_key = "...";

		for (int i = 0; i < 0x100; i++)
		{
			if (should_skip && i == VK_LBUTTON)
			{
				continue;
			}

			if (g_pInput->WasKeyPressed(i) && i != VK_ESCAPE)
			{
				m_key = i;
				m_waiting_for_key = false;
				break;
			}
		}

		if (g_pInput->WasKeyPressed(VK_ESCAPE))
		{
			m_key = -1;
			m_waiting_for_key = false;
		}

		should_skip = false;
	}

	if (m_key == -1)
	{
		m_str_key = "-";
	}
	else
	{
		if (vkKeyMap.count(m_key))
		{
			m_str_key = vkKeyMap.at(m_key);
		}
		else
		{
			m_str_key = std::to_string(m_key);
		}
	}

	g_pMenuRender->text(m_str_key, pos.x + 15.5f + strlen(m_str_key.c_str()), pos.y + 2.5f, ImColor(150, 150, 150), FONT_CENTERED | FONT_DROPSHADOW);
}