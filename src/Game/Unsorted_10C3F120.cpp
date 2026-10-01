// Game/Unsorted_10C3F120.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C3F110
{
public:
    void FUN_10c3f120(int Index, float Value);

    char Unknown00[0x2C];
    int Unknown2C[1];
};

class Class_10C3FF10
{
public:
    void FUN_10c3ff10(int A);
};

class Class_10C41420 : public Class_10C3FF10
{
public:
    void FUN_10c472d0(int A);
};

Class_10C41420* FUN_10c47d90();

class Class_10E9B5C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10c3f140(bool A);

    char Unknown04[0x1C];
    bool Unknown20;
};

// FUNCTION: 0x10C3F120 ?FUN_10c3f120@Class_10C3F110@@QAEXHM@Z
void Class_10C3F110::FUN_10c3f120(int Index, float Value)
{
    Unknown2C[Index] = (int)(Value * 100.0f);
}

// FUNCTION: 0x10C3F140 ?FUN_10c3f140@Class_10E9B5C0@@UAEX_N@Z
void Class_10E9B5C0::FUN_10c3f140(bool A)
{
    FUN_10c47d90()->FUN_10c472d0(1);
    Unknown20 = A;
    FUN_10c47d90()->FUN_10c3ff10(-1);
}
