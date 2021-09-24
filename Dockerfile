FROM ubuntu:18.04

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get install -y vim git wget valgrind clang make nginx dos2unix

RUN apt-get install -y php php-cgi php-mysql

#Python3 used with cgi script
RUN apt-get install -y python3

RUN apt-get install -y unzip

WORKDIR /root

RUN	wget https://wordpress.org/latest.zip && \
	unzip latest.zip

WORKDIR /root/wordpress

RUN mv wp-config-sample.php wp-config.php && \
	sed -i "s/database_name_here/wordpress/" wp-config.php && \
	sed -i "s/username_here/root/" wp-config.php && \
	sed -i "s/password_here/password/" wp-config.php

WORKDIR /

RUN apt-get install -y mysql-server-5.7 mysql-client-5.7

RUN sed -i "s/127.0.0.1/0.0.0.0/" /etc/mysql/mysql.conf.d/mysqld.cnf

RUN mkdir /var/run/mysqld

RUN chown -R mysql:mysql /var/lib/mysql /var/run/mysqld && \
	service mysql start; \
	mysql -u root -e "CREATE DATABASE wordpress;"; \
	mysql -u root -e "UPDATE mysql.user SET plugin='mysql_native_password';"; \
	mysql -u root -e "UPDATE mysql.user SET host = '%' WHERE USER = 'root';"; \
	mysql -u root -e "UPDATE mysql.user SET authentication_string=PASSWORD(\"password\") WHERE user='root';"; \
	mysql -u root -e "SELECT host, user, plugin, authentication_string FROM mysql.user WHERE user='root';"; \
	mysql -u root -e "FLUSH PRIVILEGES;";
	
RUN sed -i 's/;cgi.fix_pathinfo=1/cgi.fix_pathinfo=0/g' /etc/php/7.2/cgi/php.ini

RUN	apt-get update && apt-get install -y nginx php-fpm php-json php-mbstring php-mysqli php-phar curl

RUN mkdir /app

WORKDIR /app
EXPOSE 8080

COPY . /app
