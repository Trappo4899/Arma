#pragma once

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

enum FONTFLAGS
{
	FONT_CENTERED = 1,
	FONT_RIGHT = 2,

	FONT_DROPSHADOW = 4,
	FONT_OUTLINED = 8,
};

class Rendering
{
	friend class BackgroundList;
	friend class ForegroundList;

public:

	bool							m_initialized;

private:

	HWND							m_hwnd;

private:

	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_render_target;
	ID3D11Texture2D* m_back_buffer;
	D3D_FEATURE_LEVEL				m_level;

private:

	inline static ImFont* m_normal;
	inline static ImFont* m_pixel;

public:

	Rendering();

	bool init(int showCmd);

private:

	bool setup_window();
	bool setup_directX();
	bool setup_imgui();
	bool setup_fonts();

	static void render_text(ImDrawList* drawlist, ImFont* font, const char* text, float x, float y, ImColor colour, int fontFlags);

public:

	void begin_render();
	void end_render();

public:

	struct BackgroundList
	{
		ImDrawList* m_background;

		void rect(float x, float y, float w, float h, float t, ImColor colour);
		void rect_filled(float x, float y, float w, float h, ImColor colour);
		void line(float x1, float y1, float x2, float y2, float t, ImColor colour);
		void gradient(float x, float y, float w, float h, ImColor top, ImColor bot);
		void gradient2(float x, float y, float w, float h, ImColor left, ImColor right);
		void gradient3(float x, float y, float w, float h, ImColor topl, ImColor topr, ImColor botr, ImColor botl);

		void normal_text(const char* text, float x, float y, ImColor colour = ImColor(255, 255, 255, 255), int fontFlags = FONT_CENTERED | FONT_OUTLINED);
		void pixel_text(const char* text, float x, float y, ImColor colour = ImColor(255, 255, 255, 255), int fontFlags = FONT_CENTERED | FONT_OUTLINED);

	} background;

	struct ForegroundList
	{
		ImDrawList* m_foreground;

		void rect(float x, float y, float w, float h, float t, ImColor colour);
		void rect_filled(float x, float y, float w, float h, ImColor colour);
		void line(float x1, float y1, float x2, float y2, float t, ImColor colour);
		void gradient(float x, float y, float w, float h, ImColor top, ImColor bot);
		void gradient2(float x, float y, float w, float h, ImColor left, ImColor right);
		void gradient3(float x, float y, float w, float h, ImColor topl, ImColor topr, ImColor botr, ImColor botl);

		void normal_text(const char* text, float x, float y, ImColor colour = ImColor(255, 255, 255, 255), int fontFlags = FONT_CENTERED | FONT_OUTLINED);
		void pixel_text(const char* text, float x, float y, ImColor colour = ImColor(255, 255, 255, 255), int fontFlags = FONT_CENTERED | FONT_OUTLINED);

	} foreground;
};

extern std::unique_ptr<Rendering> g_pRender;