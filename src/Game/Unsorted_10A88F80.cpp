// Game/Unsorted_10A88F80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AAE300
{
public:
    void FUN_10aae300(int A);
};

class Class_10AAE310 : public Class_10AAE300
{
public:
    void FUN_10aae310(int A);
};

class Class_10E6C484
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void FUN_10a89030(int A, int B);

    char Unknown04[0x674];
    Class_10AAE310* Unknown678;
};

// FUNCTION: 0x10A89030 ?FUN_10a89030@Class_10E6C484@@UAEXHH@Z
void Class_10E6C484::FUN_10a89030(int A, int B)
{
    Unknown678->FUN_10aae310(A);
    Unknown678->FUN_10aae300(B);
}
