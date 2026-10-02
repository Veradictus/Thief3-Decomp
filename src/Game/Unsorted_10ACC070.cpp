// Game/Unsorted_10ACC070.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1098E330
{
public:
    int FUN_1098e330(int Id, int* Out);
};

extern float DAT_10e499a4;

class Class_10E7007C
{
public:
    virtual float FUN_10acc440(int A, int B, Class_1098E330* Obj);
};

class Class_10E70020;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(Class_10E70020* Obj);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E67938
{
public:
    ~Class_10E67938();

    virtual void FUN_10acb0c0(int Code, int A, int B, int C);
};

class Class_10E70020 : public Class_10E67938
{
public:
    ~Class_10E70020();

    virtual void FUN_10acb0c0(int Code, int A, int B, int C);
    void FUN_10acae80(int A, int B, int C);
};

// FUNCTION: 0x10ACC070 ??1Class_10E70020@@QAE@XZ
Class_10E70020::~Class_10E70020()
{
    DAT_10f46da0->Virtual2(this);
}

// FUNCTION: 0x10ACC440 ?FUN_10acc440@Class_10E7007C@@UAEMHHPAVClass_1098E330@@@Z
float Class_10E7007C::FUN_10acc440(int A, int B, Class_1098E330* Obj)
{
    if (Obj)
    {
        float Value = 0.0f;
        if (Obj->FUN_1098e330(0x100588, (int*)&Value))
            return Value;
    }
    return DAT_10e499a4;
}
