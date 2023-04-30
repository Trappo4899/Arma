#include "includes.h"

CDropdown::CDropdown(const char* name, std::vector<const char*> options, int defSelected)
{
	m_name = name;
	m_options = options;
	m_selected = defSelected;
	m_padding = { 0.f, 37.5f };
}

int CDropdown::get_selected()
{
	return m_selected;
}

void CDropdown::think(Vector2 pos, Vector2 size)
{
	pos.x += 32;
	pos.y += 15;

	static const float width = (size.x / 2.f);
	static const float height = 18.f;

	g_pMenuRender->rect(pos.x - 1, pos.y + 10 - 1, width + 2, height + 2, 1, ImColor(0, 0, 0));
	g_pMenuRender->gradient(pos.x, pos.y + 10, width, height, ImColor(35, 35, 35), ImColor(50, 50, 50));

	ImColor textCol = ImColor(150, 150, 150);

	if (g_pInput->CursorInMenuRegion(pos.x - 4, pos.y - 4, width + 8, height + 14) && !g_pMenu->m_waiting)
	{
		g_pMenu->m_hovering = true;

		textCol = ImColor(200, 200, 200);

		if (g_pInput->WasKeyPressed(VK_LBUTTON))
		{
			m_open = true;
		}
	}

	g_pMenuRender->text(m_name, pos.x, pos.y - 2, textCol, FONT_DROPSHADOW);

	if (m_open)
	{
		g_pMenu->m_waiting = true;

		g_pMenuRender->rect(pos.x - 1, pos.y + 10 + height,		width + 2, (height * m_options.size()) + 2, 1, ImColor(0, 0, 0), CRender::ZPanel::Z_One);
		g_pMenuRender->gradient(pos.x, pos.y + 11 + height,	width, (height * m_options.size()), ImColor(35, 35, 35), ImColor(50, 50, 50), CRender::ZPanel::Z_One);
		g_pMenuRender->rect(pos.x, pos.y + 11 + height,			width, (height * m_options.size()), 1, ImColor(45, 45, 45), CRender::ZPanel::Z_Two);

		for (int i = 0; i < m_options.size(); i++)
		{
			ImColor currTextCol = ImColor(150, 150, 150);

			if (g_pInput->CursorInMenuRegion(pos.x - 1, pos.y + 12 + ((i + 1) * height), width + 2, height + 2))
			{
				g_pMenuRender->rect_filled(pos.x, pos.y + 11 + ((i + 1) * height), width, height, ImColor(25, 25, 25), CRender::ZPanel::Z_One);

				currTextCol = ImColor(200, 200, 200);

				if (g_pInput->WasKeyPressed(VK_LBUTTON))
				{
					if (m_selected == i)
					{
						m_selected = -1;
					}
					else
					{
						m_selected = i;
					}
				}
			}

			if (m_selected == i)
			{
				currTextCol = g_pMenu->m_accent;
			}

			g_pMenuRender->text(m_options.at(i), pos.x + 4, pos.y + 15 + ((i + 1) * height), currTextCol, 8, CRender::ZPanel::Z_One);
		}

		if (!g_pInput->CursorInMenuRegion(pos.x - 4, pos.y - 4, width + 8, (m_options.size() * height) + height + 18))
		{
			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_open = false;
			}
		}
	}

	g_pMenuRender->text(m_selected != -1 ? m_options.at(m_selected) : "-", pos.x + 4, pos.y + 15, ImColor(150, 150, 150));
}