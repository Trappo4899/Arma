#include "includes.h"

void util::CopyToClipboard(const std::string& text)
{
	if (OpenClipboard(NULL))
	{
		HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, (text.size() + 1) * sizeof(char));

		if (hGlob == NULL)
		{
			CloseClipboard();
			return;
		}

		char* pChars = (char*)GlobalLock(hGlob);

		memcpy(pChars, text.c_str(), (text.size() + 1) * sizeof(char));

		GlobalUnlock(hGlob);

		EmptyClipboard();

		SetClipboardData(CF_TEXT, hGlob);

		CloseClipboard();

		GlobalFree(hGlob);
	}
}

std::string util::GetClipboardText()
{
	if (OpenClipboard(NULL))
	{
		HANDLE hData = GetClipboardData(CF_TEXT);
		if (hData != NULL)
		{
			char* pChars = (char*)GlobalLock(hData);
			DWORD size = strlen(pChars) + 1;

			std::string text(pChars, size);

			GlobalUnlock(hData);

			CloseClipboard();

			return text;
		}

		CloseClipboard();
	}

	return "";
}

ImColor util::HexToRgb(const std::string& hex)
{
	int r, g, b, a;
	sscanf_s(hex.c_str(), "#%02x%02x%02x%02x", &r, &g, &b, &a);
	return ImColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}

std::string util::RgbToHex(const ImColor& colour)
{
	int r = int(colour.Value.x * 255 + 0.5f);
	int g = int(colour.Value.y * 255 + 0.5f);
	int b = int(colour.Value.z * 255 + 0.5f);
	int a = int(colour.Value.w * 255 + 0.5f);
	char buffer[20];
	sprintf_s(buffer, "#%02X%02X%02X%02X", r, g, b, a);
	return std::string(buffer);
}

ImColor util::ColourInterpolation(ImColor col, ImColor col2, float min, float max, float val)
{
	float t = (val - min) / (max - min);
	ImVec4 color1Vec4 = col2;
	ImVec4 color2Vec4 = col;
	ImVec4 resultVec4 = ImVec4(
		ImLerp(color1Vec4.x, color2Vec4.x, t),
		ImLerp(color1Vec4.y, color2Vec4.y, t),
		ImLerp(color1Vec4.z, color2Vec4.z, t),
		ImLerp(color1Vec4.w, color2Vec4.w, t)
	);
	return resultVec4;
}
