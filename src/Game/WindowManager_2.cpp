// Game/WindowManager_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's string (0x109081E0): a char pointer to a block allocated 4 bytes before it.
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

extern const char DAT_10e79030[];

class Class_109E6D60
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4(int Window);

    bool FUN_109e6d60(int p1);
};

class WindowManager : public Class_109E6D60
{
public:
    int FUN_109e5960(const Class_109081E0& Name);
    bool FUN_10b158b0();
};

// FUNCTION: 0x10B158B0 ?FUN_10b158b0@WindowManager@@QAE_NXZ
bool WindowManager::FUN_10b158b0()
{
    int Window;
    {
        Class_109081E0 Name(DAT_10e79030);
        Window = FUN_109e5960(Name);
    }
    if (Window && !FUN_109e6d60(Window))
    {
        Virtual4(Window);
        return true;
    }
    return false;
}
