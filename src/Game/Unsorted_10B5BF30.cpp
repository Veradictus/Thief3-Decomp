// Game/Unsorted_10B5BF30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int* Obj);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);

    char* Unknown00;
};

class Class_109081E0 : public Class_1090A780
{
public:
    ~Class_109081E0()
    {
        if (Unknown00)
        {
            int* Obj = (int*)Unknown00 - 1;
            FUN_10905aa0()->Virtual5(Obj);
        }
    }
};

Class_109081E0 FUN_1090a660(const char* Text);

class Class_10B5C2A0
{
public:
    Class_109081E0 FUN_10b5c2a0();
};

// FUNCTION: 0x10B5C2A0 ?FUN_10b5c2a0@Class_10B5C2A0@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10B5C2A0::FUN_10b5c2a0()
{
    Class_109081E0 Local = FUN_1090a660("<string=T_TabScreenMissionFailedTitle>");
    return Local;
}
