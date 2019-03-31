import argparse
from struct import *
import os
import sys
import paho.mqtt.client as mqtt
import time

def on_connect(client, userdata, flags, rc):
    print("Connected Broker " + str(rc))

def on_publish(client, usedata, mid):
    print("Publish Msg")

def main(args):
    print("MQTT Client Start!")

    client = mqtt.Client()
    client.on_publish = on_publish

    client.connect("localhost", args.port, 60)

    try:
        while True:
            dataSize = 16
            x = 5
            y = 10
 
            fmt = '>Iii'
            sendData = pack(fmt,dataSize,x,y)

            client.publish("/test/msg", sendData)
            time.sleep(0.2)
    except KeyboardInterrupt:
        print("Interrupted by user, shutting down...")
    


if __name__ == "__main__":
    parser = argparse.ArgumentParser();
    parser.add_argument("-p", "--port", type=int, default=33669, help="MQTT Broker Port")
    parsed_known_args, unknown_args = parser.parse_known_args(sys.argv[1:])

    main(parsed_known_args)
