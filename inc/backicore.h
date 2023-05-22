#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <system_error>
#include <map>
#include <utility>
#include <chrono>
#include <string_view>


#ifndef BACKICORE_H
#define BACKICORE_H


enum class ERR_TYPE
{
    ERR_SUCCESS = 0x00,
    ERR_FILE_NOT_FOUND,
    ERR_ADDRESS_INVALID,
    ERR_BAD_ARGUMENT,
    ERR_NOTHING_TODO,
    ERR_OPERATION_FAILED,

    ERR_UNKNOWN = 0xFF
};

typedef std::map< std::string_view, std::int64_t> files;
/*  In this particular case file size could be negetive, when modified files be smaller than initial one, so I have decided to save size differences
 *  in int64_t rather than size_t in these case and because of space calculations.
*/

class BackiCore
{
public:

    BackiCore();

    BackiCore( std::string_view des, std::string_view src);


    ERR_TYPE makeCpyList();

    ERR_TYPE makeCpyList( std::string_view des, std::string_view src);

    ERR_TYPE cpy();

    ERR_TYPE cpyAsync();


    ~BackiCore();

private:

    std::string_view                    desPath;
    std::string_view                    srcPath;
    files                               diff;
    std::size_t                         needSpace;

};

#endif // BACKICORE_H
