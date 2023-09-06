
#
# For macOS
#

FROM		debian:buster

RUN			apt-get update				\
				&& apt-get install -y	\
					procps				\
					gcc					\
					g++					\
					make				\
					valgrind					

WORKDIR		/app
COPY		. /app

RUN			make re

EXPOSE		8080

# CMD			["./webserv", "conf/webserv.conf"]
CMD			["valgrind", "--tool=memcheck", "--track-origins=yes", "--leak-check=full", "--show-leak-kinds=all", "--track-fds=yes", "./webserv", "conf/webserv.conf"]

