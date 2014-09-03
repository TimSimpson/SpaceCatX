#ifndef FILE_CAT_CATSERVER_HPP
#define FILE_CAT_CATSERVER_HPP

#include <Config_Cat.h>
#include <Cat/SpaceCat.h>

namespace Cat {

    class MACARONI_LIB_DECL_SpaceCatX___Cat___DEV___lib CatServer {
        public: CatServer();
        public: ~CatServer();

        public: void RunServer(SpaceCat & cat, int port);
        public: void Stop();

        private: void * ioService; // Due to header issues, have to use void *
    };
}

#endif
