
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

EXPOSE		8080
