#!/bin/bash
docker build -t woody .
docker run --security-opt seccomp=unconfined -v"$PWD":"/root/woody" -it woody
