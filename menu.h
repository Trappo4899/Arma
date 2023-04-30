#pragma once

class CTab;

class CWindow
{
protected:

	Vector2 m_pos;
	Vector2 m_size;

	ImColor m_accent;

	BOOL m_open;
	BOOL m_moving;
	BOOL m_waiting;

protected:

	virtual void handle_movement();

public:

	CWindow();

public:

	virtual void think();
};

class CMenu : public CWindow
{
	friend class CElement;
	friend class CCheckbox;
	friend class CSlider;
	friend class CDropdown;
	friend class CMultiDropdown;
	friend class CColourPicker;
	friend class CButton;
	friend class CInput;
	friend class CGroup;
	friend class CKeybind;
	friend class CTextBox;
	friend class CTab;
	friend class CSettings;
	friend class CAimbotSettings;
	friend class CEspSettings;
	friend class CMiscSettings;

private:

	INT m_tabs_num;
	INT m_selected_tab = 1;

	std::vector<CTab> m_tabs;

	BOOL m_hovering;

private:

	void menu_base();
	void handle_tabs();

	void begin();
	void end();

	void handle_movement() override;

public:

	CMenu();

public:

	void add_tab(const char* name);
	void think() override;
};

extern std::unique_ptr<CMenu> g_pMenu;