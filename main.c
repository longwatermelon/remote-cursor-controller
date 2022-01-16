#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <X11/Xlib.h>

void mouse_pos(Display *display, Window *root, int *x, int *y)
{
    XEvent evt;
    XQueryPointer(display, *root, &evt.xbutton.root, &evt.xbutton.subwindow,
                &evt.xbutton.x_root, &evt.xbutton.y_root,
                &evt.xbutton.x, &evt.xbutton.y, &evt.xbutton.state);

    *x = evt.xbutton.x_root;
    *y = evt.xbutton.y_root;
}

int main()
{
    Display *display = XOpenDisplay(0);
    int scr = XDefaultScreen(display);
    Window root = XRootWindow(display, scr);

    int x, y;
    mouse_pos(display, &root, &x, &y);

    for (int i = 0; i < 100; ++i)
    {
        XWarpPointer(display, None, root, 0, 0, 0, 0, x + i, y + i);
        usleep(100);
    }

//    XWarpPointer(display, None, root, 0, 0, 0, 0, 100, 100);
//    XFlush(display);


    XCloseDisplay(display);

    return 0;
}

