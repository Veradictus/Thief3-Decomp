// Game/Unsorted_10BBFF10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BBFF10
{
public:
    void FUN_10bbff10();
};

class Class_10BC0F30
{
public:
    void FUN_10bc0f30();

    Class_10BBFF10* Unknown00;
};

// FUNCTION: 0x10BC0F30 ?FUN_10bc0f30@Class_10BC0F30@@QAEXXZ
void Class_10BC0F30::FUN_10bc0f30()
{
    Class_10BBFF10* Object = Unknown00;
    if (Object)
    {
        Object->FUN_10bbff10();
        ::operator delete(Object);
    }
}
