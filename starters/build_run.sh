#!/bin/bash

docker build . -t webserv-env
docker run --rm -it -p 8080:8080 webserv-env /bin/bash
