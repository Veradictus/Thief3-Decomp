// Game/Unsorted_10A31210.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0& operator=(const Class_109081E0& Other);
};

bool FUN_10d39910(const Class_109081E0& A);

// FUNCTION: 0x10A315F0 ?FUN_10a315f0@@YG_NABVClass_109081E0@@AAV1@@Z
bool __stdcall FUN_10a315f0(const Class_109081E0& A, Class_109081E0& B)
{
    if (!FUN_10d39910(A))
    {
        B = A;
        return false;
    }
    return true;
}
