#pragma once

class CMultiDropdown : public CElement
{
private:

	const char* m_name;

	std::vector<const char*> m_options;
	std::vector<int> m_selected;

	bool m_open;

public:

	CMultiDropdown(const char* name, std::vector<const char*> options, std::vector<int> defSeleceted = { -1 });

	bool is_selected(int option);

	void think(Vector2 pos, Vector2 size) override;
};