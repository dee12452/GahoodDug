#ifndef DISPLAY_UTIL_HPP
#define DISPLAY_UTIL_HPP

class DisplayUtil {
private:
	DisplayUtil();
	~DisplayUtil();

public:
	static int getScreenWidth();
	static int getScreenHeight();
	static int getScreenRefreshRate();
};

#endif