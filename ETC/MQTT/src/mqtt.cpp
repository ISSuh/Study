#include <iostream>
#include "mqtt.h"

template <typename T> 
mqttWrapper<T>::mqttWrapper(const char *id, const char *ip, int port, int keepAlive = 60, 
                            bool nonBlock = false, bool autoLoop = false) : mosquittopp(id), loop(autoLoop){
    mosqpp::lib_init();

    if(nonBlock)
        connect_async(ip, port, keepAlive);
    else
        connect(ip, port, keepAlive);

    if(loop)
        loop_start(); 
}

template <typename T> 
mqttWrapper<T>::~mqttWrapper(){
    if(loop)
        loop_stop();

    disconnect();
    mosqpp::lib_cleanup();
}

template <typename T> 
void mqttWrapper<T>::on_connect(int rc){
    std::cout << "Connected with code : " << rc << std::endl;
}

template <typename T> 
void mqttWrapper<T>::on_disconnect(int rc){
    std::cout << "Disconnect with cod : " << rc << std::endl;
}

template <typename T> 
void mqttWrapper<T>::on_message(const struct moquitto_message *message){
    std::cout << "Receive Message!\n";
    msg = (R)message->payload;
}

template <typename T> 
void mqttWrapper<T>::on_subscribe(int mid, int qos_count, const int *granted_qos){
    std::cout << "Subsribe Success!\n";
}

template <typename T> 
void mqttWrapper<T>::on_publish(int mid){
    std::cout << "Publish Success!\n";
}

template <typename T> 
void mqttWrapper<T>::on_unsubscribe(int mid){
    std::cout << "UnSubsribe Success!\n";
}

template <typename T> 
int mqttWrapper<T>::get_messageLength(char *Topic){
    return 1;
}

template <typename T> 
bool mqttWrapper<T>::publish(char *Topic){
    return 1;
}