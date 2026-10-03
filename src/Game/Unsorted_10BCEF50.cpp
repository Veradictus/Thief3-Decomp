// Game/Unsorted_10BCEF50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA82D0
{
public:
    int FUN_10aa82d0();
};

class Class_10BF7F90 : public Class_10AA82D0
{
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    Class_10BF7F90* FUN_10bc4160();
};

class Class_10BCFE10 : public Class_10BC4160
{
public:
    void FUN_10bcfbd0();
};

class Class_10E92C38 : public Class_10BCFE10
{
public:
    virtual void Virtual1();
    virtual void FUN_10bcfdd0();

    void FUN_10bcf680();

    char Unknown04[0x46];
    bool Unknown4A;
    bool Unknown4B;
};

// FUNCTION: 0x10BCFDD0 ?FUN_10bcfdd0@Class_10E92C38@@UAEXXZ
void Class_10E92C38::FUN_10bcfdd0()
{
    if (!Unknown4B)
        FUN_10bcfbd0();
    Class_10BF7F90* Info = FUN_10bc4160();
    if ((!Info || !Info->FUN_10aa82d0()) && !Unknown4A)
        FUN_10bcf680();
}
