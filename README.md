# remote-cursor-controller
We do a little trolling

# Usage

First build client and server executables:

```
make client
make server
```

The server will run on your machine, and the client will run on the target's machine.

Run the server with `./server` first, and then on the target machine, run `./client <host ip>`. You can obtain the host ip by using `ip addr` on the host machine.
