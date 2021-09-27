#!/bin/bash

	# chown -R mysql:mysql /var/run/mysqld/ /var/lib/mysql/ && mysqld &

	chmod -R 755 /root/wordpress/*
	chown -R mysql:mysql /var/run/mysqld/ /var/lib/mysql/
	service mysql start
	make
	./webserv $1 $2 $3 $4
