#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

struct GPS {
    struct frame {
        double latitude;
        double longitude;
        double altitude;
        double course;
        char utcTime[16];
        char utcData[16];
   };
   
   struct time{
    uint32_t secs;
    uint32_t nsecs;
   };
   
    uint32_t vid;
    time stamp;
    uint32_t length;
    frame Frame;
};

void error_handling(const char *message){
        std::cerr << message <<"\n";
        exit(1);
}

int main(int argc, char *argv[]){
        int sock;
        struct sockaddr_in serv_addr;
        int str_len;
        GPS Data;
        const char *SuccessMSG = "Success";
        const char *FailMSG = "Fail";
        
        
        if (argc != 3){
               std::cout <<"Usage :  " << argv[0] << " <IP> <port>\n";
               exit(1);
        }

        sock = socket(PF_INET, SOCK_STREAM, 0);
        if (sock == -1)
               error_handling("socket() error");

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
        serv_addr.sin_port = htons(atoi(argv[2]));

        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
               error_handling("connect() error");
		
		while(1){
			
			usleep(100);
			
                        memset(&Data, 0, sizeof(Data));
        	        str_len = recv(sock, (void*)&Data, sizeof(Data), 0);
        	        if (str_len == -1){ 
           	        	send(sock,(void*)&FailMSG,sizeof(FailMSG), 0);
            	                error_handling("read() error");
                          }
                         else
            	                send(sock,(void*)&SuccessMSG,sizeof(SuccessMSG), 0);

                        std::cout << "Timestamp(sec) : " << Data.stamp.secs << "\n"
                                        << "Timestamp(nsec) : " << Data.stamp.nsecs << "\n"
                                        << "latitude : " << Data.Frame.latitude << "\n"
                                        << "longitude : " << Data.Frame.longitude << "\n"
                                        << "altitude : " << Data.Frame.altitude << "\n"
                                        << "course : " << Data.Frame.course << "\n";
        }
        
        close(sock);
        return 0;
}



