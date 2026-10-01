// Game/Unsorted_10C08F00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C09090
{
public:
    void FUN_10c09090(int p1);
};

class Class_10C09190
{
public:
    void FUN_10c09190(int p1);

    char Unknown00[4];
    Class_10C09090* Unknown04;
};

class Class_10c092f0
{
public:
    void FUN_10c092f0(int p1);
};

class Class_10c09410
{
public:
    void FUN_10c09410(int p1);

    char Unknown00[4];
    Class_10c092f0* Unknown04;
};

// FUNCTION: 0x10C09190 ?FUN_10c09190@Class_10C09190@@QAEXH@Z
void Class_10C09190::FUN_10c09190(int p1)
{
    if (Unknown04)
        Unknown04->FUN_10c09090(p1);
}

// FUNCTION: 0x10C09410 ?FUN_10c09410@Class_10c09410@@QAEXH@Z
void Class_10c09410::FUN_10c09410(int p1)
{
    if (Unknown04)
        Unknown04->FUN_10c092f0(p1);
}
