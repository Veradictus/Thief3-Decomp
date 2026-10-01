// Game/Unsorted_109E4860.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109E4860_Primary
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
};

class Class_10E5B7C4
{
public:
    virtual void FUN_109e4860(int p1, int p2, int p3);
};

class Class_109E4860 : public Class_109E4860_Primary, public Class_10E5B7C4
{
public:
    virtual void FUN_109e4860(int p1, int p2, int p3);
};

// FUNCTION: 0x109E4860 ?FUN_109e4860@Class_109E4860@@UAEXHHH@Z
void Class_109E4860::FUN_109e4860(int p1, int p2, int p3)
{
    if (p1 == 1)
        Virtual3();
}
