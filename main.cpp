#include "backicore.h"


int main(int argc, char* argv[])
{
    if( argc < 3)
    {
        std::cerr << "Error: insufficient argument has been provided !" << std::endl;
        return -1;
    }

    std::vector< std::string_view> arguments;

    for( size_t cntr = 1; cntr < argc; cntr++)
    {
        arguments.push_back(argv[cntr]);
    }

    std::filesystem::directory_entry dir;
    for( size_t cntr = 0; cntr < arguments.size(); cntr++)
    {
        dir.assign( arguments.at( cntr));
        //std::cout << arguments.at( cntr) << std::endl;
        if( !dir.exists())
        {
            std::cerr << "Error: " << arguments.at ( cntr ) << " directory is not exist !" << std::endl;

            return -1;
        }
        else if( !dir.is_directory())
        {
            std::cerr << "Error: " << arguments.at( cntr) << " directory is Invalid !" << std::endl;

            return -2;
        }
    }

    BackiCore bk ( arguments.at ( 0), arguments.at ( 1));
    //BackiCore bk ( "dir1", "dir2");

    bk.makeCpyList();
    bk.cpy();

    return 0;
}
