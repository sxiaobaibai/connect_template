## How to execute

```
g++ server.cpp -o serve
g++ client.cpp -o client
```

Terminal1:
```
./server
```
Terminal2:
```
./client
```

### Be Careful
file for unix domain socket will be deleted is ctrl + c is pressed.
The default file is is unix_socket.
If a file or directory with the same name as "unix_socket" exists, the file or directory will be deleted.
