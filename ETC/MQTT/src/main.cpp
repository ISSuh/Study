#include <iostream>
#include "mqtt.h"

int main(){
    mqttWrapper<int> TEST("test", "localhost", 33669);
}