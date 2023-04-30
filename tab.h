#pragma once

class CGroup;
class CText;
class CTextBox;

class CTab
{
protected:

	const char* m_name;
	int m_id;

	std::vector<CGroup*> m_groups;

public:

	CTab(const char* name, int id);

public:

	void add_group(CGroup* group);

private:

	void handle_groups();

public:

	const char* get_name();
	int get_id();

	void add_element(CCheckbox* element, int group_idx);
	void add_element(CSlider* element, int group_idx);
	void add_element(CButton* element, int group_idx);
	void add_element(CDropdown* element, int group_idx);
	void add_element(CMultiDropdown* element, int group_idx);
	void add_element(CColourPicker* element, int group_idx);
	void add_element(CKeybind* element, int group_idx);
	void add_element(CTextBox* element, int group_idx);
	void add_element(CText* element, int group_idx);

	void think();
};