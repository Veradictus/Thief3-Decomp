// Game/Unsorted_10B642C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e84508[];

class Class_10E87B68
{
public:
    Class_10E87B68();

    void** Unknown00;
};

class Class_10E84508 : public Class_10E87B68
{
public:
    Class_10E84508* FUN_10b64410();
};

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

class Class_10B642C0
{
public:
    Class_109081E0 FUN_10b642c0();
};

// FUNCTION: 0x10B642C0 ?FUN_10b642c0@Class_10B642C0@@QAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10B642C0::FUN_10b642c0()
{
    Class_109081E0 Local = FUN_1090a660("<string=T_TabScreenTitleLoadGameTitle>");
    return Local;
}

// FUNCTION: 0x10B64410 ?FUN_10b64410@Class_10E84508@@QAEPAV1@XZ
Class_10E84508* Class_10E84508::FUN_10b64410()
{
    this->Class_10E87B68::Class_10E87B68();
    Unknown00 = DAT_10e84508;
    return this;
}
