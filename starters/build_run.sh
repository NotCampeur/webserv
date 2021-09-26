#!/bin/bash

docker build . -t webserv-env
docker run --rm -it -p 8080:8080 -p 80:80 webserv-env /bin/bash
