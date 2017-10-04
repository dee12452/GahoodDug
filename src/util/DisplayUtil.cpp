#include "DisplayUtil.hpp"

#include <SDL2/SDL.h>
#include "Util.hpp"

DisplayUtil::DisplayUtil() {}

DisplayUtil::~DisplayUtil() {}

int DisplayUtil::getScreenWidth() {
	const int display = 0;
	SDL_DisplayMode dm;
	if (SDL_GetCurrentDisplayMode(0, &dm) != 0) {
		Util::fatalSDLError("Failed to get the current display configuration!");
	}
	return dm.w;
}

int DisplayUtil::getScreenHeight() {
	const int display = 0;
	SDL_DisplayMode dm;
	if (SDL_GetCurrentDisplayMode(0, &dm) != 0) {
		Util::fatalSDLError("Failed to get the current display configuration!");
	}
	return dm.h;
}

int DisplayUtil::getScreenRefreshRate() {
	const int display = 0;
	SDL_DisplayMode dm;
	if (SDL_GetCurrentDisplayMode(0, &dm) != 0) {
		Util::fatalSDLError("Failed to get the current display configuration!");
	}
	return dm.refresh_rate;
}
