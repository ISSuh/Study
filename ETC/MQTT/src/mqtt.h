#include <mosquittopp.h>

template<typename S, typename R>
class mqttWrapper : public mosqpp::mosquittopp{
    public:
        mqttWrapper(const char *id, const char *ip, int port, int keepAlive = 60, 
                            bool nonBlock = false, bool autoLoop = false);
        ~mqttWrapper();

        bool publish(S data);
        int get_messageLength(char *Topic);

    private:
        void on_connect(int rc);
        void on_disconnect(int rc);
        void on_message(const struct moquitto_message *message);
        void on_subscribe(int mid, int qos_count, const int *granted_qos);
        void on_publish(int mid);
        void on_unsubscribe(int mid);
        
        bool loop = false;
        int messageLength;
        R *ReceiveMsg = NULL;
        S *sendMsg = NULL;
};