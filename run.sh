#!/bin/bash

xhost +

docker build -t armgame . && \
docker run -it \
  -e DISPLAY=host.docker.internal:0 \
  armgame