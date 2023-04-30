#include "includes.h"

CTab::CTab(const char* name, int id)
{
	m_name = name;
	m_id = id;
	m_groups = { };
}

void CTab::add_group(CGroup* group)
{
	m_groups.push_back(group);
}

void CTab::handle_groups()
{
	for (auto group : m_groups)
	{
		group->think();
	}
}

const char* CTab::get_name()
{
	return m_name;
}

int CTab::get_id()
{
	return m_id;
}

void CTab::add_element(CCheckbox* element, int group_idx)
{
	auto group = m_groups.at(group_idx);

	group->add_element(element);
}

void CTab::add_element(CSlider* element, int group_idx)
{
	auto group = m_groups.at(group_idx);

	group->add_element(element);
}

void CTab::add_element(CButton* element, int group_idx)
{
	auto group = m_groups.at(group_idx);

	group->add_element(element);
}

void CTab::add_element(CDropdown* element, int group_idx)
{
	auto group = m_groups.at(group_idx);

	group->add_element(element);
}

void CTab::add_element(CMultiDropdown* element, int group_idx)
{
	auto group = m_groups.at(group_idx);

	group->add_element(element);
}

void CTab::add_element(CColourPicker* element, int group_idx)
{
	auto group = m_groups.at(group_idx);

	group->add_element(element);
}

void CTab::add_element(CKeybind* element, int group_idx)
{
	auto group = m_groups.at(group_idx);

	group->add_element(element);
}

void CTab::add_element(CTextBox* element, int group_idx)
{
	auto group = m_groups.at(group_idx);

	group->add_element(element);
}

void CTab::add_element(CText* element, int group_idx)
{
	auto group = m_groups.at(group_idx);

	group->add_element(element);
}

void CTab::think()
{
	this->handle_groups();
}