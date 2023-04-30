#ifndef DLC_MANAGER_H
#define DLC_MANAGER_H

class DlcItem
{
private:

	Address m_base;

public:

	DlcItem();
	DlcItem(Address base);

	bool IsUnlocked();
	void Unlock();
	void Lock();
	std::string GetName();
};

class DlcList
{
private:

	List m_items;

public:

	DlcList();
	DlcList(Address list, UINT32 size);

	void UnlockAll();
	void LockAll();
};

class DlcTable
{
private:
	
	Address m_base;
	std::vector<UINT_PTR> m_lists = { 0x0, 0x78, 0x90, 0xA8, 0xF0 };

public:

	DlcTable();
	DlcTable(Address base);

	std::vector<DlcList> GetLists();
};

class DlcManager
{
private:

	Address m_dlc_table;

public:

	DlcManager();
	DlcManager(Address table);

	Address GetAddress();

	void UnlockDlcs();
	void LockDlcs();
};

#endif