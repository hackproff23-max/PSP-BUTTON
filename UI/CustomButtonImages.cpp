#include <cctype>
#include <cstdio>
#include <map>
#include <string>

#include "Common/Data/Text/I18n.h"
#include "Common/File/FileUtil.h"
#include "Common/File/Path.h"
#include "Common/GPU/thin3d.h"
#include "Common/Log.h"
#include "Common/Render/ManagedTexture.h"
#include "Common/StringUtils.h"
#include "Common/System/OSD.h"
#include "Common/System/Request.h"
#include "Common/UI/Context.h"
#include "Common/UI/View.h"
#include "Common/UI/ViewGroup.h"
#include "Core/System.h"
#include "UI/CustomButtonImages.h"

static std::map<std::string, Draw::Texture *> g_customTextures;

std::string CustomButtonFileName(std::string_view key) {
	std::string s;
	s.reserve(key.size());
	for (char c : key) {
		s.push_back(c == ' ' ? '_' : (char)tolower((unsigned char)c));
	}
	static const std::string suffix = "_button";
	if (s.size() > suffix.size() && s.compare(s.size() - suffix.size(), suffix.size(), suffix) == 0) {
		s.resize(s.size() - suffix.size());
	}
	return s;
}

static Path CustomButtonDir() {
	return GetSysDirectory(DIRECTORY_SYSTEM) / "buttons";
}

Path CustomButtonImagePath(std::string_view name) {
	return CustomButtonDir() / (std::string(name) + ".png");
}

Draw::Texture *GetCustomButtonTexture(UIContext &dc, std::string_view key) {
	const std::string name = CustomButtonFileName(key);
	auto it = g_customTextures.find(name);
	if (it != g_customTextures.end())
		return it->second;

	Draw::Texture *tex = nullptr;
	const Path path = CustomButtonImagePath(name);
	if (File::Exists(path)) {
		tex = CreateTextureFromFile(dc.GetDrawContext(), path.c_str(), ImageFileType::PNG, false);
		if (!tex) {
			WARN_LOG(Log::UI, "Failed to load custom button image %s", path.c_str());
		}
	}
	g_customTextures[name] = tex;  // Cache misses too, so we don't hit the disk every frame.
	return tex;
}

void CustomButtonImagesReset() {
	for (auto &it : g_customTextures) {
		if (it.second)
			it.second->Release();
	}
	g_customTextures.clear();
}

// ---- Settings screen ----

struct CustomButtonEntry {
	const char *key;    // Same key the on-screen button uses.
	const char *label;
};

static const CustomButtonEntry g_entries[] = {
	{ "Circle button", "Circle" },
	{ "Cross button", "Cross" },
	{ "Square button", "Square" },
	{ "Triangle button", "Triangle" },
	{ "Start button", "Start" },
	{ "Select button", "Select" },
	{ "Left shoulder button", "L" },
	{ "Right shoulder button", "R" },
	{ "Pause", "Pause" },
	{ "Fast-forward", "Fast-forward" },
	{ "Custom 1", "Custom 1" },
	{ "Custom 2", "Custom 2" },
	{ "Custom 3", "Custom 3" },
	{ "Custom 4", "Custom 4" },
	{ "Custom 5", "Custom 5" },
	{ "Custom 6", "Custom 6" },
	{ "Custom 7", "Custom 7" },
	{ "Custom 8", "Custom 8" },
	{ "Custom 9", "Custom 9" },
	{ "Custom 10", "Custom 10" },
};

std::string_view CustomButtonImagesScreen::GetTitle() const {
	auto co = GetI18NCategory(I18NCat::CONTROLS);
	return co->T("Custom button images");
}

void CustomButtonImagesScreen::CreateDialogViews(UI::ViewGroup *parent) {
	using namespace UI;

	auto co = GetI18NCategory(I18NCat::CONTROLS);
	auto sy = GetI18NCategory(I18NCat::SYSTEM);

	parent->Add(new TextView(co->T("Import your own PNG for each button"), ALIGN_LEFT, false, new LinearLayoutParams(FILL_PARENT, WRAP_CONTENT)));

	for (const CustomButtonEntry &entry : g_entries) {
		const std::string name = CustomButtonFileName(entry.key);
		const Path dest = CustomButtonImagePath(name);
		const bool exists = File::Exists(dest);

		LinearLayout *row = parent->Add(new LinearLayout(ORIENT_HORIZONTAL, new LinearLayoutParams(FILL_PARENT, WRAP_CONTENT)));
		row->SetSpacing(0);

		std::string label = entry.label;
		if (exists)
			label += " (PNG)";
		Choice *import = row->Add(new Choice(label, new LinearLayoutParams(1.0f)));
		import->OnClick.Add([this, dest, sy](UI::EventParams &e) {
			File::CreateFullPath(dest.NavigateUp());
			System_BrowseForImage(GetRequesterToken(), sy->T("Choose PNG..."), dest, [this, dest, sy](const std::string &value, int converted) {
				if (converted == 1) {
					// The platform already converted and saved the image to dest.
				} else if (!value.empty()) {
					Path src(value);
					FILE *f = File::OpenCFile(src, "rb");
					uint8_t buffer[8]{};
					ImageFileType type = ImageFileType::UNKNOWN;
					if (f) {
						if (fread(buffer, 1, sizeof(buffer), f) == sizeof(buffer))
							type = DetectImageFileType(buffer, sizeof(buffer));
						fclose(f);
					}
					if (type == ImageFileType::PNG) {
						File::Copy(src, dest);
						if (src.FilePathContainsNoCase("temp_import")) {
							File::Delete(src);
						}
					} else {
						g_OSD.Show(OSDType::MESSAGE_ERROR, sy->T("Only PNG images are supported"), src.GetFilename(), 5.0);
					}
				}
				// Textures are recreated lazily on the next draw.
				CustomButtonImagesReset();
				RecreateViews();
			});
		});

		if (exists) {
			Choice *clear = row->Add(new Choice(co->T("Remove"), new LinearLayoutParams(0.4f)));
			clear->OnClick.Add([this, dest](UI::EventParams &e) {
				File::Delete(dest);
				CustomButtonImagesReset();
				RecreateViews();
			});
		}
	}
}
