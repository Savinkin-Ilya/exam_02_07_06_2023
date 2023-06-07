FROM ubuntu

LABEL author="Gerasenkov Ilya 221-352"

ENV TZ=Europe/Moscow  
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone  
RUN apt-get update  
RUN apt-get install qt5-default -y  
RUN apt-get install qtbase5-dev -y
RUN apt-get install qt5-qmake  
RUN apt-get install build-essential -y 

WORKDIR /root/
RUN mkdir Gerasenkov
WORKDIR /root/Gerasenkov/

COPY *.cpp /root/Gerasenkov/
COPY *.h /root/Gerasenkov/
COPY *.pro /root/Gerasenkov/

RUN qmake -o hallServer echoServer.pro 
RUN make hallServer

EXPOSE 33333