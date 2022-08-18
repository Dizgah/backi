#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <system_error>
#include <map>
#include <utility>
#include <chrono>


typedef enum
{
    ERR_SUCCESS             = 0x00,
    ERR_FILE_NOT_FOUND,
    ERR_ADDRESS_INVALID,

    ERR_UNKNOWN             = 0xFF
}ERR_TYPE;

typedef std::map< std::string, std::int64_t> files;
/*  In this particular case file size could be negetive, when modified files be smaller than initial one, so I have decided to save size differences
 *  in int64_t rather than size_t in these case and because of space calculations.
*/


class BackiCore
{
public:

    BackiCore()
    {

    }

    BackiCore( const std::string &des, const std::string &src)
    {
        desPath = des;
        srcPath = src;
    }

    ERR_TYPE cpy()
    {
        return cpy( desPath, srcPath);
    }

    ERR_TYPE cpy( const std::string &des, std::string src)
    {
        files tmpBuf;


        try
        {
            if( ( des.empty()) || ( src.empty()) || ( des == src))
            {
                return ERR_ADDRESS_INVALID;
            }

            for( const std::filesystem::directory_entry &desElement : std::filesystem::recursive_directory_iterator( des))
            {
                std::cout << "des: " << desElement << std::endl;
                tmpBuf.emplace( desElement.path().generic_string(), 0);
            }

            for( const std::filesystem::directory_entry &srcElement : std::filesystem::recursive_directory_iterator( src))
            {
                std::cout << "src: " << srcElement << std::endl;
                files::iterator itr = tmpBuf.find( srcElement.path().generic_string());


                if( itr != tmpBuf.end())//check for modification
                {
                    std::filesystem::directory_entry dr( itr->first);


                    if( srcElement.last_write_time() != dr.last_write_time())
                    {
                        diff.try_emplace( srcElement.path().generic_string(), static_cast< std::int64_t>( dr.file_size() - srcElement.file_size()));
                    }
                }
                else if( diff.try_emplace( srcElement.path().generic_string(), srcElement.file_size()).second)//it's a new file
                {
                    std::cout << "insert Success!" << std::endl;
                }
                else//insreting new file to list has been failed!
                {
                    std::cout << "insert Failed!" << std::endl;
                }
            }



            return ERR_SUCCESS;
        }
        catch( std::filesystem::filesystem_error const &ex)
        {
            std::cout
                << "what():  " << ex.what() << '\n'
                << "path1(): " << ex.path1() << '\n'
                << "path2(): " << ex.path2() << '\n'
                << "code().value():    " << ex.code().value() << '\n'
                << "code().message():  " << ex.code().message() << '\n'
                << "code().category(): " << ex.code().category().name() << '\n';
        }

        return ERR_UNKNOWN;
    }

private:

    std::string                         desPath;
    std::string                         srcPath;
    files                               diff;
};



int main()
{
    BackiCore bk;

    bk.cpy( "./dir1", "./dir2");

    return 0;
}
