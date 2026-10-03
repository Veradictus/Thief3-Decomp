// Game/Unsorted_10B61CA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B61CA0
{
public:
    int FUN_10b61ca0();

    char Unknown00[0xC4];
    int UnknownC4;
    char UnknownC8[0xC8];
    int Unknown190;
    int Unknown194;
    int* Unknown198;
};

class Class_10BFBD70
{
public:
    int Unknown00;
    int Unknown04;
    void** Unknown08;
};

class Class_10B61CE0
{
public:
    int FUN_10b61ce0();

    char Unknown00[0xC4];
    void* UnknownC4;
    char UnknownC8[0xD4];
    Class_10BFBD70 Unknown19C;
};

// FUNCTION: 0x10B61CA0 ?FUN_10b61ca0@Class_10B61CA0@@QAEHXZ
int Class_10B61CA0::FUN_10b61ca0()
{
    int Result = -1;
    int i = 0;
    bool Done = false;
    while (!Done)
    {
        if (i >= Unknown190)
        {
            Result = -1;
            Done = true;
        }
        else if (Unknown198[i] == UnknownC4)
        {
            Result = i;
            Done = true;
        }
        i++;
    }
    return Result;
}

// FUNCTION: 0x10B61CE0 ?FUN_10b61ce0@Class_10B61CE0@@QAEHXZ
int Class_10B61CE0::FUN_10b61ce0()
{
    int Index = -1;
    int i = 0;
    bool Found = false;
    while (!Found)
    {
        if (i >= Unknown19C.Unknown00)
        {
            Index = -1;
            Found = true;
        }
        else if (Unknown19C.Unknown08[i] == UnknownC4)
        {
            Index = i;
            Found = true;
        }
        i++;
    }
    return Index;
}
