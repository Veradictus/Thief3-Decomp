// Game/LockPickControllerDestructor.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/Class_10905A90_Member.h"
#include "Game/cIntArray.h"
#include "Game/Class_10943600.h"
#include "Game/Class_10C56E40.h"

class Class_10E6CE28;

Class_10905A90_Member* GetAllocator();

// The native base destructor restores its vtable; its 16-byte extent is
// independently fixed by the first owned array at offset 0x10.
class Class_10B3ACD0
{
public:
    ~Class_10B3ACD0();
    char Storage[16];
};

class LockPickController : public Class_10B3ACD0
{
public:
    ~LockPickController();
    Class_10943600 Positions;
    char Unknown1C[0x34];
    cIntArray Values;
    Class_10C56E40 References[4];
};

T3_CHECK_SIZE(LockPickController, 0x6C);

// FUNCTION: 0x10B3EF20 ??1LockPickController@@QAE@XZ
LockPickController::~LockPickController()
{
}
