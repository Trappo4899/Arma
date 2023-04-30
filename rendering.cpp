#include "includes.h"
#include "raw data.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
	{
		return 0;
	}

	if (msg == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

Rendering::Rendering()
{
	/*do
	{
		if (!this->setup_window())
		{
			break;
		}

		if (!this->setup_directX())
		{
			break;
		}

		ShowWindow(m_hwnd, 1);
		UpdateWindow(m_hwnd);

		if (!this->setup_imgui())
		{
			break;
		}

		if (!this->setup_fonts())
		{
			break;
		}

		m_initialized = true;

		return;
	} while (false);*/

	m_initialized = false;
}

bool Rendering::setup_window()
{
	WNDCLASSEXW wc = { };

	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = GetModuleHandle(0);
	wc.lpszClassName = L"CrosshairClass";

	if (!RegisterClassExW(&wc))
	{
		printf("Failed to register class!\n");
		return false;
	}

	auto desk_wind = GetDesktopWindow();

	if (!desk_wind)
	{
		printf("Failed to get desktop window!\n");
		return false;
	}

	RECT desk_rect = { };

	if (!GetWindowRect(desk_wind, &desk_rect))
	{
		printf("Failed to get desktop rect!\n");
		return false;
	}

	m_hwnd = CreateWindowExW(
		WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
		wc.lpszClassName,
		L"CrosshairOverlayWindow",
		WS_POPUP,
		7,
		7,
		1920 - 14,
		1080 - 14,
		NULL,
		NULL,
		wc.hInstance,
		NULL
	);

	if (!m_hwnd)
	{
		printf("Failed to create window!\n");
		return false;
	}

	if (!SetLayeredWindowAttributes(m_hwnd, RGB(0, 0, 0), 255, LWA_ALPHA))
	{
		printf("Failed to set layered window attributes!\n");
		return false;
	}

	MARGINS margin = {
	7,
	7,
	desk_rect.right - 14,
	desk_rect.bottom - 14,
	};

	if (DwmExtendFrameIntoClientArea(m_hwnd, &margin) != S_OK)
	{
		printf("Failed to extend frame into client area!\n");
		return false;
	}

	return true;
}

bool Rendering::init(int showCmd)
{
	if (!this->setup_window())
	{
		return false;
	}

	ShowWindow(m_hwnd, showCmd);
	UpdateWindow(m_hwnd);

	if (!this->setup_directX())
	{
		return false;
	}

	if (!this->setup_imgui())
	{
		return false;
	}

	if (!this->setup_fonts())
	{
		return false;
	}

	m_initialized = true;

	return true;
}

bool Rendering::setup_directX()
{
	DXGI_SWAP_CHAIN_DESC sd = { };

	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.SampleDesc.Count = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2;
	sd.OutputWindow = m_hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	constexpr D3D_FEATURE_LEVEL levels[2]
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0
	};

	if (D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		levels,
		2,
		D3D11_SDK_VERSION,
		&sd,
		&m_swap_chain,
		&m_device,
		&m_level,
		&m_context
	) != S_OK) return false;

	m_back_buffer = nullptr;

	m_swap_chain->GetBuffer(0, IID_PPV_ARGS(&m_back_buffer));

	if (!m_back_buffer)
	{
		return false;
	}

	m_device->CreateRenderTargetView(m_back_buffer, NULL, &m_render_target);
	m_back_buffer->Release();

	return true;
}

bool Rendering::setup_imgui()
{
	ImGui::CreateContext();

	if (!ImGui_ImplWin32_Init(m_hwnd))
	{
		return false;
	}

	if (!ImGui_ImplDX11_Init(m_device, m_context))
	{
		return false;
	}

	return true;
}

bool Rendering::setup_fonts()
{
	auto io = ImGui::GetIO();

	m_normal = io.Fonts->AddFontFromMemoryTTF((void*)RawData::NormalFont, sizeof(RawData::NormalFont), 10);
	m_pixel = io.Fonts->AddFontFromMemoryTTF((void*)RawData::PixelFont, sizeof(RawData::PixelFont), 10);

	return m_normal != nullptr;
}

void Rendering::begin_render()
{
	MSG msg = { };
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT)
		{
			return;
		}
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	foreground.m_foreground = ImGui::GetForegroundDrawList();
	background.m_background = ImGui::GetBackgroundDrawList();
}

void Rendering::end_render()
{
	ImGui::Render();

	constexpr float color[4]{ 0.f, 0.f, 0.f, 0.f };
	m_context->OMSetRenderTargets(1, &m_render_target, NULL);
	m_context->ClearRenderTargetView(m_render_target, color);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	m_swap_chain->Present(1, 0);
}

void Rendering::render_text(ImDrawList* drawlist, ImFont* font, const char* text, float x, float y, ImColor colour, int flags)
{
	ImGui::PushFont(font);

	if (flags & FONT_CENTERED)
	{
		x -= (ImGui::CalcTextSize(text).x / 2);
	}
	else if (flags & FONT_RIGHT)
	{
		x -= ImGui::CalcTextSize(text).x;
	}

	if (flags & FONT_OUTLINED)
	{
		drawlist->AddText({ x + 1, y + 1 }, ImColor(0.f, 0.f, 0.f, 1.f), text);
		drawlist->AddText({ x - 1, y - 1 }, ImColor(0.f, 0.f, 0.f, 1.f), text);
		drawlist->AddText({ x + 1, y - 1 }, ImColor(0.f, 0.f, 0.f, 1.f), text);
		drawlist->AddText({ x - 1, y + 1 }, ImColor(0.f, 0.f, 0.f, 1.f), text);
		drawlist->AddText({ x + 1, y + 0 }, ImColor(0.f, 0.f, 0.f, 1.f), text);
		drawlist->AddText({ x - 1, y + 0 }, ImColor(0.f, 0.f, 0.f, 1.f), text);
		drawlist->AddText({ x + 0, y - 1 }, ImColor(0.f, 0.f, 0.f, 1.f), text);
		drawlist->AddText({ x + 0, y + 1 }, ImColor(0.f, 0.f, 0.f, 1.f), text);

		drawlist->AddText({ x, y }, colour, text);
	}
	else if (flags & FONT_DROPSHADOW)
	{
		drawlist->AddText({ x + 1, y + 1 }, ImColor(0.f, 0.f, 0.f, 1.f), text);

		drawlist->AddText({ x, y }, colour, text);
	}
	else
	{
		drawlist->AddText({ x, y }, colour, text);
	}

	ImGui::PopFont();
}


void Rendering::BackgroundList::rect(float x, float y, float w, float h, float t, ImColor colour)
{
	m_background->AddRect({ x, y }, { x + w, y + h }, colour, 0, 0, t);
}

void Rendering::BackgroundList::rect_filled(float x, float y, float w, float h, ImColor colour)
{
	m_background->AddRectFilled({ x, y }, { x + w, y + h }, colour);
}

void Rendering::BackgroundList::line(float x1, float y1, float x2, float y2, float t, ImColor colour)
{
	m_background->AddLine({ x1, y1 }, { x2, y2 }, colour, t);
}

void Rendering::BackgroundList::gradient(float x, float y, float w, float h, ImColor top, ImColor bot)
{
	m_background->AddRectFilledMultiColor({ x, y }, { x + w, y + h }, top, top, bot, bot);
}

void Rendering::BackgroundList::gradient2(float x, float y, float w, float h, ImColor left, ImColor right)
{
	m_background->AddRectFilledMultiColor({ x, y }, { x + w, y + h }, left, right, right, left);
}

void Rendering::BackgroundList::gradient3(float x, float y, float w, float h, ImColor topl, ImColor topr, ImColor botr, ImColor botl)
{
	m_background->AddRectFilledMultiColor({ x, y }, { x + w, y + h }, topl, topr, botr, botl);
}

void Rendering::BackgroundList::normal_text(const char* text, float x, float y, ImColor colour, int fontFlags)
{
	Rendering::render_text(m_background, m_normal, text, x, y, colour, fontFlags);
}

void Rendering::BackgroundList::pixel_text(const char* text, float x, float y, ImColor colour, int fontFlags)
{
	Rendering::render_text(m_background, m_pixel, text, x, y, colour, fontFlags);
}

void Rendering::ForegroundList::rect(float x, float y, float w, float h, float t, ImColor colour)
{
	m_foreground->AddRect({ x, y }, { x + w, y + h }, colour, 0, 0, t);
}

void Rendering::ForegroundList::rect_filled(float x, float y, float w, float h, ImColor colour)
{
	m_foreground->AddRectFilled({ x, y }, { x + w, y + h }, colour);
}

void Rendering::ForegroundList::line(float x1, float y1, float x2, float y2, float t, ImColor colour)
{
	m_foreground->AddLine({ x1, y1 }, { x2, y2 }, colour, t);
}

void Rendering::ForegroundList::gradient(float x, float y, float w, float h, ImColor top, ImColor bot)
{
	m_foreground->AddRectFilledMultiColor({ x, y }, { x + w, y + h }, top, top, bot, bot);
}

void Rendering::ForegroundList::gradient2(float x, float y, float w, float h, ImColor left, ImColor right)
{
	m_foreground->AddRectFilledMultiColor({ x, y }, { x + w, y + h }, left, right, right, left);
}

void Rendering::ForegroundList::gradient3(float x, float y, float w, float h, ImColor topl, ImColor topr, ImColor botr, ImColor botl)
{
	m_foreground->AddRectFilledMultiColor({ x, y }, { x + w, y + h }, topl, topr, botr, botl);
}

void Rendering::ForegroundList::normal_text(const char* text, float x, float y, ImColor colour, int fontFlags)
{
	Rendering::render_text(m_foreground, m_normal, text, x, y, colour, fontFlags);
}

void Rendering::ForegroundList::pixel_text(const char* text, float x, float y, ImColor colour, int fontFlags)
{
	Rendering::render_text(m_foreground, m_pixel, text, x, y, colour, fontFlags);
}