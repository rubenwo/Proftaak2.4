#pragma once
class Vec2f;
struct Color4;
#include <string>
namespace Util
{
	// Draw text on screen.
	void drawText(const Color4& clr, const Vec2f& pos, int windowWidth, int windowHeight, const std::string& text);
	// Retrieves the exe path.
	std::string getExePath();
}