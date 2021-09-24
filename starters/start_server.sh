#!/bin/bash

	# cp ressources/nginx_conf/default.conf /etc/nginx/conf.d/
	# php-fpm &
	# nginx

	chown -R mysql:mysql /var/run/mysqld/ /var/lib/mysql/ && mysqld &
	chmod -R 755 /root/wordpress/*
	make
	echo "172.17.0.2	server1" >> /etc/hosts
	./webserv $1 $2 $3 $4
