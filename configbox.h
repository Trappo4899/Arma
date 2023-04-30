#pragma once

class CSelectionBox;
class CTextBox;
class CButton;

class CConfigBox : public CElement
{
private:

	std::string path;

	std::vector<const char*> m_cfg_paths;
	std::vector<const char*> m_options;

	int m_selected;

	CSelectionBox m_selection = CSelectionBox({ "default" }, 0, { 279.f, 200.f });;
	CTextBox m_textbox = CTextBox("Name");
	CButton m_save = CButton("save", CConfigBox::save);
	CButton m_load = CButton("load", CConfigBox::load);
	CButton m_delete = CButton("delete", nullptr);

private:

	static void __stdcall save();
	static void __stdcall load();
	static void __stdcall remove();

public:

	CConfigBox();

public:

	void think(Vector2 size, Vector2 pos) override;

};