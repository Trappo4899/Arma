#include "includes.h"

CRender::CRender(Rendering* rendering)
{
	m_pos = { };
	m_render = rendering;
}

void CRender::init(Vector2 pos, ImColor accent)
{
	m_pos = pos;
	m_accent = accent;
}

void CRender::render()
{
	for (auto req : m_zero_requests)
	{
		switch (req.drawType)
		{
		case RECT:
			this->draw_rect(req.x, req.y, req.w, req.h, req.t, req.col);
			break;

		case RECT_FILLED:
			this->draw_rect_filled(req.x, req.y, req.w, req.h, req.col);
			break;

		case LINE:
			this->draw_line(req.x1, req.y1, req.x2, req.y2, req.t, req.col);
			break;

		case GRADIENT:
			this->draw_gradient(req.x, req.y, req.w, req.h, req.top, req.bot);
			break;

		case GRADIENT2:
			this->draw_gradient2(req.x, req.y, req.w, req.h, req.left, req.right);
			break;

		case GRADIENT3:
			this->draw_gradient3(req.x, req.y, req.w, req.h, req.topl , req.topr, req.botr, req.botl);
			break;

		case TEXT:
			this->draw_text(req.text, req.x, req.y, req.col, req.flags);
			break;
		}
	}

	for (auto req : m_one_requests)
	{
		switch (req.drawType)
		{
		case RECT:
			this->draw_rect(req.x, req.y, req.w, req.h, req.t, req.col);
			break;

		case RECT_FILLED:
			this->draw_rect_filled(req.x, req.y, req.w, req.h, req.col);
			break;

		case LINE:
			this->draw_line(req.x1, req.y1, req.x2, req.y2, req.t, req.col);
			break;

		case GRADIENT:
			this->draw_gradient(req.x, req.y, req.w, req.h, req.top, req.bot);
			break;

		case GRADIENT2:
			this->draw_gradient2(req.x, req.y, req.w, req.h, req.left, req.right);
			break;

		case GRADIENT3:
			this->draw_gradient3(req.x, req.y, req.w, req.h, req.topl, req.topr, req.botr, req.botl);
			break;

		case TEXT:
			this->draw_text(req.text, req.x, req.y, req.col, req.flags);
			break;
		}
	}

	for (auto req : m_two_requests)
	{
		switch (req.drawType)
		{
		case RECT:
			this->draw_rect(req.x, req.y, req.w, req.h, req.t, req.col);
			break;

		case RECT_FILLED:
			this->draw_rect_filled(req.x, req.y, req.w, req.h, req.col);
			break;

		case LINE:
			this->draw_line(req.x1, req.y1, req.x2, req.y2, req.t, req.col);
			break;

		case GRADIENT:
			this->draw_gradient(req.x, req.y, req.w, req.h, req.top, req.bot);
			break;

		case GRADIENT2:
			this->draw_gradient2(req.x, req.y, req.w, req.h, req.left, req.right);
			break;

		case GRADIENT3:
			this->draw_gradient3(req.x, req.y, req.w, req.h, req.topl, req.topr, req.botr, req.botl);
			break;

		case TEXT:
			this->draw_text(req.text, req.x, req.y, req.col, req.flags);
			break;
		}
	}

	m_zero_requests.clear();
	m_one_requests.clear();
	m_two_requests.clear();
}

void CRender::draw_rect(float x, float y, float w, float h, float t, ImColor col)
{
	m_render->foreground.rect(m_pos.x + x, m_pos.y + y, w, h, t, col);
}

void CRender::draw_rect_filled(float x, float y, float w, float h, ImColor col)
{
	m_render->foreground.rect_filled(m_pos.x + x, m_pos.y + y, w, h, col);
}

void CRender::draw_line(float x1, float y1, float x2, float y2, float t, ImColor col)
{
	m_render->foreground.line(m_pos.x + x1, m_pos.y + y1, m_pos.x + x2, m_pos.y + y2, t, col);
}

void CRender::draw_gradient(float x, float y, float w, float h, ImColor top, ImColor bot)
{
	m_render->foreground.gradient(m_pos.x + x, m_pos.y + y, w, h, top, bot);
}

void CRender::draw_gradient2(float x, float y, float w, float h, ImColor left, ImColor right)
{
	m_render->foreground.gradient2(m_pos.x + x, m_pos.y + y, w, h, left, right);
}

void CRender::draw_gradient3(float x, float y, float w, float h, ImColor topl, ImColor topr, ImColor botr, ImColor botl)
{
	m_render->foreground.gradient3(m_pos.x + x, m_pos.y + y, w, h, topl, topr, botr, botl);
}

void CRender::draw_text(const std::string& text, float x, float y, ImColor col, int flags)
{
	m_render->foreground.normal_text(text.c_str(), m_pos.x + x, m_pos.y + y, col, flags);
}

void CRender::rect(float x, float y, float w, float h, float t, ImColor col, ZPanel z)
{
	DrawRequest req = { };

	req.x = x;
	req.y = y;
	req.w = w;
	req.h = h;
	req.t = t;
	req.col = col;
	req.drawType = RECT;

	switch (z)
	{
	case ZPanel::Z_Zero:
		m_zero_requests.push_back(req);
		break;

	case ZPanel::Z_One:
		m_one_requests.push_back(req);
		break;

	case ZPanel::Z_Two:
		m_two_requests.push_back(req);
		break;

	default:
		m_zero_requests.push_back(req);
		break;
	}
}

void CRender::rect_filled(float x, float y, float w, float h, ImColor col, ZPanel z)
{
	DrawRequest req = { };

	req.x = x;
	req.y = y;
	req.w = w;
	req.h = h;
	req.col = col;
	req.drawType = RECT_FILLED;

	switch (z)
	{
	case ZPanel::Z_Zero:
		m_zero_requests.push_back(req);
		break;

	case ZPanel::Z_One:
		m_one_requests.push_back(req);
		break;

	case ZPanel::Z_Two:
		m_two_requests.push_back(req);
		break;

	default:
		m_zero_requests.push_back(req);
		break;
	}
}

void CRender::line(float x1, float y1, float x2, float y2, float t, ImColor col, ZPanel z)
{
	DrawRequest req = { };

	req.x1 = x1;
	req.y1 = y1;
	req.x2 = x2;
	req.y2 = y2;
	req.t = t;
	req.col = col;
	req.drawType = LINE;

	switch (z)
	{
	case ZPanel::Z_Zero:
		m_zero_requests.push_back(req);
		break;

	case ZPanel::Z_One:
		m_one_requests.push_back(req);
		break;

	case ZPanel::Z_Two:
		m_two_requests.push_back(req);
		break;

	default:
		m_zero_requests.push_back(req);
		break;
	}
}

void CRender::gradient(float x, float y, float w, float h, ImColor top, ImColor bot, ZPanel z)
{
	DrawRequest req = { };

	req.x = x;
	req.y = y;
	req.w = w;
	req.h = h;
	req.top = top;
	req.bot = bot;
	req.drawType = GRADIENT;

	switch (z)
	{
	case ZPanel::Z_Zero:
		m_zero_requests.push_back(req);
		break;

	case ZPanel::Z_One:
		m_one_requests.push_back(req);
		break;

	case ZPanel::Z_Two:
		m_two_requests.push_back(req);
		break;

	default:
		m_zero_requests.push_back(req);
		break;
	}
}

void CRender::gradient2(float x, float y, float w, float h, ImColor left, ImColor right, ZPanel z)
{
	DrawRequest req = { };

	req.x = x;
	req.y = y;
	req.w = w;
	req.h = h;
	req.left = left;
	req.right = right;
	req.drawType = GRADIENT2;

	switch (z)
	{
	case ZPanel::Z_Zero:
		m_zero_requests.push_back(req);
		break;

	case ZPanel::Z_One:
		m_one_requests.push_back(req);
		break;

	case ZPanel::Z_Two:
		m_two_requests.push_back(req);
		break;

	default:
		m_zero_requests.push_back(req);
		break;
	}
}

void CRender::gradient3(float x, float y, float w, float h, ImColor topl, ImColor topr, ImColor botr, ImColor botl, ZPanel z)
{
	DrawRequest req = { };

	req.x = x;
	req.y = y;
	req.w = w;
	req.h = h;
	req.topl = topl;
	req.topr = topr;
	req.botr = botr;
	req.botl = botl;
	req.drawType = GRADIENT3;

	switch (z)
	{
	case ZPanel::Z_Zero:
		m_zero_requests.push_back(req);
		break;

	case ZPanel::Z_One:
		m_one_requests.push_back(req);
		break;

	case ZPanel::Z_Two:
		m_two_requests.push_back(req);
		break;

	default:
		m_zero_requests.push_back(req);
		break;
	}
}

void CRender::text(const std::string& text, float x, float y, ImColor col, int flags, ZPanel z)
{
	DrawRequest req = { };

	req.text = text;
	req.x = x;
	req.y = y;
	req.col = col;
	req.flags = flags;
	req.drawType = TEXT;

	switch (z)
	{
	case ZPanel::Z_Zero:
		m_zero_requests.push_back(req);
		break;

	case ZPanel::Z_One:
		m_one_requests.push_back(req);
		break;

	case ZPanel::Z_Two:
		m_two_requests.push_back(req);
		break;

	default:
		m_zero_requests.push_back(req);
		break;
	}
}