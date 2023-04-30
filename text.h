#pragma once

class CText : public CElement
{
private:

	std::string m_text;

public:

	CText(std::string text);

	void think(Vector2 pos, Vector2 size) override;
};