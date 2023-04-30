#include "includes.h"

void CInput::update()
{
	for (int i = 0; i < 0x100; i++)
	{
		auto keystate = GetAsyncKeyState(i);

		/* if the most significant bit is set the key is down */
		m_keys[i].down = keystate & 0x8000;

		/* if the least significant bit is set the key was pressed since the last call to GetAsyncKeyState*/
		m_keys[i].pressed = keystate & 0x0001;

		m_keys[i].state = GetKeyState(i);
	}

	GetCursorPos(&m_cursor);
}

POINT CInput::GetCursor()
{
	return m_cursor;
}

bool CInput::WasKeyPressed(UINT_PTR key)
{
	if (key <= 0x100)
	{
		return m_keys[key].pressed;
	}

	return false;
}

bool CInput::IsKeyDown(UINT_PTR key)
{
	if (key <= 0x100)
	{
		return m_keys[key].down;
	}

	return false;
}

bool CInput::GetState(UINT_PTR key)
{
	if (key <= 0x100)
	{
		return m_keys[key].state;
	}

	return false;
}

bool CInput::CursorInRegion(float x, float y, float w, float h)
{
	//g_pRender->foreground.rect(x, y, w, h, 1, ImColor(255, 255, 255));
	y += 7; /* add the window start pos */
	x += 7; /* add the window start pos */
	return m_cursor.x > x && m_cursor.x < x + w && m_cursor.y > y && m_cursor.y < y + h;
}

bool CInput::CursorInMenuRegion(float x, float y, float w, float h)
{
	//g_pMenuRender->rect(x, y, w, h, 1, ImColor(255, 255, 255, 255), CRender::ZPanel::Z_Two);
	auto pos = g_pMenu->m_pos;
	return CursorInRegion(x + pos.x, y + pos.y, w, h);
}

std::array<CInput::key_t, 0x100> CInput::GetAllKeys()
{
	std::array<key_t, 0x100> ret = { };

	for (int i = 0; i < 0x100; i++)
	{
		auto keystate = GetAsyncKeyState(i);

		/* if the most significant bit is set the key is down */
		ret[i].down = keystate & 0x8000;

		/* if the least significant bit is set the key was pressed since the last call to GetAsyncKeyState*/
		ret[i].pressed = keystate & 0x0001;
	}

	return ret;
}
