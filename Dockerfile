FROM debian:latest
RUN apt-get update
RUN apt-get -y install gcc-avr avr-libc virtualenv
