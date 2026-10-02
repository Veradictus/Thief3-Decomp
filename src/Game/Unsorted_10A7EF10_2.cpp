// Game/Unsorted_10A7EF10_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class ULinkDataObject
{
    DECLARE_CLASS(ULinkDataObject, UObject, 0x1, Core)
};

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* A);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0()
    {
        if (Unknown00)
        {
            char* Block = Unknown00 - 4;
            FUN_10905aa0()->Virtual5(Block);
            Unknown00 = 0;
        }
    }

    char* Unknown00;
};

bool FUN_1094c430(const Class_109081E0& A, const Class_109081E0& B) throw();

extern const char DAT_10e5da48[];

class Class_10E6BFBC
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
    virtual void Virtual8();
    virtual int FUN_10a7f420();

    int Unknown04;
    Class_109081E0 Unknown08;
};

// FUNCTION: 0x10A7EF10 ??$Cast@VULinkDataObject@@@@YAPAVULinkDataObject@@PAVUObject@@@Z
template ULinkDataObject* Cast<ULinkDataObject>(UObject* Src);

// FUNCTION: 0x10A7F420 ?FUN_10a7f420@Class_10E6BFBC@@UAEHXZ
int Class_10E6BFBC::FUN_10a7f420()
{
    return FUN_1094c430(Unknown08, Class_109081E0(DAT_10e5da48));
}
