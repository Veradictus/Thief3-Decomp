// Game/ScriptControllerCommand.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"
#include "Game/cIntArray.h"
#include "Game/Class_10A7F5A0.h"
#include "Game/Class_10A9DBE0_Param2.h"
#include "Game/Class_10A9DBE0_Param3.h"

class UObject;

class AAIPawnController;

template<> AAIPawnController* Cast<AAIPawnController>(UObject* Object);

class Class_10B9C180 { public: bool FUN_10b9c180(); };

class Class_10BB3190_Result {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual int Virtual34();
    char Unknown04[0xBC];
    UObject* UnknownC0;
};

Class_10BB3190_Result* FUN_10983cf0(int A);

class Class_10BB3300 {
public:
    int FUN_10bb3300(int A, Class_10A9DBE0_Param2* B, Class_10A9DBE0_Param3* C);
};

// FUNCTION: 0x10BB3300 ?FUN_10bb3300@Class_10BB3300@@QAEHHPAVClass_10A9DBE0_Param2@@PAVClass_10A9DBE0_Param3@@@Z
int Class_10BB3300::FUN_10bb3300(int A, Class_10A9DBE0_Param2* B, Class_10A9DBE0_Param3* C)
{
    if (B && B->Virtual8() && C && C->Virtual3() >= 1) {
        cIntArray Found = C->Virtual4(0)->FUN_10a7f5a0(B->Virtual8(), 0);
        for (int i = 0; i < Found.Count; ++i) {
            Class_10BB3190_Result* Item = FUN_10983cf0(Found.Data[i]);
            if (Item && !Item->Virtual34()) {
                UObject* Owner = Item->UnknownC0;
                if (Owner) {
                    AAIPawnController* Controller = Cast<AAIPawnController>(Owner);
                    if (Controller)
                        ((Class_10B9C180*)Controller)->FUN_10b9c180();
                }
            }
        }
        return 1;
    }
    return 0;
}
