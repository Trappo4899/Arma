#include "includes.h"

void __stdcall CConfigBox::save()
{
	//g_pMiscSettings->m_config->m_options.push_back(g_pMiscSettings->m_config->m_textbox.GetText().c_str());
}

void __stdcall CConfigBox::load()
{

}

void __stdcall CConfigBox::remove()
{

}

CConfigBox::CConfigBox()
{
	m_selection		= CSelectionBox({ "default" }, 0, { 279.f, 200.f });
	m_textbox		= CTextBox("");
	m_save			= CButton("save", CConfigBox::save);
	m_load			= CButton("load", CConfigBox::load);
	m_delete		= CButton("delete", CConfigBox::remove);
}

void CConfigBox::think(Vector2 pos, Vector2 size)
{
	m_selection.think(    pos,											  size	  );
	m_textbox.think(	{ pos.x, pos.y + 195.f },						  size    );
	m_save.think(		{ pos.x, pos.y + 240.f },		{ size.x + 178.f, size.y });
	m_load.think(		{ pos.x, pos.y + 270.f },		{ size.x + 178.f, size.y });
	m_delete.think(		{ pos.x, pos.y + 300.f },		{ size.x + 178.f, size.y });
}