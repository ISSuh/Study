#include <iostream>
#include <mosquittopp.h>

template <typename DataType>
class mqttWrapper : public mosqpp::mosquittopp{
  public:
    mqttWrapper(const char *id, const char *ip, int port, int keepAlive = 60,
                bool nonBlock = false, bool autoLoop = false);
    ~mqttWrapper();

    bool Pub(const char* Topic, DataType &data, int mid);
    bool Sub(const char* Topic, int mid);
    int get_messageLength(const char* Topic);
    void Set_QOS(int qos){QOS = qos;}
    void disconnect();

  private:
    void on_connect(int rc){
        if(!rc)
            std::cout << "Connect!\n";
        else
            std::cout << "Connected Fail with : " << rc << std::endl;
        }

    void on_disconnect(int rc){
        if(!rc)
            std::cout << "Disconnect!\n";
        else
            std::cout << "Disconnected Fail with : " << rc << std::endl;
        }

    void on_message(const struct moquitto_message *message);
    void on_subscribe(int mid, int qos_count, const int *granted_qos){
         std::cout << "Subsribe Success!\n";
         }
    void on_publish(int mid){std::cout << "Publish Success!\n";}
    void on_unsubscribe(int mid){std::cout << "UnSubsribe Success!\n";}

    bool loop = false;
    int messageLength;
    DataType *MSG = nullptr;
    int messageID;
    int QOS = 0;
};


template <typename DataType> 
mqttWrapper<DataType>::mqttWrapper(const char *id, const char *ip, int port, int keepAlive, 
                            bool nonBlock, bool autoLoop) : mosquittopp(id){
    mosqpp::lib_init();

    if(nonBlock)
        connect_async(ip, port, keepAlive);
    else
        connect(ip, port, keepAlive);

    if(loop)
        loop_start(); 
}

template <typename DataType> 
mqttWrapper<DataType>::~mqttWrapper(){ 
}


template <typename DataType> 
void mqttWrapper<DataType>::on_message(const struct moquitto_message *message){
    std::cout << "Receive Message!\n";
    // MSG = message->payload;
}

template <typename DataType> 
int mqttWrapper<DataType>::get_messageLength(const char *Topic){
    return 1;
}

template <typename DataType> 
bool mqttWrapper<DataType>::Pub(const char* Topic, DataType &data, int mid){
    int ret = publish(mid, Topic, sizeof(DataType), data ,QOS, false);
    return ( ret == MOSQ_ERR_SUCCESS );
}

template <typename DataType> 
bool mqttWrapper<DataType>::Sub(const char* Topic, int mid){
    int ret = subscribe(mid, Topic, QOS);
    return ( ret == MOSQ_ERR_SUCCESS );
}

template <typename DataType> 
void mqttWrapper<DataType>::disconnect(){
        if(loop)
            loop_stop();

        disconnect();
        mosqpp::lib_cleanup();
}