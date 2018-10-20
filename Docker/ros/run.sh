#!/usr/bin/env bash

docker run --rm -it --cap-add=NET_ADMIN --device /dev/net/tun --name vpn-00 ros_vpn
