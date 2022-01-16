# remote-cursor-controller
We do a little trolling

# Building

Depends on x11 and the xtest extension.

```
make client server
```

# Usage

The server will run on your machine, and the client will run on the target's machine.

Run the server with `./server` first, and then on the target machine, run `./client <host ip>`. You can obtain the host ip by using `ip addr` on the host machine.

