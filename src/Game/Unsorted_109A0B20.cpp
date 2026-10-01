// Game/Unsorted_109A0B20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e57440[];

class Class_10E70A50
{
public:
    Class_10E70A50();

    void** Unknown00;
    char Unknown04[0x28];
};

class Class_10E55E78 : public Class_10E70A50
{
public:
    Class_10E55E78();
};

class Class_10E57440 : public Class_10E55E78
{
public:
    Class_10E57440* FUN_109a0b90();
};

extern void* DAT_10e574c8[];

class Class_10E574C8 : public Class_10E55E78
{
public:
    Class_10E574C8* FUN_109a0c20();
};

extern void* DAT_10e57550[];

class Class_10E57550 : public Class_10E55E78
{
public:
    Class_10E57550* FUN_109a0cb0();
};

extern void* DAT_10e575d8[];

class Class_10E575D8 : public Class_10E55E78
{
public:
    Class_10E575D8* FUN_109a0d40();
};

// FUNCTION: 0x109A0B90 ?FUN_109a0b90@Class_10E57440@@QAEPAV1@XZ
Class_10E57440* Class_10E57440::FUN_109a0b90()
{
    this->Class_10E55E78::Class_10E55E78();
    Unknown00 = DAT_10e57440;
    return this;
}

// FUNCTION: 0x109A0C20 ?FUN_109a0c20@Class_10E574C8@@QAEPAV1@XZ
Class_10E574C8* Class_10E574C8::FUN_109a0c20()
{
    this->Class_10E55E78::Class_10E55E78();
    Unknown00 = DAT_10e574c8;
    return this;
}

// FUNCTION: 0x109A0CB0 ?FUN_109a0cb0@Class_10E57550@@QAEPAV1@XZ
Class_10E57550* Class_10E57550::FUN_109a0cb0()
{
    this->Class_10E55E78::Class_10E55E78();
    Unknown00 = DAT_10e57550;
    return this;
}

// FUNCTION: 0x109A0D40 ?FUN_109a0d40@Class_10E575D8@@QAEPAV1@XZ
Class_10E575D8* Class_10E575D8::FUN_109a0d40()
{
    this->Class_10E55E78::Class_10E55E78();
    Unknown00 = DAT_10e575d8;
    return this;
}
