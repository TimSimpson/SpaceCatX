// The following configures symbols for export if needed.
#define MACARONI_LIB_CREATE_SpaceCatX___Cat___DEV___lib

#include "CatServer.hpp"
#include <boost/asio.hpp>
#include <chrono>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <memory>
#include <thread>

#include <Cat/SpaceCat.h>
#include <Lp3/Log.h>

using std::cout;
using std::string;
using boost::asio::ip::tcp;


namespace Cat {

    class Session : public std::enable_shared_from_this<Session> {
        private: char buffer[1024];
        private: SpaceCat & cat;
        private: tcp::socket socket;

        public: Session(tcp::socket socket, SpaceCat & cat)
        :   cat(cat)
        ,   socket(std::move(socket)) {
        }

        private: void exitLoop() {
        }

        private: void readHeader() {
            auto self = shared_from_this();
            boost::asio::async_read(
                socket,
                boost::asio::buffer(buffer, 4),
                [this, self](boost::system::error_code ec, std::size_t) {
                    if (!ec) {
                        size_t msgLength = std::atoi(buffer);
                        readBody(msgLength, "");
                    } else {
                        LP3_LOG_ERROR("Session was whacked!");
                        exitLoop();
                    }
                }
            );
        }

        private: void readBody(const size_t msgLength,
                               const string currentMessage) {
            auto self = shared_from_this();
            boost::asio::async_read(
                socket,
                boost::asio::buffer(buffer, std::min(msgLength, sizeof(buffer))),
                [this, self, msgLength, currentMessage](
                        boost::system::error_code ec,
                        std::size_t length) {
                    if (!ec) {
                        const string newMessage
                            = currentMessage + string(buffer, length);
                        const auto nextLength = msgLength - length;
                        if (nextLength > 0) {
                            readBody(nextLength, newMessage);  // read more
                        } else {
                            const auto output = cat.InputCommand(newMessage);
                            writeResponseHeader(output);
                        }
                    } else {
                        LP3_LOG_ERROR("Session whacked as body was read.");
                        exitLoop();
                    }
                }
            );
        }

        private: void writeResponseHeader(const std::string response) {
            std::sprintf(buffer, "%4d", static_cast<int>(response.length()));
            auto self = shared_from_this();
            boost::asio::async_write(
                socket,
                boost::asio::buffer(buffer, 4),
                [this, response, self](boost::system::error_code ec,
                                       std::size_t) {
                    if (!ec) {
                        writeResponseBody(response);
                    } else {
                        LP3_LOG_ERROR("Error sending responseHeader!");
                        exitLoop();
                    }
                }
            );
        }

        private: void writeResponseBody(const std::string response) {
            auto self = shared_from_this();
            boost::asio::async_write(
                socket,
                boost::asio::buffer(response.c_str(), response.length()),
                [this, self](boost::system::error_code ec, std::size_t) {
                    if (!ec) {
                        Start();  // repeat the process
                    } else {
                        LP3_LOG_ERROR("Error sending responseBody!");
                        exitLoop();
                    }
                }
            );
        }

        public: void Start() {
            readHeader();
        }
    };

    class Server {
        private: tcp::acceptor acceptor;
        private: SpaceCat & cat;
        private: tcp::socket socket;

        public: Server(SpaceCat & cat,
                       boost::asio::io_service & service,
                       const tcp::endpoint & endpoint)
        :   acceptor(service, endpoint)
        ,   cat(cat)
        ,   socket(service) {
            acceptConnection();
        }

        private: void acceptConnection() {
            acceptor.async_accept(socket,
                [this](boost::system::error_code ec) {
                    if (!ec) {
                        std::make_shared<Session>(std::move(socket), cat)
                            ->Start();
                    }
                    acceptConnection();
                });
        }
    };

    MACARONI_LIB_DECL_SpaceCatX___Cat___DEV___lib
    CatServer::CatServer()
    :   ioService(new boost::asio::io_service()) {
    }

    MACARONI_LIB_DECL_SpaceCatX___Cat___DEV___lib
    CatServer::~CatServer() {
        delete static_cast<boost::asio::io_service *>(ioService);
    }

    MACARONI_LIB_DECL_SpaceCatX___Cat___DEV___lib
    void CatServer::RunServer(SpaceCat & cat, int port) {
        const tcp::endpoint endpoint(tcp::v4(), port);
        const auto ptr = static_cast<boost::asio::io_service *>(ioService);
        Server server(cat, *ptr, endpoint);
        LP3_LOG_DEBUG("Starting Cat...\n");
        ptr->run();
        LP3_LOG_DEBUG("End of Cat Server\n");
    }

    MACARONI_LIB_DECL_SpaceCatX___Cat___DEV___lib
    void CatServer::Stop() {
        static_cast<boost::asio::io_service *>(ioService)->stop();
        while(!static_cast<boost::asio::io_service *>(ioService)->stopped()) {
            std::chrono::milliseconds t(2000);
            std::this_thread::sleep_for(t);
        }
    }
}
