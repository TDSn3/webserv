
#
# For macOS
#

FROM		ubuntu:22.04

RUN			apt-get update				\
				&& apt-get install -y	\
					curl				\
					vim					\
					gcc					\
					g++					\
					make				\
					valgrind					

WORKDIR		/app
COPY		. /app

RUN			make re

EXPOSE		8080

# CMD			["./webserv"]
CMD			./webserv > ./log 2>&1
# CMD			valgrind ./webserv > ./log 2>&1
