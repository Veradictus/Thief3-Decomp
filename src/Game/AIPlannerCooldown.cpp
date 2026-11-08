// Game/AIPlannerCooldown.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/Class_10C7D570.h"
#include "Game/Class_10BBDB40.h"
#include "Game/Class_10BAA9D0.h"
#include "Game/Class_10BAA6B0_Param.h"
#include "Game/Class_10FF667C.h"
#include "Game/Class_10BB7F30.h"
#include "Game/cStateStack.h"

class Class_10BFB8C0 { public: float GetTime(int Index); };

class Class_10BFB8D0 { public: void FUN_10bfb8d0(int Index); };

class Class_10BFF460 {
public:
    bool FUN_10bff460();
    void* FUN_10bff2a0();
    float MeasureDistance();
};

extern Class_10FF667C* DAT_10ff667c;

extern float DAT_10eafbdc;

double GetTimeSeconds();

float GetFrameDeltaTime();

float appFrand();

class Class_10BBB410 {
public:
    void CancelCurrent();
    void FUN_10bbb8d0();
    Class_10BFF460* GetCurrent() {
        if (m_Current) {
            if (m_Current->FUN_10bff460() != 1)
                CancelCurrent();
        }
        return m_Current;
    }
    char Unknown00[8];
    Class_10C7D570* m_Owner;
    char Unknown0C[0x204];
    Class_10BFF460* m_Current;
    char Unknown214[0x44];
    float Accumulator;
    float Cooldown;
};

// FUNCTION: 0x10BBB8D0 ?FUN_10bbb8d0@Class_10BBB410@@QAEXXZ
void Class_10BBB410::FUN_10bbb8d0()
{
    float Threshold = m_Owner->FUN_10dbd510()->GetFloat(0x401004B2);
    if (Threshold != DAT_10eafbdc) {
        if (Cooldown > DAT_10eafbdc) {
            Cooldown = (double)Cooldown - GetFrameDeltaTime();
            if (Cooldown > DAT_10eafbdc)
                return;
            Accumulator = 0.0f;
        }
        if (Accumulator > Threshold) {
            Class_10BFF460* Current = GetCurrent();
            if (!Current)
                return;
            void* Target = Current->FUN_10bff2a0();
            if (!Target)
                return;
            if (!((Class_10BAA6B0_Param*)Target)->Virtual34())
                return;
            if (!((Class_10BAA9D0*)m_Owner)->FUN_10baa9d0(Target, 0.25f, false))
                return;
            float DistanceLimit = m_Owner->FUN_10dbd510()->GetFloat(0x40100851) * 16.0f;
            if (Current->MeasureDistance() > DistanceLimit)
                return;
            double Now = GetTimeSeconds();
            if (((Class_10BFB8C0*)DAT_10ff667c->Unknown28)->GetTime(11) < Now) {
                ((Class_10BFB8D0*)DAT_10ff667c->Unknown28)->FUN_10bfb8d0(11);
                float Min = m_Owner->FUN_10dbd510()->GetFloat(0x401004B0);
                float Max = m_Owner->FUN_10dbd510()->GetFloat(0x401004B1);
                Cooldown = Min + appFrand() * (Max - Min);
                Class_10B9CAC0* Stack = ((Class_10BB7F30*)this)->FUN_10bb7f30();
                if (Stack)
                    ((cStateStack*)Stack)->FUN_10b9e410();
            }
        }
        float DecayRate = m_Owner->FUN_10dbd510()->GetFloat(0x401004B3);
        Accumulator = (double)Accumulator - GetFrameDeltaTime() * DecayRate;
        Accumulator = DAT_10eafbdc >= Accumulator ? DAT_10eafbdc : Accumulator;
    }
}
