#include "backicore.h"


int main(int argc, char* argv[])
{
    if( argc < 2)
    {
        std::cerr << "Error: insufficient argument has been provided!";
//        return -1;
    }

    std::vector< std::string_view> arguments;

    for( size_t cntr = 0; cntr < argc; cntr++)
    {
         arguments.push_back(argv[cntr]);
    }

    for (size_t cntr = 0; cntr < arguments.size(); cntr++)
    {
        std::cout << arguments.at(cntr) << std::endl;
    }

//    BackiCore bk("./dir2", "./dir1");
    BackiCore bk( arguments.at( 0), arguments.at( 1));

    bk.makeCpyList();
    bk.cpy();

    return 0;
}
