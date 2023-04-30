#pragma once

class CColourPicker : public CElement
{
	/*
	
	possibly when showing the boxes for input take into account
	were the cursor was when it clicked on the box
	
	*/

private:

	const char* m_name;
	bool m_show_name;
	ImColor m_default;
	ImColor m_colour;

	bool m_open;
	bool m_open_two;

	bool m_sliding_hue;
	bool m_sliding_sat;
	bool m_sliding_alpha;

public:

	CColourPicker(const char* name, ImColor colour, bool showName = false);

	ImColor get_colour();

	void think(Vector2 pos, Vector2 size) override;
};