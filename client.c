#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <X11/Xlib.h>

void warp_mouse(int sock)
{
    Display *display = XOpenDisplay(0);
    int scr = XDefaultScreen(display);
    Window root = XRootWindow(display, scr);

    XWarpPointer(display, None, root, 0, 0, 0, 0, 100, 100);

    while (true)
    {
        char buf[100] = { 0 };
        read(sock, buf, 50);

        int x, y;
        sscanf(buf, "%d %d", &x, &y);

        printf("Client: %d %d\n", x, y);
        XWarpPointer(display, None, root, 0, 0, 0, 0, x, y);
        XFlush(display);
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

