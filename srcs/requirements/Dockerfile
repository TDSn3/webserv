
#
# For macOS
#

FROM		debian:buster

RUN			apt-get update				\
				&& apt-get install -y	\
					gcc					\
					g++					\
					make				\
					valgrind					

WORKDIR		/app
COPY		. /app

RUN			make re

EXPOSE		8080

CMD			["./webserv"]
# CMD			["valgrind", "./webserv"]
