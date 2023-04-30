#pragma once

typedef bool(__stdcall* tShowCallback)();

class CElement
{
	friend class CGroup;
protected: /* variables for all elements */

	Vector2 m_padding;
	Vector2 m_size = { };

	const char* m_name;

	/* intialize this here cause i cba going through all the fucking constructors */
	tShowCallback m_show_callback = nullptr;

public:

	void add_show_callback(tShowCallback showCallback);

	bool can_show();

	virtual void think(Vector2 pos, Vector2 size);
};