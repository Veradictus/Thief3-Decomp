// Game/Class_10B59E00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e822b0[];

class Class_10A66190
{
public:
    void FUN_10a66190();

    void* VTable;
};

class Class_10B59E00 : public Class_10A66190
{
public:
    void FUN_10b59e00();
};

// FUNCTION: 0x10B59E00 ?FUN_10b59e00@Class_10B59E00@@QAEXXZ
void Class_10B59E00::FUN_10b59e00()
{
    VTable = DAT_10e822b0;
    FUN_10a66190();
}
