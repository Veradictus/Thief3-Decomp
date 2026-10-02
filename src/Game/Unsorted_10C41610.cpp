// Game/Unsorted_10C41610.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <map>

class Class_10C63AD0
{
public:
    void FUN_10c63ad0();
};

class Class_10C41420
{
public:
    virtual void FUN_10c423d0(int A, int B, int C, int D);

    void FUN_10c41b10();

    char Unknown04[0x3C];
    std::map<int, Class_10C63AD0*> Unknown40;
};

// FUNCTION: 0x10C41B10 ?FUN_10c41b10@Class_10C41420@@QAEXXZ
void Class_10C41420::FUN_10c41b10()
{
    for (std::map<int, Class_10C63AD0*>::iterator It = Unknown40.begin(); It != Unknown40.end(); ++It)
        It->second->FUN_10c63ad0();
}
