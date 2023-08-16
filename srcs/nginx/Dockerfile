
#
# For testing
#

FROM		debian:buster

RUN			apt-get update				\
				&& apt-get install -y	\
					nginx

COPY		./conf/nginx.conf /etc/nginx/conf.d

EXPOSE		8181

CMD			["nginx", "-g", "daemon off;"]
