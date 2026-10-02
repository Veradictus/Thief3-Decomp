// Game/Unsorted_10AB5AE0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10AB5AE0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
};

class Class_10AB5AE0
{
public:
    Class_10AB5AE0* FUN_10ab5ae0(Class_10AB5AE0* Other);

    Object_10AB5AE0* Unknown00;
};

// FUNCTION: 0x10AB5AE0 ?FUN_10ab5ae0@Class_10AB5AE0@@QAEPAV1@PAV1@@Z
Class_10AB5AE0* Class_10AB5AE0::FUN_10ab5ae0(Class_10AB5AE0* Other)
{
    Unknown00 = Other->Unknown00;
    if (Unknown00)
        Unknown00->Virtual1();
    return this;
}
