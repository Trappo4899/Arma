#include "includes.h"

CText::CText(std::string text)
{
	m_text = text;
	m_padding = { 0.f, 25.f };
}

void CText::think(Vector2 pos, Vector2 size)
{
	pos.x += 32;
	pos.y += 15;

	g_pMenuRender->text(m_text, pos.x, pos.y, ImColor(150, 150, 150), FONT_DROPSHADOW);
}
