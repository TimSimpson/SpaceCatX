#ifndef FILE_CATCLIENT_HPP
#define FILE_CATCLIENT_HPP

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

using boost::asio::ip::tcp;

class CatClient {
public:
    template<typename T1, typename T2>
    CatClient(T1 host, T2 port)
    :   ioService()
    ,   socket(ioService) {
        connect(host, port);
    }

    void MoveX(int v) {
        if (v > 0) {
            Send(str(boost::format("x+%d") % v));
        } else {
            Send(str(boost::format("x%d") % v));
        }
    }

    void MoveY(int v) {
        if (v > 0) {
            Send(str(boost::format("y+%d") % v));
        } else {
            Send(str(boost::format("y%d") % v));
        }
    }

    bool Crashed() {
        return (Send("status").substr(0, 5) == "ERROR");
    }

    std::string Status() {
        return Send("status");
    }

    int X() {
        return boost::lexical_cast<int>(Send("x"));
    }

    int Y() {
        return boost::lexical_cast<int>(Send("y"));
    }

    std::string Send(std::string command) {
        char buffer[1024];
        std::sprintf(buffer, "%4d", static_cast<int>(command.size()));
        boost::asio::write(socket, boost::asio::buffer(buffer, 4));
        boost::asio::write(socket, boost::asio::buffer(command.c_str(),
                                                       command.size()));
        boost::asio::read(socket, boost::asio::buffer(buffer, 4));
        size_t len = std::min(std::atoi(buffer), 1023);
        boost::asio::read(socket, boost::asio::buffer(buffer, len));
        buffer[len] = 0;
        std::string response(buffer, len);
        return response;
    }

private:
    boost::asio::io_service ioService;
    boost::asio::ip::tcp::socket socket;

    template<typename T1, typename T2>
    void connect(T1 host, T2 port) {
        using boost::asio::ip::tcp;
        tcp::resolver resolver(ioService);
        tcp::resolver::query query(host, port);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        boost::asio::connect(socket, endpoint_iterator);
    }
};


#endif
