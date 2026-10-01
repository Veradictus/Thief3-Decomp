// Game/Unsorted_10A2FC10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

bool FUN_1090f010(const int* A, const int* B);

class Class_10E66390
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a2fcb0(Class_10E66390* A);

    int Unknown04;
};

// FUNCTION: 0x10A2FCB0 ?FUN_10a2fcb0@Class_10E66390@@UAEHPAV1@@Z
int Class_10E66390::FUN_10a2fcb0(Class_10E66390* A)
{
    return FUN_1090f010(&A->Unknown04, &Unknown04);
}
