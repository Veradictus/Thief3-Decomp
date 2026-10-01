// Game/Unsorted_10B93D30_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e8b1a8[];

class Class_10E70A50
{
public:
    void** Unknown00;
};

class AActor : public Class_10E70A50
{
};

class AMarker : public AActor
{
};

class AAIPathPoint : public AMarker
{
public:
    AAIPathPoint();
};

class Class_10E8B1A8 : public AAIPathPoint
{
public:
    Class_10E8B1A8* FUN_10b93e30();
};

extern void* DAT_10e8b330[];

class Class_10E8B330 : public AAIPathPoint
{
public:
    Class_10E8B330* FUN_10b93e50();
};

extern void* DAT_10e8b4b8[];

class Class_10E8B4B8 : public AAIPathPoint
{
public:
    Class_10E8B4B8* FUN_10b93ef0();
};

enum EInternal { EC_Internal };

inline void* operator new(unsigned int, EInternal* Mem)
{
    return Mem;
}

class AAIPawnController
{
public:
    AAIPawnController();
};

class AAddAIPoint
{
public:
    AAddAIPoint();
};

class AChangeDirectionPoint
{
public:
    AChangeDirectionPoint();
};

class AFormationPoint
{
public:
    AFormationPoint();
};

class AFormationPointAbsolute
{
public:
    AFormationPointAbsolute();
};

class AHeadTurnPoint
{
public:
    AHeadTurnPoint();
};

class ALookPoint
{
public:
    ALookPoint();
};

class APlayAnimPoint
{
public:
    APlayAnimPoint();
};

class APlayBarkPoint
{
public:
    APlayBarkPoint();
};

class AAICombatModel
{
public:
    AAICombatModel();
};

class AAIFactionModel
{
public:
    AAIFactionModel();
};

class AAIMovementModel
{
public:
    AAIMovementModel();
};

class AAISensoryModel
{
public:
    AAISensoryModel();
};

extern void* DAT_10e8bca0[];

class Class_10E67508
{
public:
    Class_10E67508* FUN_10a503e0();

    void** Unknown00;
};

class Class_10E8BCA0 : public Class_10E67508
{
public:
    Class_10E8BCA0* FUN_10b97660();
};

// FUNCTION: 0x10B93E30 ?FUN_10b93e30@Class_10E8B1A8@@QAEPAV1@XZ
Class_10E8B1A8* Class_10E8B1A8::FUN_10b93e30()
{
    this->AAIPathPoint::AAIPathPoint();
    Unknown00 = DAT_10e8b1a8;
    return this;
}

// FUNCTION: 0x10B93E50 ?FUN_10b93e50@Class_10E8B330@@QAEPAV1@XZ
Class_10E8B330* Class_10E8B330::FUN_10b93e50()
{
    this->AAIPathPoint::AAIPathPoint();
    Unknown00 = DAT_10e8b330;
    return this;
}

// FUNCTION: 0x10B93EF0 ?FUN_10b93ef0@Class_10E8B4B8@@QAEPAV1@XZ
Class_10E8B4B8* Class_10E8B4B8::FUN_10b93ef0()
{
    this->AAIPathPoint::AAIPathPoint();
    Unknown00 = DAT_10e8b4b8;
    return this;
}

// FUNCTION: 0x10B95150 ?FUN_10b95150@@YAXPAX@Z
void FUN_10b95150(void* Memory)
{
    new ((EInternal*)Memory) AAIPawnController();
}

// FUNCTION: 0x10B951A0 ?FUN_10b951a0@@YAXPAX@Z
void FUN_10b951a0(void* Memory)
{
    new ((EInternal*)Memory) AAddAIPoint();
}

// FUNCTION: 0x10B951B0 ?FUN_10b951b0@@YAXPAX@Z
void FUN_10b951b0(void* Memory)
{
    new ((EInternal*)Memory) AChangeDirectionPoint();
}

// FUNCTION: 0x10B951C0 ?FUN_10b951c0@@YAXPAX@Z
void FUN_10b951c0(void* Memory)
{
    new ((EInternal*)Memory) AFormationPoint();
}

// FUNCTION: 0x10B951D0 ?FUN_10b951d0@@YAXPAX@Z
void FUN_10b951d0(void* Memory)
{
    new ((EInternal*)Memory) AFormationPointAbsolute();
}

// FUNCTION: 0x10B951E0 ?FUN_10b951e0@@YAXPAX@Z
void FUN_10b951e0(void* Memory)
{
    new ((EInternal*)Memory) AHeadTurnPoint();
}

// FUNCTION: 0x10B951F0 ?FUN_10b951f0@@YAXPAX@Z
void FUN_10b951f0(void* Memory)
{
    new ((EInternal*)Memory) ALookPoint();
}

// FUNCTION: 0x10B95200 ?FUN_10b95200@@YAXPAX@Z
void FUN_10b95200(void* Memory)
{
    new ((EInternal*)Memory) APlayAnimPoint();
}

// FUNCTION: 0x10B95210 ?FUN_10b95210@@YAXPAX@Z
void FUN_10b95210(void* Memory)
{
    new ((EInternal*)Memory) APlayBarkPoint();
}

// FUNCTION: 0x10B952A0 ?FUN_10b952a0@@YAXPAX@Z
void FUN_10b952a0(void* Memory)
{
    new ((EInternal*)Memory) AAICombatModel();
}

// FUNCTION: 0x10B952B0 ?FUN_10b952b0@@YAXPAX@Z
void FUN_10b952b0(void* Memory)
{
    new ((EInternal*)Memory) AAIFactionModel();
}

// FUNCTION: 0x10B952C0 ?FUN_10b952c0@@YAXPAX@Z
void FUN_10b952c0(void* Memory)
{
    new ((EInternal*)Memory) AAIMovementModel();
}

// FUNCTION: 0x10B952D0 ?FUN_10b952d0@@YAXPAX@Z
void FUN_10b952d0(void* Memory)
{
    new ((EInternal*)Memory) AAISensoryModel();
}

// FUNCTION: 0x10B97660 ?FUN_10b97660@Class_10E8BCA0@@QAEPAV1@XZ
Class_10E8BCA0* Class_10E8BCA0::FUN_10b97660()
{
    FUN_10a503e0();
    Unknown00 = DAT_10e8bca0;
    return this;
}
