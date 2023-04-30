#include "includes.h"

CGroup::CGroup(const char* name, Vector2 pos, Vector2 size)
{
	m_name = name;
	m_pos = { pos.x + 13, pos.y + 35 };
	m_size = size;
	m_padding = { };
	m_elements = { };
	m_view_padding = { 0.f, m_size.y - 22.5f };
	m_scroll_pos = { m_pos.x + m_size.x - 8, m_pos.y + 4.f };
}

bool CGroup::in_view(Vector2 pad)
{
	return pad.y >= m_view_padding.x && pad.y <= m_view_padding.y;
}

void CGroup::group_base()
{
	g_pMenuRender->rect(m_pos.x - 1, m_pos.y - 1, m_size.x, m_size.y, 1, ImColor(0, 0, 0));
	g_pMenuRender->rect_filled(m_pos.x, m_pos.y, m_size.x - 2, m_size.y - 2, ImColor(25, 25, 25));
	g_pMenuRender->rect(m_pos.x, m_pos.y, m_size.x - 2, m_size.y - 2, 1, ImColor(45, 45, 45));
	g_pMenuRender->text(m_name, m_pos.x + 11, m_pos.y - 5, ImColor(255, 255, 255));
}

void CGroup::handle_scrollbar_vertical()
{
	if (m_padding.y < m_size.y)
	{
		return;
	}

	ImColor barCol = ImColor(175, 175, 175, 150);

	static float relative = 0.f;

	float bar_height = (m_padding.y / m_elements.size()) * 4.f;

	if (g_pInput->CursorInMenuRegion(m_scroll_pos.x, m_scroll_pos.y, 4.f, bar_height) && !g_pMenu->m_waiting)
	{
		g_pMenu->m_hovering = true;

		barCol = ImColor(200, 200, 200, 150);

		if (g_pInput->WasKeyPressed(VK_LBUTTON))
		{
			m_scrolling = true;

			relative = ((g_pInput->GetCursor().y - 7) - ((m_pos.y + 4.f + m_view_padding.x)));
		}
	}

	if (m_scrolling)
	{
		barCol = ImColor(200, 200, 200, 175);

		g_pMenu->m_waiting = true;

		float top_of_scrollbar = m_pos.y + 2.f;
		float bottom_of_scrollbar = m_size.y - (bar_height / 2.f);

		m_scroll_pos.y = std::clamp<float>((g_pInput->GetCursor().y - 7) - relative, top_of_scrollbar, bottom_of_scrollbar);

		float total_scroll_range = bottom_of_scrollbar - top_of_scrollbar;
		float current_scroll_position = m_scroll_pos.y - top_of_scrollbar;

		float fraction = current_scroll_position / total_scroll_range;

		m_view_padding.x = (fraction * (m_padding.y - m_size.y));
		m_view_padding.y = (m_view_padding.x + m_size.y) - 22.f;

		if (!g_pInput->IsKeyDown(VK_LBUTTON))
		{
			m_scrolling = false;
		}
	}

	//g_pMenuRender->rect_filled(0, m_view_padding.x + m_pos.y, 10, 1, ImColor(255, 255, 255, 255));
	//g_pMenuRender->rect_filled(0, m_view_padding.y + m_pos.y, 10, 1, ImColor(255, 255, 255, 255));

	g_pMenuRender->rect_filled(m_scroll_pos.x, m_scroll_pos.y, 4.f, bar_height, barCol);
}

void CGroup::handle_elements()
{
	for (int i = 0; i < m_elements.size(); i++)
	{
		auto element = m_elements.at(i);

		bool should_pad = i != m_elements.size();

		switch (element.second)
		{
		case CHECKBOX:
		{
			auto el = (CCheckbox*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}

			break;
		}
		case SLIDER:
		{
			auto el = (CSlider*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}
			break;
		}
		case BUTTON:
		{
			auto el = (CButton*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}
			break;
		}
		case DROPDOWN:
		{
			auto el = (CDropdown*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}
			break;
		}
		case MULTIDROPDOWN:
		{
			auto el = (CMultiDropdown*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}

			break;
		}
		case COLOURPICKER:
		{
			auto el = (CColourPicker*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}

			break;
		}
		case KEYBIND:
		{
			auto el = (CKeybind*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}

			break;
		}
		case TEXTBOX:
		{
			auto el = (CTextBox*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}

			break;
		}
		case TEXT:
		{
			auto el = (CText*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}

			break;
		}

		case SELECTIONBOX:
		{
			auto el = (CSelectionBox*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}

			break;
		}

		case CONFIGBOX:
		{
			auto el = (CSelectionBox*)element.first;

			if (this->in_view(m_padding))
			{
				el->think({ m_pos.x + m_real_padding.x, m_pos.y + m_real_padding.y }, m_size);

				if (should_pad)
				{
					m_real_padding.x += el->m_padding.x;
					m_real_padding.y += el->m_padding.y;
				}
			}

			if (should_pad)
			{
				m_padding.x += el->m_padding.x;
				m_padding.y += el->m_padding.y;
			}

			break;
		}
		}
	}
}

void CGroup::add_element(CCheckbox* element)
{
	m_elements.push_back({ (void*)element, CHECKBOX });
}

void CGroup::add_element(CButton* element)
{
	m_elements.push_back({ (void*)element, BUTTON });
}

void CGroup::add_element(CSlider* element)
{
	m_elements.push_back({ (void*)element, SLIDER });
}

void CGroup::add_element(CDropdown* element)
{
	m_elements.push_back({ (void*)element, DROPDOWN });
}

void CGroup::add_element(CMultiDropdown* element)
{
	m_elements.push_back({ (void*)element, MULTIDROPDOWN });
}

void CGroup::add_element(CColourPicker* element)
{
	m_elements.push_back({ (void*)element, COLOURPICKER });
}

void CGroup::add_element(CKeybind* element)
{
	m_elements.push_back({ (void*)element, KEYBIND });
}

void CGroup::add_element(CTextBox* element)
{
	m_elements.push_back({ (void*)element, TEXTBOX });
}

void CGroup::add_element(CText* element)
{
	m_elements.push_back({ (void*)element, TEXT });
}

void CGroup::add_element(CSelectionBox* element)
{
	m_elements.push_back({ (void*)element, SELECTIONBOX });
}

void CGroup::add_element(CConfigBox* element)
{
	m_elements.push_back({ (void*)element, CONFIGBOX });
}

void CGroup::think()
{
	group_base();

	handle_elements();

	handle_scrollbar_vertical();

	m_padding = { };
	m_real_padding = { };
}