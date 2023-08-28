# webserv
Create a basic HTTP server from scratch in C++.

## Usage

Creates and starts two containers. One with webserv connected to port `8080` and another for testing purposes with Nginx connected to port `8181` :
``` bash
make
```

- ` make cat_log_webserv ` : Displays webserv log file. It lists every connection and **HTTP** request received.
- ` make it_webserv ` :  Enters the webserv container in interactive mode.
- ` make fclean ` : Stops and deletes **ALL** containers **(Note that this will delete all your other containers, if any)**.
- Other commands are available in the Makefile.

The configuration file is located in ` srcs/requirements/conf/webserv.conf `
