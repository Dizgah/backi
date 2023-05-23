#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <system_error>
#include <map>
#include <utility>
#include <chrono>
#include <string_view>

#include "backicore.h"


BackiCore::BackiCore()
{

}

BackiCore::BackiCore( std::string_view des, std::string_view src)
{
    desPath = des;
    srcPath = src;
}

ERR_TYPE BackiCore::makeCpyList()
{
    return makeCpyList(desPath, srcPath);
}

ERR_TYPE BackiCore::makeCpyList( std::string_view des, std::string_view src)
{
    files                               tmpBuf;
    std::filesystem::directory_entry    dir;


    try
    {
        //@TODO:It's better to implement a seperate validation method in the future!
        if (( des.empty()) || ( src.empty()) || ( des == src))
        {
            return ERR_TYPE::ERR_ADDRESS_INVALID;
        }

        dir.assign( des);
        if( !dir.exists())
        {
            std::cerr << "Error: " << des << " directory is not exist !" << std::endl;

            return ERR_TYPE::ERR_ADDRESS_INVALID;
        }
        else if( !dir.is_directory())
        {
            std::cerr << "Error: " << des << " directory is Invalid !" << std::endl;

            return ERR_TYPE::ERR_ADDRESS_INVALID;
        }

        dir.assign ( src);
        if( !dir.exists ())
        {
            std::cerr << "Error: " << des << " directory is not exist !" << std::endl;

            return ERR_TYPE::ERR_ADDRESS_INVALID;
        }
        else if( !dir.is_directory ())
        {
            std::cerr << "Error: " << des << " directory is Invalid !" << std::endl;

            return ERR_TYPE::ERR_ADDRESS_INVALID;
        }


        for( const std::filesystem::directory_entry& desElement : std::filesystem::recursive_directory_iterator(des))
        {
            std::cout << "des: " << desElement << " size:" << desElement.file_size() << " modifiedTime:" << std::format("{}", desElement.last_write_time()) << std::endl;
            tmpBuf.emplace( desElement.path().generic_string().erase(0, des.length()), 0);
        }

        for (const std::filesystem::directory_entry& srcElement : std::filesystem::recursive_directory_iterator(src))
        {
            std::cout << "src: " << srcElement << " size:" << srcElement.file_size() << " modifiedTime:" << std::format("{}", srcElement.last_write_time()) << std::endl;
            files::iterator itr = tmpBuf.find( srcElement.path().generic_string().erase(0, src.length()));


            if (itr != tmpBuf.end())//check for modification
            {
                std::filesystem::directory_entry dr( std::string( des) + std::string( itr->first));


                if (srcElement.last_write_time() != dr.last_write_time())
                {
                    diff.try_emplace(srcElement.path().generic_string(), static_cast<std::int64_t>(dr.file_size() - srcElement.file_size()));
                    std::cout << "inserting modified " << srcElement.path ().generic_string () << " Success !" << std::endl;
                }
            }
            else if (diff.try_emplace(srcElement.path().generic_string(), srcElement.file_size()).second)//it's a new file
            {
                std::cout << "inserting " << srcElement.path().generic_string() << " Success !" << std::endl;
            }
            else//inserting new file to list has been failed!
            {
                std::cout << "inserting " << srcElement.path().generic_string() << " Failed !" << std::endl;
            }
        }

        return ERR_TYPE::ERR_SUCCESS;
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
            << "code().category(): " << ex.code().category().name() << std::endl;
    }

    return ERR_TYPE::ERR_UNKNOWN;
}

ERR_TYPE BackiCore::cpy()
{
    try
    {
        if ( diff.empty())
        {
            return ERR_TYPE::ERR_NOTHING_TODO;
        }

        for ( auto itr : diff)
        {
            std::cout << "File:" << itr.first << " Size:" << itr.second << std::endl;
            std::string desAdr{ itr.first };

            desAdr.replace( 0, desPath.length(), desPath);

            if( !std::filesystem::copy_file( itr.first, desAdr, std::filesystem::copy_options::overwrite_existing))
            {
                std::cout << "Copy Failed! on File:" << itr.first << " Size:" << itr.second << std::endl;

                return ERR_TYPE::ERR_OPERATION_FAILED;
            }
        }

        return ERR_TYPE::ERR_SUCCESS;
    }
    catch( std::filesystem::filesystem_error const &ex)
    {

        std::cout
            << "\r\nException Occurred:" << std::endl
            << "what():  " << ex.what() << std::endl
            << "path1(): " << ex.path1() << std::endl
            << "path2(): " << ex.path2() << std::endl
            << "code().value():    " << ex.code().value() << std::endl
            << "code().message():  " << ex.code().message() << std::endl
            << "code().category(): " << ex.code().category().name() << std::endl;
    }

    return ERR_TYPE::ERR_UNKNOWN;
}

ERR_TYPE BackiCore::cpyAsync()
{
    try
    {
        if (diff.empty())
        {
            return ERR_TYPE::ERR_NOTHING_TODO;
        }

        for (auto itr : diff)
        {
            std::cout << "File:" << itr.first << " Size:" << itr.second << std::endl;
            std::string desAdr{ itr.first};

            desAdr.replace(0, desPath.length(), desPath);

            if (!std::filesystem::copy_file(itr.first, desAdr))
            {
                std::cout << "Copy Failed! on File:" << itr.first << " Size:" << itr.second << std::endl;

                return ERR_TYPE::ERR_OPERATION_FAILED;
            }
        }

        return ERR_TYPE::ERR_SUCCESS;
    }
    catch (std::filesystem::filesystem_error const& ex)
    {

        std::cout
            << "\r\nException Occurred:" << std::endl
            << "what():  " << ex.what() << std::endl
            << "path1(): " << ex.path1() << std::endl
            << "path2(): " << ex.path2() << std::endl
            << "code().value():    " << ex.code().value() << std::endl
            << "code().message():  " << ex.code().message() << std::endl
            << "code().category(): " << ex.code().category().name() << std::endl;
    }

    return ERR_TYPE::ERR_UNKNOWN;
}

BackiCore::~BackiCore()
{

}
