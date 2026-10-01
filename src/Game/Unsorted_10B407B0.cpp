// Game/Unsorted_10B407B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e80088[];

class Class_10E7B360
{
public:
    Class_10E7B360();

    void** Unknown00;
};

class Class_10E80088 : public Class_10E7B360
{
public:
    Class_10E80088* FUN_10b407b0();
};

extern void* DAT_10e80250[];

class Class_10E80250 : public Class_10E7B360
{
public:
    Class_10E80250* FUN_10b407d0();
};

// FUNCTION: 0x10B407B0 ?FUN_10b407b0@Class_10E80088@@QAEPAV1@XZ
Class_10E80088* Class_10E80088::FUN_10b407b0()
{
    this->Class_10E7B360::Class_10E7B360();
    Unknown00 = DAT_10e80088;
    return this;
}

// FUNCTION: 0x10B407D0 ?FUN_10b407d0@Class_10E80250@@QAEPAV1@XZ
Class_10E80250* Class_10E80250::FUN_10b407d0()
{
    this->Class_10E7B360::Class_10E7B360();
    Unknown00 = DAT_10e80250;
    return this;
}
