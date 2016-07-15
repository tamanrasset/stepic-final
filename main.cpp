#include <iostream>
#include <string>
#include <unistd.h>

struct Config
{
    std::string ip;
    int port;
    std::string dir;
};

Config GetConfig(int argc, char**argv)
{
    const std::string optStr = "h:p:d:";
    Config config;
    auto opt = getopt( argc, argv, optStr.c_str());
    while( opt != -1 ) {
        switch( opt ) {
            case 'h':
                config.ip = optarg;
                break;
                
            case 'p':
                config.port = atoi(optarg);
                break;
                
            case 'd':
                config.dir = optarg;
                break;
        }
        
        opt = getopt( argc, argv, optStr.c_str());
    }
    
    std::cout << "ip: " << config.ip
              << "; port: " << config.port
              << "; dir: " << config.dir << std::endl;
    return config;
}

int main (int argc, char ** argv)
{
    auto cfg = GetConfig(argc, argv);

    if(fork() == 0){
        std::cout << "daemon started" << std::endl;
        //start server
    }
    return 0;
}
