/*
** EPITECH PROJECT, 2024
** B-YEP-400-STG-4-1-zappy-augustin.grosnon
** File description:
** ArgumentParser
*/

#ifndef ARGUMENTPARSER_HPP_
    #define ARGUMENTPARSER_HPP_
    #include <iostream>
    #include <boost/asio.hpp>
    #include <boost/system/error_code.hpp>

namespace rl {
    class ArgumentParser {
        public:
            static ArgumentParser &getInstance();

            int setInfo(int argc, char **argv);

            std::string getPort() const;
            std::string getIp() const;


        private:
            ArgumentParser();
            ~ArgumentParser();
            std::string _port;
            std::string _ip;
    };
}

#endif /* !ARGUMENTPARSER_HPP_ */
