#include "includes.h"

CSelectionBox::CSelectionBox(std::vector<const char*> options, int defSelected, Vector2 size)
{
	m_options = options;
	m_selected = defSelected;
	m_size = size;
}

void CSelectionBox::add(const char* option)
{
	m_options.push_back(option);
}

void CSelectionBox::remove(const char* option)
{
	for (int i = 0; i < m_options.size(); i++)
	{
		if (_stricmp(option, m_options.at(i)) == 0)
		{
			m_options.erase(m_options.begin() + i);
		}
	}
}

void CSelectionBox::think(Vector2 pos, Vector2 size)
{
	if (m_size.x == 0.f || m_size.y == 0.f)
	{
		m_size.x = size.x;
		m_size.y = size.y;
	}

	pos.x += 15;
	pos.y += 15;

	g_pMenuRender->rect(pos.x - 1, pos.y - 1, m_size.x + 2, m_size.y + 2, 1, ImColor(0, 0, 0));
	g_pMenuRender->rect_filled(pos.x, pos.y, m_size.x, m_size.y, ImColor(35, 35, 35));
	g_pMenuRender->rect(pos.x, pos.y, m_size.x, m_size.y, 1, ImColor(45, 45, 45));

	ImColor textCol = ImColor(150, 150, 150);

	for (int i = 0; i < m_options.size(); i++)
	{
		if (g_pInput->CursorInMenuRegion(pos.x, pos.y + (i * 20), m_size.x, 20))
		{
			textCol = ImColor(200, 200, 200);

			g_pMenuRender->rect_filled(pos.x, pos.y + (i * 20), m_size.x, 20, ImColor(25, 25, 25));
		}

		g_pMenuRender->text(m_options.at(i), pos.x + 4.f, pos.y + (i * 20) + 5.f, textCol, FONT_DROPSHADOW);
	}
}