// Game/Class_10E93E48.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e93e48[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
};

class Class_10E93E48 : public Class_10E90D70
{
public:
    Class_10E93E48* FUN_10bd9780(int A, int B);
};

// FUNCTION: 0x10BD9780 ?FUN_10bd9780@Class_10E93E48@@QAEPAV1@HH@Z
Class_10E93E48* Class_10E93E48::FUN_10bd9780(int A, int B)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown00 = DAT_10e93e48;
    return this;
}
