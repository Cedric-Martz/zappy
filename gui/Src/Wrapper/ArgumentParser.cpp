/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** ArgumentParser
*/

#include "ArgumentParser.hpp"

namespace rl
{
    ArgumentParser &ArgumentParser::getInstance()
    {
        static ArgumentParser instance;
        return instance;
    }

    ArgumentParser::ArgumentParser()
        : _port(""),
        _ip("")
    {}

    ArgumentParser::~ArgumentParser() {}

    int ArgumentParser::setInfo(int argc, char **argv)
    {
        if (argc == 1)
            return 1;
        if (argc != 5 && argc != 3) {
            std::cerr << "Bad numbers of arguments" << std::endl;
            return 0;
        }
        if (std::string(argv[1]) == "-p" && argv[2][0] != '-')
            _port = std::string(argv[2]);
        if (argv[3] && std::string(argv[3]) == "-h" && argv[4][0] != '-')
            _ip = std::string(argv[4]);
        if (std::string(argv[1]) == "-h" && argv[2][0] != '-')
            _ip = std::string(argv[2]);
        if (argv[3] && std::string(argv[3]) == "-p" && argv[4][0] != '-')
            _port = std::string(argv[4]);
        if (_port.empty() && _ip.empty()) {
            std::cerr << "Bad arguments" << std::endl;
            return 0;
        }
        if (!_port.empty()) {
            int tmp = std::stoi(_port);
            if (tmp <= 0) {
                std::cerr << "Bad number of port" << std::endl;
                return 0;
            }
        }
        if (!_ip.empty()) {
            if (_ip == "localhost")
                return 1;
            boost::system::error_code ec;
            boost::asio::ip::address::from_string(_ip, ec);
            if (ec) {
                std::cerr << ec.message() << std::endl;
                return 0;
            }
        }
        return 1;
    }

    std::string ArgumentParser::getPort() const
    {
        return _port;
    }

    std::string ArgumentParser::getIp() const
    {
        return _ip;
    }
}
