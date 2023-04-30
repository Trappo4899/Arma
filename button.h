#pragma once

typedef void(__stdcall* tButtonRoutine)();

class CButton : public CElement
{
private:

	const char* m_name;
	tButtonRoutine m_routine;

public:

	CButton(const char* name, tButtonRoutine routine);

	void think(Vector2 pos, Vector2 size) override;
};