#include "includes.h"

CColourPicker::CColourPicker(const char* name, ImColor colour, bool showName)
{
	m_name = name;
	m_default = colour;
	m_colour = colour;
	m_show_name = showName;
}

ImColor CColourPicker::get_colour()
{
	return m_colour;
}

void CColourPicker::think(Vector2 pos, Vector2 size)
{
	pos.x += (size.x - 26);
	pos.y += 15;

	static const float width = 12;
	static const float height = 8;

	static const float col_width = 160;
	static const float col_height = 160;

	g_pMenuRender->rect(pos.x - 1, pos.y - 1, width + 2, height + 2, 1, ImColor(0, 0, 0));
	g_pMenuRender->gradient(pos.x, pos.y, width, height, ImColor(m_colour.Value.x - (30.f / 255.f), m_colour.Value.y - (30.f / 255.f), m_colour.Value.z - (30.f / 255.f)), m_colour);

	if (g_pInput->CursorInMenuRegion(pos.x - 2, pos.y - 2, width + 4, height + 4))
	{
		g_pMenu->m_hovering = true;

		if (g_pInput->WasKeyPressed(VK_LBUTTON))
		{
			m_open = true;
		}
		else if (g_pInput->WasKeyPressed(VK_RBUTTON))
		{
			m_open_two = true;
		}
	}

	if (m_open_two)
	{
		g_pMenu->m_waiting = true;

		g_pMenuRender->rect(pos.x - 1, pos.y + height + 9,		100 + 2, 60 + 2, 1, ImColor(0, 0, 0), CRender::ZPanel::Z_One);
		g_pMenuRender->rect_filled(pos.x, pos.y + height + 10,	100, 60, ImColor(25, 25, 25), CRender::ZPanel::Z_One);
		g_pMenuRender->rect(pos.x, pos.y + height + 10, 100, 60, 1, ImColor(45, 45, 45), CRender::ZPanel::Z_Two);

		ImColor textCol1 = ImColor(150, 150, 150);
		ImColor textCol2 = ImColor(150, 150, 150);
		ImColor textCol3 = ImColor(150, 150, 150);

		/* copy */
		if (g_pInput->CursorInMenuRegion(pos.x - 1, pos.y + height + 10, 100 + 2, 20))
		{
			textCol1 = ImColor(200, 200, 200);		

			g_pMenuRender->rect_filled(pos.x - 1, pos.y + height + 10, 100 + 2, 20, ImColor(15, 15, 15), CRender::ZPanel::Z_One);

			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				util::CopyToClipboard(util::RgbToHex(m_colour));
			}
		}

		/* paste */
		if (g_pInput->CursorInMenuRegion(pos.x - 1, pos.y + height + 30, 100 + 2, 20))
		{
			textCol2 = ImColor(200, 200, 200);

			g_pMenuRender->rect_filled(pos.x - 1, pos.y + height + 30, 100 + 2, 20, ImColor(15, 15, 15), CRender::ZPanel::Z_One);

			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_colour = util::HexToRgb(util::GetClipboardText());
			}
		}

		/* reset */
		if (g_pInput->CursorInMenuRegion(pos.x - 1, pos.y + height + 50, 100 + 2, 20))
		{
			textCol3 = ImColor(200, 200, 200);

			g_pMenuRender->rect_filled(pos.x - 1, pos.y + height + 50, 100 + 2, 20, ImColor(15, 15, 15), CRender::ZPanel::Z_One);

			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_colour = m_default;
			}
		}

		g_pMenuRender->text("copy", pos.x	+ 50, pos.y + height + 15, textCol1, FONT_CENTERED | FONT_DROPSHADOW, CRender::ZPanel::Z_One);
		g_pMenuRender->text("paste", pos.x	+ 50, pos.y + height + 35, textCol2, FONT_CENTERED | FONT_DROPSHADOW, CRender::ZPanel::Z_One);
		g_pMenuRender->text("reset", pos.x	+ 50, pos.y + height + 55, textCol3, FONT_CENTERED | FONT_DROPSHADOW, CRender::ZPanel::Z_One);

		if (!g_pInput->CursorInMenuRegion(pos.x - 2, pos.y - 2, width + 4, height + 4))
		{
			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_open_two = false;
			}
		}
	}

	if (m_open)
	{
		g_pMenu->m_waiting = true;

		g_pMenuRender->rect(pos.x - 1, pos.y + height + 10 - 1, col_width + 2, col_height + 2, 1, ImColor(0, 0, 0), CRender::ZPanel::Z_One);
		g_pMenuRender->rect_filled(pos.x, pos.y + height + 10, col_width, col_height, ImColor(25, 25, 25), CRender::ZPanel::Z_One);
		g_pMenuRender->rect(pos.x, pos.y + height + 10, col_width, col_height, 1, ImColor(45, 45, 45), CRender::ZPanel::Z_One);

		/* variables for changing the value */

		float hue = 0.f;
		float saturation = 0.f;
		float value = 0.f;
		float alpha = m_colour.Value.w;

		ImGui::ColorConvertRGBtoHSV(m_colour.Value.x, m_colour.Value.y, m_colour.Value.z, hue, saturation, value);

		ImColor hue_colour = ImColor::HSV(hue, 1.f, 1.f); // #1F1F1F

		/* draw hue bar */

		static const std::vector<ImColor> colours = {
			ImColor(255, 0, 0),
			ImColor(255, 255, 0),
			ImColor(0, 255, 0),
			ImColor(0, 255, 255),
			ImColor(0, 0, 255),
			ImColor(255, 0, 255),
			ImColor(255, 0, 0)
		};

		g_pMenuRender->rect(pos.x + col_width - 13, pos.y + height + 13, 10.f, col_height - 18.f, 1, ImColor(0, 0, 0));

		for (int i = 0; i < colours.size() - 1; i++)
		{
			g_pMenuRender->gradient(
				pos.x + col_width - 12,
				pos.y + height + 14 + (i * ((col_height - 20.f) / (colours.size() - 1))),
				8.f,
				((col_height - 20.f) / (colours.size() - 1)),
				colours.at(i),
				colours.at(i + 1), 
				CRender::ZPanel::Z_One
				);
		}

		/* draw main picker */

		g_pMenuRender->rect(pos.x + 3.f, pos.y + height + 13.f, col_width - 18.f, col_height - 18.f, 1.f, ImColor(0, 0, 0, 255)
			, CRender::ZPanel::Z_One);

		g_pMenuRender->gradient3(pos.x + 4.f, pos.y + height + 14.f, col_width - 20.f, col_height - 20.f,
			ImColor(255, 255, 255, 255),
			ImColor(hue_colour.Value.x, hue_colour.Value.y, hue_colour.Value.z, 1.f),
			ImColor(hue_colour.Value.x, hue_colour.Value.y, hue_colour.Value.z, 0.f),
			ImColor(0, 0, 0, 0), CRender::ZPanel::Z_One);

		g_pMenuRender->gradient3(pos.x + 4.f, pos.y + height + 14, col_width - 20.f, col_height - 20.f,
			ImColor(0, 0, 0, 0),
			ImColor(0, 0, 0, 0),
			ImColor(0, 0, 0, 255),
			ImColor(0, 0, 0, 255), CRender::ZPanel::Z_One);

		/* draw alpha bar */

		g_pMenuRender->rect_filled(pos.x + 3.f, pos.y + height + col_height - 3.f, col_width - 17.f, 10.f, ImColor(0, 0, 0, 255)
			, CRender::ZPanel::Z_One);
		g_pMenuRender->rect_filled(pos.x + 4.f, pos.y + height + col_height - 2.f, col_width - 19.f, 8.f, m_colour, 
			CRender::ZPanel::Z_One);

		/* hue bar input */
		
		if (g_pInput->CursorInMenuRegion(pos.x + col_width - 13, pos.y + height + 13, 10.f, col_height - 18.f))
		{
			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_sliding_hue = true;
			}
		}

		if (m_sliding_hue)
		{
			float hue_pixels				= ((g_pInput->GetCursor().y - 7) - (pos.y + height + 13 + g_pMenu->m_pos.y));

			/* fix visual bug with crosshair if pos of crosshair */
			if (hue_pixels < 0.f)
			{
				hue_pixels = 0.f;
			}
			else if (hue_pixels >= (col_height - 18.f) - 2.f)
			{
				hue_pixels = (col_height - 18.f) - 2.f;
			}

			float hue_pixels_clamp			= std::clamp<float>(hue_pixels, 0.f, col_height - 18.f);
			float hue_value_fraction		= (hue_pixels_clamp / (col_height - 18.f));

			hue = hue_value_fraction;

			/* handle closing */
			if (!g_pInput->IsKeyDown(VK_LBUTTON))
			{
				m_sliding_hue = false;
			}
		}

		if (g_pInput->CursorInMenuRegion(pos.x + 3.f, pos.y + height + 13.f, col_width - 18.f, col_height - 18.f))
		{
			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_sliding_sat = true;
			}
		}

		if (m_sliding_sat)
		{
			float sat_pixels				= ((g_pInput->GetCursor().x - 7) - (pos.x + 3.f + g_pMenu->m_pos.x));
			float val_pixels				= ((g_pInput->GetCursor().y - 7) - (pos.y + height + 13.f + g_pMenu->m_pos.y));

			/* fix visual bug with crosshair if pos of crosshair */
			if (sat_pixels < 0.f)
			{
				sat_pixels = 0.f;
			}
			else if (sat_pixels >= (col_width - 18.f) - 2.f)
			{
				sat_pixels = (col_width - 18.f) - 2.f;
			}

			/* fix visual bug with crosshair if pos of crosshair */
			if (val_pixels < 0.f)
			{
				val_pixels = 0.f;
			}
			else if (val_pixels >= (col_height - 18.f) - 2.f)
			{
				val_pixels = (col_height - 18.f) - 2.f;
			}

			float sat_pixels_clamp			= std::clamp<float>(sat_pixels, 0.f, col_width - 18.f);
			float val_pixels_clamp			= std::clamp<float>(val_pixels, 0.f, col_height - 18.f);

			float sat_pixels_fraction		= (sat_pixels_clamp / (col_width - 18.f));
			float val_pixels_fraction		= (val_pixels_clamp / (col_height - 18.f));

			value							= 1.0f - val_pixels_fraction;
			saturation						= value == 0 ? 0.f : sat_pixels_fraction;

			/* handle closing */
			if (!g_pInput->IsKeyDown(VK_LBUTTON))
			{
				m_sliding_sat = false;
			}
		}

		if (g_pInput->CursorInMenuRegion(pos.x + 3.f, pos.y + height + col_height - 3.f, col_width - 17.f, 10.f))
		{
			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_sliding_alpha = true;
			}
		}

		if (m_sliding_alpha)
		{
			float alpha_pixels				= ((g_pInput->GetCursor().x - 7) - (pos.x + 3.f + g_pMenu->m_pos.x));
			float alpha_pixels_clamp		= std::clamp<float>(alpha_pixels, 0.f, col_width - 17.f);
			float alpha_value_fraction		= (alpha_pixels_clamp / (col_width - 17.f));

			alpha = alpha_value_fraction * 1.f;

			/* handle closing */
			if (!g_pInput->IsKeyDown(VK_LBUTTON))
			{
				m_sliding_alpha = false;
			}
		}

		/* draw picker crosshair */
		g_pMenuRender->rect_filled((pos.x + 4.f + (col_width - 20.f) * (saturation / 1.0f)) - 1,	(pos.y + height + 10.f + (col_height - 20.f) * (1.0f - (value / 1.0f))) + 3, 3, 3, ImColor(0, 0, 0, 255), CRender::ZPanel::Z_One);
		g_pMenuRender->rect_filled((pos.x + 4.f + (col_width - 20.f) * (saturation / 1.0f)),		(pos.y + height + 10.f + (col_height - 20.f) * (1.0f - (value / 1.0f))) + 4, 1, 1, ImColor(255, 255, 255, 255), CRender::ZPanel::Z_One);

		/* draw hue bar crosshair */
		g_pMenuRender->rect_filled((pos.x + col_width - 14.f), ((pos.y + height + 13.f) + (hue * (col_height - 18.f))) - 1.f, 12.f,   3.f, ImColor(0, 0, 0, 255), CRender::ZPanel::Z_One);
		g_pMenuRender->rect_filled((pos.x + col_width - 14.f) + 1.f, ((pos.y + height + 13.f) + (hue * (col_height - 18.f))),				10.f,	1.f, ImColor(255, 255, 255, 255), CRender::ZPanel::Z_One);

		/* draw alpha bar crosshair */
		g_pMenuRender->rect_filled((pos.x + 4.f + (col_width - 19.f) * alpha) - 1, (pos.y + height + col_height - 2.f)	- 2,		3,  12, ImColor(0, 0, 0, 255), CRender::ZPanel::Z_One);
		g_pMenuRender->rect_filled((pos.x + 4.f + (col_width - 19.f) * alpha), (pos.y + height + col_height - 2.f)		- 1,		1,	10, ImColor(255, 255, 255, 255), CRender::ZPanel::Z_One);

		m_colour = ImColor::HSV(hue, saturation, value);
		m_colour.Value.w = alpha;
		
		/* handle closing */
		if (!g_pInput->CursorInMenuRegion(pos.x - 2, pos.y + height + 6 - 2, col_width + 4, col_height + 4) &&
			!g_pInput->CursorInMenuRegion(pos.x - 2, pos.y - 2, width + 4, height + 4))
		{
			if (g_pInput->WasKeyPressed(VK_LBUTTON))
			{
				m_open = false;
			}
		}
	}
}