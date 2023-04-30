#pragma once

class CKeybind : public CElement
{
private:

    std::unordered_map<int, std::string> vkKeyMap = {
    {1, "M1"},
    {2, "M2"},
    {4, "M3"},
    {5, "M4"},
    {6, "M5" },
    {8, "Back"},
    {9, "Tab"},
    {13, "Enter"},
    {16, "Shift"},
    {17, "Ctrl"},
    {18, "Alt"},
    {19, "Pause"},
    {20, "Caps"},
    {27, "Esc"},
    {32, "Space"},
    {33, "PU"},
    {34, "PD"},
    {35, "End"},
    {36, "Home"},
    {37, "Left"},
    {38, "Up"},
    {39, "Right"},
    {40, "Down"},
    {45, "Ins"},
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
    {91, "WLeft"},
    {92, "RLeft"},
    {93, "Apps"},
    {96, "Num 0"},
    {97, "Num 1"},
    {98, "Num 2"},
    {99, "Num 3"},
    {100, "Num 4"},
    {101, "Num 5"},
    {102, "Num 6"},
    {103, "Num 7"},
    {104, "Num 8"},
    {105, "Num 9"},
    {106, "*"},
    {107, "+"},
    {109, "Sub"},
    {110, "."},
    {111, "/"},
    {112, "F1"},
    {113, "F2"},
    {114, "F3"},
    {115, "F4"},
    {116, "F5"},
    {117, "F6"},
    {118, "F7"},
    {119, "F8"},
    {120, "F9"},
    {121, "F10"},
    {122, "F11"},
    {123, "F12"},
    {144, "Num"},
    {145, "Scroll"},
    {186, ";"},
    {187, "="},
    {188, ","},
    {189, "-"},
    {190, "."},
    {191, "/"},
    {192, "`"},
    {219, "["},
    {220, "\\"},
    {221, "]"},
    {222, "'"},
    {-1, "-"},
    };

public:

	enum KeybindType
	{
		HOLD,
		TOGGLE,
		ALWAYS_ON,
		OFF_KEYBIND,
	};

private:

	INT_PTR m_key;
    std::string m_str_key;
	KeybindType m_type;
    bool m_can_change_type;

	bool m_waiting_for_key;
    bool m_change_type;

public:

	CKeybind(INT_PTR defKey = -1, KeybindType defType = HOLD, bool canChange = true);

	bool IsActive();
	
	void think(Vector2 pos, Vector2 size) override;
};