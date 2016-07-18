#include <iostream>
#include <string>
#include <unistd.h>
#include "server.hpp"
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;


#define NUM_THREADS 4

struct Config
{
    std::string ip;
    std::string port;
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
                config.port = optarg;
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
    
    logging::add_file_log("sample.log");
    logging::add_common_attributes();

    using namespace logging::trivial;
    src::severity_logger<severity_level> lg;


    if(fork() == 0)
    {
        std::cout << "daemon started" << std::endl;
        http::server3::server s(cfg.ip, cfg.port, cfg.dir, NUM_THREADS);
        s.run();
    }

    return 0;
}
