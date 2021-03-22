# remote-shell
Remote shell Client-Server implementation in C

## Features:
1. Remote shell used for simulate core concepts of OS system calls
2. server.c runs a process which listens on `localhost:###`
3. client.c runs a process to look for that socket address
4. If the server is there and accepting, create a new socket connection
5. The connection stays open indefinitely, until the client inputs `exit`
6. The client reads input line by line from `stdin`
7. The client sends this data to the server, the server handles the processing
8. The server makes a system call to create a child process and execute the input
9. The exec System call is looking to execute a bash command and store it in variable
10. Finally, the server will send back the contents of the output to the client
11. The client renders the output, and continues to sit on the connection

### Client Process & Server Process

#### Client : Typically request to server for information.

* Create a socket with the ```socket()``` system call
* Connect socket to the address of the server using the ```connect()``` system call
* Send and receive data. There are a number of ways to do this, but the simplest way is to use the ```read()``` and ```write()``` system calls

#### Server : Takes request from the clients, perform required processing, and send it to the client

* Create a socket with the ```socket()``` system call
* Bind the socket to an address (IP + port) using the ```bind()``` system call.
* Listen for connections with the ```listen()``` system call
* Accept a connection with the ```accept()``` system call. This call typically blocks the connection until a client connects with the server
* Send and receive data using the ```read()``` and ```write()``` system calls

<p align="center">
  <img src="https://user-images.githubusercontent.com/19291492/44955906-363dae80-aef6-11e8-9795-161a90f30b1e.png"/>
</p>

taken to [https://github.com/kusdavletov/](https://github.com/kusdavletov/socket-programming-simple-server-and-client)

## How to run
1. Clone the repo
2. Run the following command in the directory to compile
   * `make all` - the Makefile will generate a `server` or `client` executable
3. Open two separate terminals and run `server` in the first open
4. Once the server is running, run `client` in the other Once
5. Play around and enjoy!