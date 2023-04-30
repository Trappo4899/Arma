#pragma once
#undef DrawText

enum BOX_POSITION
{
	TOP = 1,
	BOTTOM = 2,

	LEFT = 4,
	RIGHT = 8,
};

class CVisuals
{
private:

	Vector2 m_padding_top				= { };
	Vector2 m_padding_bottom			= { };
	Vector2 m_padding_left				= { };
	Vector2 m_padding_right				= { };

private:

	void DrawBox(const Entity& ent);

	void DrawBar(Box box, float value, float max, ImColor colour, ImColor colour2, BOX_POSITION boxPos);
	void DrawGradientBar(Box box, float value, float max, ImColor colour, ImColor colour2, BOX_POSITION boxPos);
	void DrawText(Box box, const char* text, ImColor colour, int fontFlags, BOX_POSITION boxPos, bool pixel = false);

	BOX_POSITION GetBoxPos(int option);

private:

	void handle_players(Entity ent);
	void handle_vehicles(Vehicle veh);
	void handle_wildlife(Entity ent);

public:

	bool GetBox(Entity ent, Box& box);

	void think(const EntityList&);
};

extern std::unique_ptr<CVisuals> g_pVisuals;