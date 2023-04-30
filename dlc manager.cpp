#include "includes.h"

DlcItem::DlcItem()
{
	m_base = nullptr;
}

DlcItem::DlcItem(Address base)
{
	m_base = base;
}

bool DlcItem::IsUnlocked()
{
	return m_base.at<bool>(0x1C);
}

void DlcItem::Unlock()
{
	m_base.set(0x1C, true);
}

void DlcItem::Lock()
{
	m_base.set(0x1C, false);
}

std::string DlcItem::GetName()
{
	return "";
}

DlcList::DlcList()
{
	m_items = { };
}

DlcList::DlcList(Address list, UINT32 size)
{
	m_items = List(list, size);
}

void DlcList::UnlockAll()
{
	auto list = m_items.get_list();

	if (list.empty())
	{
		return;
	}

	for (auto item : list)
	{
		if (!item.as<DlcItem>().IsUnlocked())
		{
			item.as<DlcItem>().Unlock();
		}
	}
}

void DlcList::LockAll()
{
	auto list = m_items.get_list();

	if (list.empty())
	{
		return;
	}

	for (auto item : list)
	{
		item.as<DlcItem>().Lock();
	}
}

DlcTable::DlcTable()
{
	m_base = nullptr;
}

DlcTable::DlcTable(Address base)
{
	m_base = base;
}

std::vector<DlcList> DlcTable::GetLists()
{
	std::vector<DlcList> out = { };
	int i = 1;
	for (auto curr_offset : m_lists)
	{
		auto list = m_base.at(curr_offset);
		auto size = m_base.at<UINT32>(curr_offset + 0x8);

		if (!size || !list)
		{
			continue;
		}

		out.push_back(DlcList(list, size));
		i++;
	}

	return out;
}

DlcManager::DlcManager()
{
	m_dlc_table = nullptr;
}

DlcManager::DlcManager(Address table)
{
	m_dlc_table = table;
}

Address DlcManager::GetAddress()
{
	return m_dlc_table;
}

void DlcManager::UnlockDlcs()
{
	auto dlc_table = DlcTable(m_dlc_table);

	auto dlc_lists = dlc_table.GetLists();

	for (auto list : dlc_lists)
	{
		list.UnlockAll();
	}
}

void DlcManager::LockDlcs()
{
	auto dlc_table = DlcTable(m_dlc_table.at(0x30));

	auto dlc_lists = dlc_table.GetLists();

	for (auto list : dlc_lists)
	{
		list.LockAll();
	}
}