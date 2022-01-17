#include <X11/X.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

void warp_mouse(int sock)
{
    Display *display = XOpenDisplay(0);
    int scr = XDefaultScreen(display);
    Window root = XRootWindow(display, scr);

    while (true)
    {
        char buf[100] = { 0 };
        read(sock, buf, 100 * sizeof(char));

        if (strlen(buf) == 0)
            continue;

        int type = -1;
        sscanf(buf, "%d", &type);

        switch (type)
        {
        case -1:
            break;
        case 0:
        {
            int x, y;
            sscanf(buf, "%*d %d %d", &x, &y);
            XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
            XFlush(display);
        } break;
        case 1:
            return;
        case 2:
        {
            int btn, down;
            sscanf(buf, "%*d %d %d", &btn, &down);
            XTestFakeButtonEvent(display, btn, down, CurrentTime);
            XFlush(display);
        } break;
        case 3:
        {
            system("xdg-open https://www.youtube.com/watch?v=dQw4w9WgXcQ");
        } break;
        }
    }

    XCloseDisplay(display);
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        fprintf(stderr, "Error: no ip provided\n");
        exit(EXIT_FAILURE);
    }

    int sock = 0;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Failed to create socket\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0)
    {
        fprintf(stderr, "Invalid address\n");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        fprintf(stderr, "Failed to connect to server\n");
        exit(EXIT_FAILURE);
    }

    warp_mouse(sock);

    return 0;
}

