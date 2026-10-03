// Game/Unsorted_10B83850.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Allocator_10FFA700
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* A, int B, int C);
};

extern Allocator_10FFA700* DAT_10ffa700;

class Class_10943600;

class Class_10B83820
{
public:
    Class_10B83820() : Unknown00(0), Unknown04(0), Unknown08(0), Unknown08Flag(1) {}
    ~Class_10B83820()
    {
        if (!Unknown08Flag)
        {
            Allocator_10FFA700* Allocator = DAT_10ffa700;
            Allocator->Virtual5(Unknown00, Unknown08 * 16, 0x11);
        }
    }

    void* Unknown00;
    int Unknown04;
    unsigned Unknown08 : 31;
    unsigned Unknown08Flag : 1;
};

class Class_10B83DC0
{
public:
    int FUN_10b83dc0(Class_10943600* Out);
};

int FUN_10b83a30(Class_10B83DC0* Self, Class_10B83820* Out);

void FUN_10b83870(Class_10B83820* In, Class_10943600* Out);

class Class_10B83E50
{
public:
    int FUN_10b83e50(Class_10943600* Out);
};

int FUN_10b83b60(Class_10B83E50* Self, Class_10B83820* Out);

// FUNCTION: 0x10B83DC0 ?FUN_10b83dc0@Class_10B83DC0@@QAEHPAVClass_10943600@@@Z
int Class_10B83DC0::FUN_10b83dc0(Class_10943600* Out)
{
    Class_10B83820 Tmp;
    int Count = FUN_10b83a30(this, &Tmp);
    FUN_10b83870(&Tmp, Out);
    return Count;
}

// FUNCTION: 0x10B83E50 ?FUN_10b83e50@Class_10B83E50@@QAEHPAVClass_10943600@@@Z
int Class_10B83E50::FUN_10b83e50(Class_10943600* Out)
{
    Class_10B83820 Tmp;
    int Count = FUN_10b83b60(this, &Tmp);
    FUN_10b83870(&Tmp, Out);
    return Count;
}
