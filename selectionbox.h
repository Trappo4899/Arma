#pragma once

class CSelectionBox : public CElement
{
private:

	std::vector<const char*> m_options;
	int m_selected;

	Vector2 m_size;

public:

	CSelectionBox(std::vector<const char*> options, int defSelected, Vector2 size);

public:

	void add(const char* option);
	void remove(const char* option);

	void think(Vector2 pos, Vector2 size) override;
};