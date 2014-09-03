#ifndef FILE_FLAGS_H
#define FILE_FLAGS_H

#include <map>
#include <memory>
#include <string>

class Flags {
public:
    void add_from_argument(const std::string & arg);

private:
    std::map<std::string, std::string> guts;
};

#endif
