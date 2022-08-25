#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <system_error>
#include <map>
#include <utility>
#include <chrono>


#ifndef BACKI_CORE_H
#define BACKI_CORE_H

typedef enum
{
    ERR_SUCCESS = 0x00,
    ERR_FILE_NOT_FOUND,
    ERR_ADDRESS_INVALID,
    ERR_BAD_ARGUMENT,

    ERR_UNKNOWN = 0xFF
}ERR_TYPE;

typedef std::map< std::string, std::int64_t> files;
/*  In this particular case file size could be negetive, when modified files be smaller than initial one, so I have decided to save size differences
 *  in int64_t rather than size_t in these case and because of space calculations.
*/


class BackiCore
{
public:

    BackiCore();

    BackiCore(const std::string& des, const std::string& src);

    ERR_TYPE cpy();

    ERR_TYPE cpy(const std::string& des, std::string src);

private:

    std::string                         desPath;
    std::string                         srcPath;
    files                               diff;
};

#endif