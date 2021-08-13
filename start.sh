#!/bin/bash

docker build -t woody .
docker run -it --mount src=`pwd`,target=/root/woody,type=bind woody