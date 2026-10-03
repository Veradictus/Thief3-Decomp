// Game/Unsorted_10915860.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <string.h>

class Class_10915B00
{
public:
    int FUN_10915b00(const char* Needle);

    char* Unknown00;
};

class Class_109081E0
{
public:
    Class_109081E0() : Unknown00(0) {}
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10E499A8
{
public:
    virtual void Virtual0();
    virtual int FUN_1090f3c0(int* A, int* B);
};

class Class_10914D80
{
public:
    Class_10914D80() : Unknown00(0), Unknown04(0), Unknown0C(0), Unknown10(false), Unknown14(0) {}

    void FUN_10914e60(int Size);

    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    bool Unknown10;
    void* Unknown14;
    Class_10E499A8 Unknown18;
};

class Class_10E495F8
{
public:
    Class_10E495F8();

    virtual ~Class_10E495F8();

    Class_109081E0 Unknown04;
    char Unknown08;
    bool Unknown09;
    Class_10914D80 Unknown0C;
};

// FUNCTION: 0x10915860 ??0Class_10E495F8@@QAE@XZ
Class_10E495F8::Class_10E495F8()
    : Unknown09(false)
{
    Unknown0C.FUN_10914e60(0x40);
}

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
