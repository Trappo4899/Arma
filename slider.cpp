#include "includes.h"

CSlider::CSlider(const char* name, const char* typeDisplay, float max, float min, float defValue)
{
	m_name = name;
	m_type_display = typeDisplay;
	m_max = max;
	m_min = min;
	m_val = defValue;
	m_padding = { 0.f, 30 };
}

void CSlider::think(Vector2 pos, Vector2 size)
{
	pos.x += 32;
	pos.y += 15;

	static const float width = (size.x / 2.f);

	g_pMenuRender->rect(pos.x - 1, pos.y + 10 - 1, width + 2, 8, 1, ImColor(0, 0, 0));
	g_pMenuRender->gradient(pos.x, pos.y + 10, width, 6, ImColor(35, 35, 35), ImColor(50, 50, 50));

	float val_width = ((m_val - m_min) * width / (m_max - m_min));

	ImColor accent = g_pMiscSettings->m_accent->get_colour();
	g_pMenuRender->rect_filled(pos.x, pos.y + 10, val_width, 6, accent);

	ImColor textCol = ImColor(150, 150, 150);

	if (g_pInput->CursorInMenuRegion(pos.x - 4, pos.y - 3, width + 12, 24) && !g_pMenu->m_waiting)
	{
		g_pMenu->m_hovering = true;

		textCol = ImColor(200, 200, 200);

		if (g_pInput->IsKeyDown(VK_LBUTTON))
		{
			m_sliding = true;
		}
	}
	else if (m_sliding)
	{
		textCol = ImColor(200, 200, 200);
	}

	g_pMenuRender->text(m_name, pos.x, pos.y - 2, textCol, FONT_DROPSHADOW);

	std::string str_val = std::string(std::to_string(m_val));

	/* subtract most of the precision of the float so we dont display it all only 1 decimal of it */
	str_val = str_val.substr(0, str_val.size() - 5) + m_type_display;

	g_pMenuRender->text(str_val.c_str(), pos.x + width, pos.y - 2, textCol, FONT_RIGHT | FONT_DROPSHADOW);

	if (m_sliding)
	{
		g_pMenu->m_waiting = true;

		/* get the difference from the the start of the slider to where the cursor is */
		float pixels = ((g_pInput->GetCursor().x - 7) - (pos.x + g_pMenu->m_pos.x));

		/* clamp the difference in pixels so we dont have to clamp the end value */
		float pixels_clamp = std::clamp<float>(pixels, 0.f, width);

		/* get the fraction of the difference in pixels to the width of the slider */
		float value_fraction = (pixels_clamp / width * (m_max - m_min) + m_min);

		/* use the fraction to get a value in between our min and max */
		m_val = std::clamp<float>(value_fraction, m_min, m_max);

		if (!g_pInput->IsKeyDown(VK_LBUTTON))
		{
			m_sliding = false;
		}
	}
}