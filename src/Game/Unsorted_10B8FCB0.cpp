// Game/Unsorted_10B8FCB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e8984c[];

class Class_10E8984C
{
public:
    Class_10E8984C();

    void** Unknown00;
    int Unknown04;
};

extern void* DAT_10e89a10[];

class Class_10E89AA0
{
public:
    Class_10E89AA0(int A, int B, int C);

    void** Unknown00;
};

class Class_10E89A10 : public Class_10E89AA0
{
public:
    Class_10E89A10* FUN_10b92660(int A, int B);
};

// FUNCTION: 0x10B90320 ??0Class_10E8984C@@QAE@XZ
Class_10E8984C::Class_10E8984C()
{
    Unknown00 = DAT_10e8984c;
    Unknown04 = 0;
}

// FUNCTION: 0x10B92660 ?FUN_10b92660@Class_10E89A10@@QAEPAV1@HH@Z
Class_10E89A10* Class_10E89A10::FUN_10b92660(int A, int B)
{
    this->Class_10E89AA0::Class_10E89AA0(0, A, B);
    Unknown00 = DAT_10e89a10;
    return this;
}
