// Game/Unsorted_1099BA20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e475cc[];

extern int DAT_10f7b5bc;

int FUN_10b0f240(const char* Name);

void FUN_10b0f310();

inline void* operator new(unsigned int, void* Ptr)
{
    return Ptr;
}

class Class_10E559D0
{
public:
    Class_10E559D0();
};

class Class_10E55B48
{
public:
    Class_10E55B48();
};

class Class_10E55CC0
{
public:
    Class_10E55CC0();
};

// FUNCTION: 0x1099BBE0 ?FUN_1099bbe0@@YAHXZ
int FUN_1099bbe0()
{
    if (DAT_10f7b5bc == 0)
    {
        DAT_10f7b5bc = FUN_10b0f240(DAT_10e475cc);
        FUN_10b0f310();
    }
    return DAT_10f7b5bc;
}

// FUNCTION: 0x1099BC10 ?FUN_1099bc10@@YAXPAX@Z
void FUN_1099bc10(void* Memory)
{
    new (Memory) Class_10E559D0();
}

// FUNCTION: 0x1099BC20 ?FUN_1099bc20@@YAXPAX@Z
void FUN_1099bc20(void* Memory)
{
    new (Memory) Class_10E55B48();
}

// FUNCTION: 0x1099BC30 ?FUN_1099bc30@@YAXPAX@Z
void FUN_1099bc30(void* Memory)
{
    new (Memory) Class_10E55CC0();
}
