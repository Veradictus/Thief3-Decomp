// Game/Unsorted_10B6BE30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E871C8
{
public:
    virtual void Virtual0();
};

Class_10E871C8* FUN_10b70460();

extern void* DAT_10e86a28[];

class Class_10B787F0
{
public:
    void FUN_10b787f0();

    void* VTable;
};

class Class_10B6D990 : public Class_10B787F0
{
public:
    void FUN_10b6d990();
};

extern void* DAT_10e871d0[];

extern void* DAT_10e7edb8[];

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class Class_10E67BD8
{
public:
    Class_10E67BD8();

    void** Unknown00;
    char Unknown04[0x114];
    void** Unknown118;
    char Unknown11C[0x38];
};

class Class_10E871D0 : public Class_10E67BD8
{
public:
    Class_10E871D0* FUN_10b70430();

    FArray Unknown154;
};

class Class_10B78780
{
public:
    void FUN_10b78780();

    void** Unknown00;
    char Unknown04[0x18C];
};

class Class_10E86A28 : public Class_10B78780
{
public:
    Class_10E86A28* FUN_10b6d970();

    int Unknown190;
};

// FUNCTION: 0x10B6D970 ?FUN_10b6d970@Class_10E86A28@@QAEPAV1@XZ
Class_10E86A28* Class_10E86A28::FUN_10b6d970()
{
    FUN_10b78780();
    Unknown00 = DAT_10e86a28;
    Unknown190 = 0;
    return this;
}

// FUNCTION: 0x10B6D990 ?FUN_10b6d990@Class_10B6D990@@QAEXXZ
void Class_10B6D990::FUN_10b6d990()
{
    VTable = DAT_10e86a28;
    FUN_10b787f0();
}

// FUNCTION: 0x10B70430 ?FUN_10b70430@Class_10E871D0@@QAEPAV1@XZ
Class_10E871D0* Class_10E871D0::FUN_10b70430()
{
    this->Class_10E67BD8::Class_10E67BD8();
    Unknown00 = DAT_10e871d0;
    Unknown118 = DAT_10e7edb8;
    Unknown154.FArray::FArray();
    return this;
}

// FUNCTION: 0x10B70AB0 ?FUN_10b70ab0@@YAXXZ
void FUN_10b70ab0()
{
    FUN_10b70460()->Virtual0();
}
