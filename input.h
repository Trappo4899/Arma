#pragma once

class CInput
{
public:

	struct key_t
	{
		bool pressed;
		bool down;
		bool state;
	};

private:

	std::array<key_t, 0x100>	m_keys;
	POINT						m_cursor;

public:

	void update();

	POINT GetCursor();

	bool WasKeyPressed(UINT_PTR key);
	bool IsKeyDown(UINT_PTR key);
	bool GetState(UINT_PTR key);

	bool CursorInRegion(float x, float y, float w, float h);

	bool CursorInMenuRegion(float x, float y, float w, float h);

	std::array<key_t, 0x100> GetAllKeys();
};

extern std::unique_ptr<CInput> g_pInput;