FROM ubuntu:18.04

LABEL author="Savinkin Ilya 221-352"

ENV TZ=Europe/Moscow  
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone  
RUN apt-get update  
RUN apt-get install qt5-default -y  
RUN apt-get install qtbase5-dev -y
RUN apt-get install qt5-qmake  
RUN apt-get install build-essential -y 

WORKDIR /root/
RUN mkdir Savinkin_221-352
WORKDIR /root/Savinkin_221-352/

COPY *.cpp /root/Savinkin_221-352/
COPY *.h /root/Savinkin_221-352/
COPY *.pro /root/Savinkin_221-352/

RUN qmake -o hallServer echoServer.pro 
RUN make hallServer