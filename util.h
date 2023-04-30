#ifndef UTIL_H
#define UTIL_H

namespace util
{
	template<typename O = void*, typename I = void*>
	__forceinline O force_cast(I in)
	{
		union {
			I in; 
			O out;
		}

		u = { in };

		return u.out;
	};

	void CopyToClipboard(const std::string& text);
	std::string GetClipboardText();

	ImColor HexToRgb(const std::string& hex);
	std::string RgbToHex(const ImColor& colour);

	ImColor ColourInterpolation(ImColor col, ImColor col2, float min, float max, float val);
}

#endif