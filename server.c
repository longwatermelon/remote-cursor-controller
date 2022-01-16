#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>
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

void send_mouse_coords(int sock)
{
    Display *display = XOpenDisplay(0);
    int scr = XDefaultScreen(display);
    Window root = XRootWindow(display, scr);

    while (true)
    {
        int x, y;
        mouse_pos(display, &root, &x, &y);
        char *s = calloc(50, sizeof(char));
        sprintf(s, "%d %d", x, y);
        s = realloc(s, sizeof(char) * (strlen(s) + 1));

        send(sock, s, strlen(s) * sizeof(char), 0);

        usleep(10000);
    }

    XCloseDisplay(display);
}

int main(int argc, char **argv)
{
    int server_fd;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        fprintf(stderr, "Failed to create socket fd\n");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        fprintf(stderr, "Error in setsockopt\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address))<0)
    {
        fprintf(stderr, "Bind failed\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        fprintf(stderr, "Failed to listen\n");
        exit(EXIT_FAILURE);
    }

    printf("Server: Listening for connections\n");

    int addrlen = sizeof(address);
    int new_socket;

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    {
        fprintf(stderr, "Error when accepting connection\n");
        exit(EXIT_FAILURE);
    }

    printf("Server: accepted connection\n");

    send_mouse_coords(new_socket);

    return 0;
}

