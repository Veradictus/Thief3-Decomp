// Game/StringBufferAllocate.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <string.h>
#include "Game/Class_10905A90_Member.h"

Class_10905A90_Member* GetAllocator();

class cString
{
public:
    void FUN_10907870(int Length, bool Zero);
    char* Unknown00;
};

// FUNCTION: 0x10907870 ?FUN_10907870@cString@@QAEXH_N@Z
void cString::FUN_10907870(int Length, bool Zero)
{
    if (Unknown00)
    {
        char* Block = Unknown00 - 4;
        GetAllocator()->Virtual5(Block);
        Unknown00 = 0;
    }
    if (Length)
    {
        char* Block = (char*)GetAllocator()->Virtual2(Length + 5, 0, 0, 0, 0);
        Unknown00 = Block + 4;
        *(int*)Block = Length;
        if (Zero)
            memset(Unknown00, 0, Length + 1);
    }
}
