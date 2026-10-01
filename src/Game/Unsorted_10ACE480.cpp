// Game/Unsorted_10ACE480.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e701c8[];

class Class_10E67938
{
public:
    Class_10E67938();

    void** Unknown00;
};

class Class_10E701C8 : public Class_10E67938
{
public:
    Class_10E701C8* FUN_10ace480();
};

// FUNCTION: 0x10ACE480 ?FUN_10ace480@Class_10E701C8@@QAEPAV1@XZ
Class_10E701C8* Class_10E701C8::FUN_10ace480()
{
    this->Class_10E67938::Class_10E67938();
    Unknown00 = DAT_10e701c8;
    return this;
}
