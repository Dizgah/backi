#include "backicore.h"


int main()
{
    BackiCore bk( "./dir2", "./dir1");

    bk.makeCpyList();
    bk.cpy();

    return 0;
}
