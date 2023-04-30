#pragma once

class CTextBox : public CElement
{
private:

	std::unordered_map<int, std::string> vkInputKeys = {
    {32, " "},
    {9, "   "},
	{37, "Left"},
	{39, "Right"},
    {46, "Del"},
    {48, "0"},
    {49, "1"},
    {50, "2"},
    {51, "3"},
    {52, "4"},
    {53, "5"},
    {54, "6"},
    {55, "7"},
    {56, "8"},
    {57, "9"},
    {65, "A"},
    {66, "B"},
    {67, "C"},
    {68, "D"},
    {69, "E"},
    {70, "F"},
    {71, "G"},
    {72, "H"},
    {73, "I"},
    {74, "J"},
    {75, "K"},
    {76, "L"},
    {77, "M"},
    {78, "N"},
    {79, "O"},
    {80, "P"},
    {81, "Q"},
    {82, "R"},
    {83, "S"},
    {84, "T"},
    {85, "U"},
    {86, "V"},
    {87, "W"},
    {88, "X"},
    {89, "Y"},
    {90, "Z"},
	};

    std::unordered_map<int, std::string> vkCaps = {
{65, "A"},
{66, "B"},
{67, "C"},
{68, "D"},
{69, "E"},
{70, "F"},
{71, "G"},
{72, "H"},
{73, "I"},
{74, "J"},
{75, "K"},
{76, "L"},
{77, "M"},
{78, "N"},
{79, "O"},
{80, "P"},
{81, "Q"},
{82, "R"},
{83, "S"},
{84, "T"},
{85, "U"},
{86, "V"},
{87, "W"},
{88, "X"},
{89, "Y"},
{90, "Z"},
    };

    std::unordered_map<int, std::string> vkLower = {
{65, "a"},
{66, "b"},
{67, "c"},
{68, "d"},
{69, "e"},
{70, "f"},
{71, "g"},
{72, "h"},
{73, "i"},
{74, "j"},
{75, "k"},
{76, "l"},
{77, "m"},
{78, "n"},
{79, "o"},
{80, "p"},
{81, "q"},
{82, "r"},
{83, "s"},
{84, "t"},
{85, "u"},
{86, "v"},
{87, "w"},
{88, "x"},
{89, "y"},
{90, "z"},
    };

private:

	const char* m_name;
	std::string m_text;
    std::string m_last_action;

	bool m_typing;
    bool m_selected_all;

public:

	CTextBox(const char* name);

	std::string GetText();
    void SetText(const std::string& text);

	void think(Vector2 pos, Vector2 size) override;
};