#pragma once

class CRender
{
public:

	enum class ZPanel
	{
		Z_Zero,
		Z_One,
		Z_Two,
	};

private:

	enum DrawTypes
	{
		RECT,
		RECT_FILLED,
		LINE,
		GRADIENT,
		GRADIENT2,
		GRADIENT3,
		TEXT,
	};

private:

	struct DrawRequest
	{
		float x;
		float y;
		float w;
		float h;
		float t;
		ImColor col;
		float x1; 
		float y1; 
		float x2; 
		float y2; 
		ImColor top;
		ImColor bot; 
		ImColor left;
		ImColor right;
		ImColor topl;
		ImColor topr;
		ImColor botr;
		ImColor botl;
		std::string text;
		int flags;
		DrawTypes drawType;
	};

private:

	Vector2 m_pos;
	ImColor m_accent;

	Rendering* m_render;

	std::vector< DrawRequest > m_zero_requests;
	std::vector< DrawRequest > m_one_requests;
	std::vector< DrawRequest > m_two_requests;

public:

	CRender(Rendering* rendering);

	void init(Vector2 pos, ImColor accent);
	void render();

private:

	void draw_rect(float x, float y, float w, float h, float t, ImColor col);
	void draw_rect_filled(float x, float y, float w, float h, ImColor col);
	void draw_line(float x1, float y1, float x2, float y2, float t, ImColor col);
	void draw_gradient(float x, float y, float w, float h, ImColor top, ImColor bot);
	void draw_gradient2(float x, float y, float w, float h, ImColor left, ImColor right);
	void draw_gradient3(float x, float y, float w, float h, ImColor topl, ImColor topr, ImColor botr, ImColor botl);
	void draw_text(const std::string& text, float x, float y, ImColor col, int flags = FONTFLAGS::FONT_OUTLINED);

public:

	void rect(float x, float y, float w, float h, float t, ImColor col, ZPanel z = ZPanel::Z_Zero);
	void rect_filled(float x, float y, float w, float h, ImColor col, ZPanel z = ZPanel::Z_Zero);
	void line(float x1, float y1, float x2, float y2, float t, ImColor col, ZPanel z = ZPanel::Z_Zero);
	void gradient(float x, float y, float w, float h, ImColor top, ImColor bot, ZPanel z = ZPanel::Z_Zero);
	void gradient2(float x, float y, float w, float h, ImColor left, ImColor right, ZPanel z = ZPanel::Z_Zero);
	void gradient3(float x, float y, float w, float h, ImColor topl, ImColor topr, ImColor botr, ImColor botl, ZPanel z = ZPanel::Z_Zero);
	void text(const std::string& text, float x, float y, ImColor col, int flags = FONTFLAGS::FONT_OUTLINED, ZPanel z = ZPanel::Z_Zero);
};

extern std::unique_ptr<CRender> g_pMenuRender;