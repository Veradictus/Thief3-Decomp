// Game/Unsorted_10B40900.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e80418[];

class Class_10E81A60
{
public:
    Class_10E81A60();

    void** Unknown00;
};

class Class_10E80418 : public Class_10E81A60
{
public:
    Class_10E80418* FUN_10b40a00();
};

extern void* DAT_10e805d8[];

class Class_10E805D8 : public Class_10E81A60
{
public:
    Class_10E805D8* FUN_10b40a20();
};

// FUNCTION: 0x10B40A00 ?FUN_10b40a00@Class_10E80418@@QAEPAV1@XZ
Class_10E80418* Class_10E80418::FUN_10b40a00()
{
    this->Class_10E81A60::Class_10E81A60();
    Unknown00 = DAT_10e80418;
    return this;
}

// FUNCTION: 0x10B40A20 ?FUN_10b40a20@Class_10E805D8@@QAEPAV1@XZ
Class_10E805D8* Class_10E805D8::FUN_10b40a20()
{
    this->Class_10E81A60::Class_10E81A60();
    Unknown00 = DAT_10e805d8;
    return this;
}
