#!/bin/bash

if [ $# -ne "1" ]
then
	echo "Provide server config file as script argument"
else
	echo "Configuration file: " $1
	chown -R mysql:mysql /var/run/mysqld/ /var/lib/mysql/ && mysqld &
	chmod -R 755 /root/wordpress/*
	make
	./webserv $1
fi