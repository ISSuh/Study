FROM       ubuntu:16.04
MAINTAINER issuh@aspringcloud.com
RUN        apt-get -y update

RUN apt-get -y install curl lsb-release net-tools openvpn

# 1. ros 설치

RUN sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

RUN apt-key adv --keyserver hkp://ha.pool.sks-keyservers.net:80 --recv-key 421C365BD9FF1F717815A3895523BAEEB01FA116

RUN apt-get -y update

RUN apt-get -y install ros-kinetic-desktop-full

RUN rosdep init

RUN rosdep update

RUN echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
RUN echo "export ROS_MASTER_URI=http://10.8.0.1:11311" >> ~/.bashrc
RUN echo "export ROS_HOSTNAME=127.0.0.1" >> ~/.bashrc

RUN /bin/bash -c "source ~/.bashrc"

# 2. vpn 설정
#RUN mkdir -p /dev/net
#RUN mknod /dev/net/tun c 10 200
#RUN chmod 600 /dev/net/tun
#RUN cat /dev/net/tun 
 
ADD ./client.ovpn ./
RUN cp ./client.ovpn /etc/openvpn/
#RUN install -o root -m 400 client.ovpn /etc/openvpn/client.ovpn

#RUN echo AUTOSTART=all | tee -a /etc/default/openvpn
#RUN /etc/init.d/openvpn restart
#CMD openvpn /etc/openvpn/client.ovpn
CMD openvpn /etc/openvpn/client.ovpn

