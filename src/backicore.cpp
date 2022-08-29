#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <system_error>
#include <map>
#include <utility>
#include <chrono>

#include "backicore.h"


BackiCore::BackiCore()
{

}

BackiCore::BackiCore( const std::string &des, const std::string &src)
{
    desPath = des;
    srcPath = src;
}

ERR_TYPE BackiCore::cpy()
{
    return cpy(desPath, srcPath);
}

ERR_TYPE BackiCore::cpy( const std::string &des, std::string &src)
{
    files tmpBuf;


    try
    {
        if ((des.empty()) || (src.empty()) || (des == src))
        {
            return ERR_ADDRESS_INVALID;
        }

        for (const std::filesystem::directory_entry& desElement : std::filesystem::recursive_directory_iterator(des))
        {
            std::cout << "des: " << desElement << " size:" << desElement.file_size() << " modifiTime:" << std::format("{}", desElement.last_write_time()) << std::endl;
            tmpBuf.emplace(desElement.path().generic_string().erase(0, des.length()), 0);
        }

        for (const std::filesystem::directory_entry& srcElement : std::filesystem::recursive_directory_iterator(src))
        {
            std::cout << "src: " << srcElement << " size:" << srcElement.file_size() << " modifiTime:" << std::format("{}", srcElement.last_write_time()) << std::endl;
            files::iterator itr = tmpBuf.find(srcElement.path().generic_string().erase(0, src.length()));


            if (itr != tmpBuf.end())//check for modification
            {
                std::filesystem::directory_entry dr(des + itr->first);


                if (srcElement.last_write_time() != dr.last_write_time())
                {
                    diff.try_emplace(srcElement.path().generic_string(), static_cast<std::int64_t>(dr.file_size() - srcElement.file_size()));
                }

            }
            else if (diff.try_emplace(srcElement.path().generic_string(), srcElement.file_size()).second)//it's a new file
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
            << "\r\nException Occurred:" << '\n\n'
            << "what():  " << ex.what() << '\n'
            << "path1(): " << ex.path1() << '\n'
            << "path2(): " << ex.path2() << '\n'
            << "code().value():    " << ex.code().value() << '\n'
            << "code().message():  " << ex.code().message() << '\n'
            << "code().category(): " << ex.code().category().name() << '\n';
    }

    return ERR_UNKNOWN;
}

BackiCore::~BackiCore()
{

}
