#!/bin/bash

if [ $# -ne "1" ]
then
	echo "Provide server config file as script argument"
else
	echo "Configuration file: " $1
	chmod -R 755 /root/wordpress/*

	chown -R mysql:mysql /var/run/mysqld/ /var/lib/mysql/
	service mysql start
	make
	./webserv $1
fi
