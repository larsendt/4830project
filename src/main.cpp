#include "IEngine.h"

int main(int argc, char** argv)
{
    IEngine* ge = new IEngine(argc, argv);
    int retval = ge->begin();
    delete ge;
    return retval;
}
