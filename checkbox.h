#pragma once

class CCheckbox : public CElement
{
	friend class CGroup;
private:

	bool m_on;

public:

	CCheckbox(const char* name, bool def);

	bool active();

	void think(Vector2 pos, Vector2 size) override;
};