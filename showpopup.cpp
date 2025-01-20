#include <iostream>
#include <string>

#if defined(_WIN32) || defined(_WIN64) // Windows-specific includes
#include <windows.h>
#elif defined(__linux__) // X11-specific includes for Linux
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#endif

void showPopup(const std::string& message, const std::string& title) {
#if defined(_WIN32) || defined(_WIN64)
    // Windows-specific popup using MessageBox
    MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONINFORMATION);
#elif defined(__linux__)
    // Linux-specific popup using X11
    Display* display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Unable to open X display.\n";
        return;
    }

    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);

    // Create a simple window
    Window win = XCreateSimpleWindow(display, root, 100, 100, 400, 200, 1,
                                     BlackPixel(display, screen), WhitePixel(display, screen));

    // Set window title
    XStoreName(display, win, title.c_str());

    // Select input events for the window
    XSelectInput(display, win, ExposureMask | KeyPressMask);

    // Map the window (make it visible)
    XMapWindow(display, win);

    // Create graphics context
    GC gc = XCreateGC(display, win, 0, NULL);

    // Event loop for handling window events
    XEvent event;
    while (true) {
        XNextEvent(display, &event);

        if (event.type == Expose) {
            // Draw the message in the window
            XDrawString(display, win, gc, 50, 100, message.c_str(), message.length());
        }

        if (event.type == KeyPress) {
            // Exit on key press
            break;
        }
    }

    // Cleanup
    XDestroyWindow(display, win);
    XCloseDisplay(display);
#endif
}
