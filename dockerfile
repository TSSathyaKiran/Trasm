FROM ubuntu:latest
RUN apt-get update && apt-get install -y \
    gcc \
    binutils \
    libx11-dev \
    x11-apps 
WORKDIR /armgame
COPY . .
RUN gcc -o mygame createWindow.c -lX11
CMD ["./mygame"]