#pragma once

#include <string>
#include <string_view>

#include "Common/File/Path.h"
#include "UI/BaseScreens.h"
#include "UI/SimpleDialogScreen.h"

class UIContext;

namespace Draw {
class Texture;
}

// Custom PNGs for the on-screen touch buttons live in <memstick>/PSP/SYSTEM/buttons/<name>.png
// e.g. circle.png, cross.png, square.png, triangle.png, start.png, select.png,
// left_shoulder.png, right_shoulder.png, pause.png, custom_1.png ...

// Turns a button key ("Circle button", "Custom 1") into the file base name ("circle", "custom_1").
std::string CustomButtonFileName(std::string_view key);
Path CustomButtonImagePath(std::string_view name);

// Returns the custom texture for this button, or nullptr if the user hasn't imported one.
// Result is cached (including misses). Do not Release() it.
Draw::Texture *GetCustomButtonTexture(UIContext &dc, std::string_view key);

// Releases all cached textures. Call after importing/removing images and on shutdown.
void CustomButtonImagesReset();

class CustomButtonImagesScreen : public UISimpleBaseDialogScreen {
public:
	CustomButtonImagesScreen(const Path &gamePath) : UISimpleBaseDialogScreen(gamePath, SimpleDialogFlags::ContentsCanScroll) {}
	void CreateDialogViews(UI::ViewGroup *parent) override;
	std::string_view GetTitle() const override;
	const char *tag() const override { return "CustomButtonImages"; }
};
