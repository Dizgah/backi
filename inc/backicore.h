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

enum class LOG_LEVEL
{
    LOG_LEVEL_ENABLE,
    LOG_LEVEL_DISABLE
};

typedef std::map< std::string, std::int64_t> files;
/*  In this particular case file size could be negetive, when modified files be smaller than initial one, so I have decided to save size differences
 *  in int64_t rather than size_t in these case and because of space calculations.
*/

class BackiCore
{
public:

    BackiCore( LOG_LEVEL log = LOG_LEVEL::LOG_LEVEL_DISABLE);

    BackiCore( const std::string& src, const std::string& des, LOG_LEVEL log = LOG_LEVEL::LOG_LEVEL_DISABLE );


    ERR_TYPE makeCpyList();

    ERR_TYPE makeCpyList( const std::string& src, const std::string& des );

    ERR_TYPE checkConfirmCpyList();//@TODO:need to check if user wanted to modify the copy list!

    ERR_TYPE cpy();

    ERR_TYPE cpyAsync();

    ERR_TYPE checkCpy();//@TODO:need to check if all files have been copied successfully!


    ~BackiCore();

private:

    std::string                     desPath;
    std::string                     srcPath;
    files                           diff;
    std::size_t                     needSpace;
    LOG_LEVEL                       logLevel;
};

#endif // BACKICORE_H
