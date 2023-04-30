#pragma once

class CCheckbox;
class CSlider;
class CDropdown;
class CMultiDropdown;
class CColourPicker;
class CButton;
class CText;
class CSelectionBox;
class CConfigBox;

class CGroup
{
	friend class CTab;
	friend class CCheckbox;

public:

	enum ELEMENTS
	{
		CHECKBOX,
		SLIDER,
		BUTTON,
		DROPDOWN,
		MULTIDROPDOWN,
		COLOURPICKER,
		KEYBIND,
		TEXTBOX,
		TEXT,
		SELECTIONBOX,
		CONFIGBOX,
	};

protected:

	Vector2 m_pos;
	Vector2 m_size;
	Vector2 m_padding;
	Vector2 m_real_padding;
	Vector2 m_view_padding;
	Vector2 m_scroll_pos;

	const char* m_name;

	bool m_do_scroll;
	bool m_scrolling;

	std::vector<std::pair<void*, ELEMENTS>> m_elements;

public:

	CGroup(const char* name, Vector2 pos, Vector2 size);

private:

	bool in_view(Vector2 pad);

	void group_base();

	void handle_scrollbar_vertical();

	void handle_elements();

public:

	void add_element(CCheckbox* element);
	void add_element(CSlider* element);
	void add_element(CButton* element);
	void add_element(CDropdown* element);
	void add_element(CMultiDropdown* element);
	void add_element(CColourPicker* element);
	void add_element(CKeybind* element);
	void add_element(CTextBox* element);
	void add_element(CText* element);
	void add_element(CSelectionBox* element);
	void add_element(CConfigBox* element);

	void think();
};