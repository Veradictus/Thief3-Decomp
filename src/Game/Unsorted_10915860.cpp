// Game/Unsorted_10915860.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <string.h>

class Class_10915B00
{
public:
    int FUN_10915b00(const char* Needle);

    char* Unknown00;
};

// FUNCTION: 0x10915B00 ?FUN_10915b00@Class_10915B00@@QAEHPBD@Z
int Class_10915B00::FUN_10915b00(const char* Needle)
{
    if (Unknown00)
    {
        char* Found = strstr(Unknown00, Needle);
        if (Found)
            return Found - Unknown00;
    }
    return -1;
}
