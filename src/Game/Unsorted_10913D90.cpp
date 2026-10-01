// Game/Unsorted_10913D90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780;

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);
};

class Class_10914380
{
public:
    bool FUN_10914380(const Class_1090A780& A, const Class_1090A780& B, Class_109081E0& Out, void* Filter);
    Class_109081E0* FUN_10913fc0(const Class_1090A780& A, const Class_1090A780& B, void* Filter, void** Index);
};

// FUNCTION: 0x10914380 ?FUN_10914380@Class_10914380@@QAE_NABVClass_1090A780@@0AAVClass_109081E0@@PAX@Z
bool Class_10914380::FUN_10914380(const Class_1090A780& A, const Class_1090A780& B, Class_109081E0& Out, void* Filter)
{
    Class_109081E0* Found = FUN_10913fc0(A, B, Filter, 0);
    if (!Found)
        return false;
    Out = *Found;
    return true;
}
