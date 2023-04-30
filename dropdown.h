#pragma once

class CDropdown : public CElement
{
private:

	const char* m_name;

	std::vector<const char*> m_options;
	int m_selected;

	bool m_open;

public:

	CDropdown(const char* name, std::vector<const char*> options, int defSelected = -1);

	int get_selected();

	void think(Vector2 pos, Vector2 size) override;
};