#pragma once

class CSlider : public CElement
{
private:

	const char* m_name;
	const char* m_type_display;

	float m_max;
	float m_min;
	float m_val;

	bool m_sliding;

public:

	CSlider(const char* name, const char* typeDisplay, float max, float min, float defValue);

	template <typename T = float>
	T get()
	{
		return (T)m_val;
	}

	void think(Vector2 pos, Vector2 size) override;
};