#ifndef NSUTIL
#define NSUTIL
#include<stdlib.h>
#include<time.h>
namespace nsUtil
{
    unsigned Random (unsigned Min, unsigned Max)//[Min, Max[
    {
        srand (time (NULL) - rand());
        return rand () % Max + Min;
    }// Random ()
}
#endif // NSUTIL

