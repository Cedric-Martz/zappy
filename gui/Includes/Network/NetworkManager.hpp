/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** NetworkManager.hpp
*/

#ifndef B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_NETWORKMANAGER_HPP
    #define B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_NETWORKMANAGER_HPP
    #include "RayLib.hpp"
    #include "Game.hpp"
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdio.h>
    #include <sstream>

namespace rl
{
    class NetworkManager {
    public:
        static NetworkManager &getInstance();

        void init();
        void stop();
        void setPort(const uint16_t port);
        uint16_t getPort();
        void setIp(const std::string &ip);
        std::string getIp();

        NetworkManager &operator<<(const std::string &string);
        NetworkManager &operator>>(std::string &string);

        int getFd() const;
        std::string getBuffer();

        bool setSocket();
        std::string &readToBuffer();
        int getBufferLen() const;
        void clearBuffer();
        void interpretCommand(const std::string &buffer,
                              Game &scene);

        void readSocketInput(Game &scene);

    private:
        NetworkManager();
        ~NetworkManager();

        int _fd;
        bool _isConnected;
        uint16_t _port;
        std::string _ip;
        sockaddr_in _serverAddress;
        std::string _buffer;
        fd_set _writeFds;
        fd_set _readFds;
        std::unordered_map<std::string, std::function<void(const std::vector<std::string> &, Game &)>> _commands;
    };
}

#endif /*!B_YEP_400_STG_4_1_ZAPPY_AUGUSTIN_GROSNON_NETWORKMANAGER_HPP*/
