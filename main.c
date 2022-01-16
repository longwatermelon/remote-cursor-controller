#include <stdio.h>
#include <unistd.h>
#include <X11/Xlib.h>

int main()
{
    Display *display = XOpenDisplay(0);
    int scr = XDefaultScreen(display);
    Window root = XRootWindow(display, scr);

    XWarpPointer(display, None, root, 0, 0, 0, 0, 100, 100);
    XFlush(display);

    XCloseDisplay(display);

    return 0;
}

