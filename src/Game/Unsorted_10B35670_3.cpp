// Game/Unsorted_10B35670_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7C2CC_Primary
{
public:
    virtual void Virtual0();
    virtual void Virtual1();

    char Unknown04[8];
};

class Class_10E7C2CC_Secondary
{
public:
    char Unknown00[4];
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E7C2CC_Secondary* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E7C2CC : public Class_10E7C2CC_Primary, public Class_10E7C2CC_Secondary
{
public:
    virtual void FUN_10b35770();
};

// Ion Storm's memory manager (0x10905AA0): the allocation happens inside a
// scope of it (slots 8 and 9).
class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(int A, int B);
    virtual void Virtual9();
};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e7c328[];

class Class_10EB766C
{
public:
    Class_10EB766C();

    void** VTable;
    int Unknown04;
    int Unknown08;
};

class Class_10E7C328 : public Class_10EB766C
{
public:
    Class_10E7C328()
    {
        VTable = DAT_10e7c328;
    }
};

class Class_10E79568
{
public:
    virtual Class_10E7C328* FUN_10b35b40();
};

extern void* DAT_10e7c344[];

class Class_10E7C344 : public Class_10EB766C
{
public:
    Class_10E7C344()
    {
        VTable = DAT_10e7c344;
    }
};

class Class_10E79570
{
public:
    virtual Class_10E7C344* FUN_10b35be0();
};

extern void* DAT_10e7c360[];

class Class_10E7C360 : public Class_10EB766C
{
public:
    Class_10E7C360()
    {
        VTable = DAT_10e7c360;
    }
};

class Class_10E7956C
{
public:
    virtual Class_10E7C360* FUN_10b35c80();
};

// FUNCTION: 0x10B35770 ?FUN_10b35770@Class_10E7C2CC@@UAEXXZ
void Class_10E7C2CC::FUN_10b35770()
{
    DAT_10f46da0->Virtual1(this, 0x4d, -1, -1);
}

// FUNCTION: 0x10B35B40 ?FUN_10b35b40@Class_10E79568@@UAEPAVClass_10E7C328@@XZ
Class_10E7C328* Class_10E79568::FUN_10b35b40()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E7C328* Result = new(0, 0, 0, 0, 0) Class_10E7C328;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B35BE0 ?FUN_10b35be0@Class_10E79570@@UAEPAVClass_10E7C344@@XZ
Class_10E7C344* Class_10E79570::FUN_10b35be0()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E7C344* Result = new(0, 0, 0, 0, 0) Class_10E7C344;
    FUN_10905aa0()->Virtual9();
    return Result;
}

// FUNCTION: 0x10B35C80 ?FUN_10b35c80@Class_10E7956C@@UAEPAVClass_10E7C360@@XZ
Class_10E7C360* Class_10E7956C::FUN_10b35c80()
{
    FUN_10905aa0()->Virtual8(0, 0);
    Class_10E7C360* Result = new(0, 0, 0, 0, 0) Class_10E7C360;
    FUN_10905aa0()->Virtual9();
    return Result;
}
