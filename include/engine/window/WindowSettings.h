#ifndef WINDOW_SETTINGS_H
#define WINDOW_SETTINGS_H

struct WindowSettings {
    int screenWidth;
    int screenHeight;
    const char* title;

    WindowSettings(const int screenWidth, const int screenHeight, const char* title):
        screenWidth(screenWidth),
        screenHeight(screenHeight),
        title(title) {}
};

#endif //WINDOW_SETTINGS_H