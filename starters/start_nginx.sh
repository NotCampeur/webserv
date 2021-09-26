#!/bin/bash

	chmod -R 755 /root/wordpress/*

	cp ressources/nginx_config/default.conf /etc/nginx/sites-available/default

	chown -R www-data:www-data /root/wordpress/*
	chown www-data:www-data /root
	chown -R mysql:mysql /var/run/mysqld/ /var/lib/mysql/
	
	service mysql start
	service php7.2-fpm start
	service nginx start