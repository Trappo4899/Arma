#include "includes.h"

CTextBox::CTextBox(const char* name)
{
	m_name = name;
	m_text = { };
	m_padding = { 0.f, 25.f };
	m_typing = false;
	m_selected_all = false;
}

std::string CTextBox::GetText()
{
	return m_text;
}

void CTextBox::SetText(const std::string& text)
{
	m_text = text;
}

void CTextBox::think(Vector2 pos, Vector2 size)
{
	pos.x += 32;
	pos.y += 30;

	const float width = (size.x / 1.27f);

	g_pMenuRender->rect(pos.x - 1, pos.y - 1, width + 2, 17.f, 1, ImColor(0, 0, 0));
	g_pMenuRender->rect_filled(pos.x, pos.y, width, 15.f, ImColor(35, 35, 35));
	g_pMenuRender->rect(pos.x, pos.y, width, 15.f, 1, ImColor(45, 45, 45));

	if (!m_typing)
	{
		g_pMenuRender->text(m_text, pos.x + 4.f, pos.y + 2.f, ImColor(175, 175, 175));
	}

	ImColor textCol = ImColor(150, 150, 150);

	if (g_pInput->CursorInMenuRegion(pos.x - 1, pos.y - 1, width + 2, 17.f) && !g_pMenu->m_waiting)
	{
		textCol = ImColor(175, 175, 175);

		auto cursor = g_pInput->GetCursor();
		g_pMenuRender->line(pos.x + 6.f + (m_text.size() * 6.f), pos.y + 2.f, pos.x + 6.f + (m_text.size() * 6.f), pos.y + 12.f, 1, ImColor(200, 200, 200));

		if (g_pInput->WasKeyPressed(VK_LBUTTON))
		{
			m_typing = true;
		}
	}

	if (m_typing)
	{
		g_pMenu->m_waiting = true;

		textCol = ImColor(200, 200, 200);

		static bool m_select_one = false;

		if (m_selected_all)
		{
			g_pMenuRender->rect_filled(pos.x + 2.f, pos.y,(m_text.size() * 6.f) + 2.f, 14.f, ImColor(3, 78, 252, 75), CRender::ZPanel::Z_One);
		}

		if (g_pInput->IsKeyDown(17))
		{
			if (g_pInput->WasKeyPressed(65)) // ctrl + a
			{
				m_selected_all = true;
				m_select_one = true;
			}

			if (g_pInput->WasKeyPressed(67)) // ctrl + c
			{
				util::CopyToClipboard(m_text);
			}

			if (g_pInput->WasKeyPressed(86)) // ctrl + v
			{
				if (m_selected_all && !m_select_one)
				{
					m_selected_all = false;

					m_text = util::GetClipboardText();
				}
				else
				{
					m_text += util::GetClipboardText();
				}
			}
		}

		for (int i = 0; i < 0x100; i++)
		{
			if (g_pInput->WasKeyPressed(i))
			{
				/* is a letter */	/* is in one of the letters in the map*/
				if (i >= 65 && i <= 90 && vkCaps.count(i))
				{
					if (g_pInput->IsKeyDown(17))
					{
						continue;
					}

					/* if caps is on add the capital version*/
					if (g_pInput->GetState(20))
					{
						if (m_selected_all && !m_select_one)
						{
							m_text = vkCaps.at(i);
							m_selected_all = false;
						}
						else
						{
							m_text += vkCaps.at(i);
						}
					}
					else
					{
						if (m_selected_all && !m_select_one)
						{
							m_text = vkLower.at(i);
							m_selected_all = false;
						}
						else
						{
							m_text += vkLower.at(i);
						}
					}
				}
				else if (vkInputKeys.count(i))
				{
					if (m_selected_all && !m_select_one)
					{
						m_text = vkInputKeys.at(i);
						m_selected_all = false;
					}
					else
					{
						m_text += vkInputKeys.at(i);
					}
				}
			}
		}

		if (g_pInput->WasKeyPressed(8) && m_text.size() > 0)
		{
			if (m_selected_all && !m_select_one)
			{
				m_text = "";
				m_selected_all = false;
			}
			else
			{
				m_text.pop_back();
			}
		}

		if (g_pInput->WasKeyPressed(VK_LBUTTON) && m_selected_all && !m_select_one)
		{
			m_selected_all = false;
		}

		g_pMenuRender->text(m_text, pos.x + 4.f, pos.y + 2.f, ImColor(175, 175, 175));

		if (g_pInput->WasKeyPressed(VK_RETURN) || g_pInput->WasKeyPressed(VK_ESCAPE))
		{
			m_typing = false;
		}

		m_select_one = false;
	}

	pos.y -= 15;

	g_pMenuRender->text(m_name, pos.x, pos.y, textCol, FONT_DROPSHADOW);
}