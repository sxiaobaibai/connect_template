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
The file for unix domain socket will be deleted after ctrl + c is pressed.
The default file name is "unix_socket".
If a file or directory with the same name as "unix_socket" already exists, the file or directory will be deleted.
