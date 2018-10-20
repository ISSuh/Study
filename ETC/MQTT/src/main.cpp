#include <iostream>
#include "mqtt.hpp"

int main(){
    mqttWrapper<int> TEST("test", "localhost", 33669);
    TEST.disconnect();
}