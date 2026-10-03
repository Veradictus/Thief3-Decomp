// Game/T3AIRegistration.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "T3AI/T3AIClasses.h"

// Ion Storm's memory manager (0x10905AA0): the registration allocates inside a
// scope of it (slots 8 and 9).
class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void Virtual8(int A, int B);
    virtual void Virtual9();
};

Class_10905A90_Member* FUN_10905aa0();

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

// FUNCTION: 0x10962F90 ?InitializePrivateStaticClassAT3AIPawnController@AT3AIPawnController@@SAXXZ
void AT3AIPawnController::InitializePrivateStaticClassAT3AIPawnController()
{
    if (Super::StaticClass() != PrivateStaticClass)
        PrivateStaticClass->SuperField = Super::StaticClass();
    else
        PrivateStaticClass->SuperField = NULL;
    PrivateStaticClass->ClassWithin = WithinClass::StaticClass();
    PrivateStaticClass->SetClass(UClass::StaticClass());
    if (GetInitialized() && PrivateStaticClass->GetClass() == PrivateStaticClass->StaticClass())
        PrivateStaticClass->Register();
}

// FUNCTION: 0x109630A0 ?InitializePrivateStaticClassAT3BehaviorModel@AT3BehaviorModel@@SAXXZ
void AT3BehaviorModel::InitializePrivateStaticClassAT3BehaviorModel()
{
    if (Super::StaticClass() != PrivateStaticClass)
        PrivateStaticClass->SuperField = Super::StaticClass();
    else
        PrivateStaticClass->SuperField = NULL;
    PrivateStaticClass->ClassWithin = WithinClass::StaticClass();
    PrivateStaticClass->SetClass(UClass::StaticClass());
    if (GetInitialized() && PrivateStaticClass->GetClass() == PrivateStaticClass->StaticClass())
        PrivateStaticClass->Register();
}

// FUNCTION: 0x109631B0 ?InitializePrivateStaticClassAT3SensoryModel@AT3SensoryModel@@SAXXZ
void AT3SensoryModel::InitializePrivateStaticClassAT3SensoryModel()
{
    if (Super::StaticClass() != PrivateStaticClass)
        PrivateStaticClass->SuperField = Super::StaticClass();
    else
        PrivateStaticClass->SuperField = NULL;
    PrivateStaticClass->ClassWithin = WithinClass::StaticClass();
    PrivateStaticClass->SetClass(UClass::StaticClass());
    if (GetInitialized() && PrivateStaticClass->GetClass() == PrivateStaticClass->StaticClass())
        PrivateStaticClass->Register();
}

// FUNCTION: 0x109632C0 ?InitializePrivateStaticClassAT3CombatModel@AT3CombatModel@@SAXXZ
void AT3CombatModel::InitializePrivateStaticClassAT3CombatModel()
{
    if (Super::StaticClass() != PrivateStaticClass)
        PrivateStaticClass->SuperField = Super::StaticClass();
    else
        PrivateStaticClass->SuperField = NULL;
    PrivateStaticClass->ClassWithin = WithinClass::StaticClass();
    PrivateStaticClass->SetClass(UClass::StaticClass());
    if (GetInitialized() && PrivateStaticClass->GetClass() == PrivateStaticClass->StaticClass())
        PrivateStaticClass->Register();
}

// FUNCTION: 0x109633D0 ?InitializePrivateStaticClassAT3MovementModel@AT3MovementModel@@SAXXZ
void AT3MovementModel::InitializePrivateStaticClassAT3MovementModel()
{
    if (Super::StaticClass() != PrivateStaticClass)
        PrivateStaticClass->SuperField = Super::StaticClass();
    else
        PrivateStaticClass->SuperField = NULL;
    PrivateStaticClass->ClassWithin = WithinClass::StaticClass();
    PrivateStaticClass->SetClass(UClass::StaticClass());
    if (GetInitialized() && PrivateStaticClass->GetClass() == PrivateStaticClass->StaticClass())
        PrivateStaticClass->Register();
}

// FUNCTION: 0x109634E0 ?InitializePrivateStaticClassAT3FactionModel@AT3FactionModel@@SAXXZ
void AT3FactionModel::InitializePrivateStaticClassAT3FactionModel()
{
    if (Super::StaticClass() != PrivateStaticClass)
        PrivateStaticClass->SuperField = Super::StaticClass();
    else
        PrivateStaticClass->SuperField = NULL;
    PrivateStaticClass->ClassWithin = WithinClass::StaticClass();
    PrivateStaticClass->SetClass(UClass::StaticClass());
    if (GetInitialized() && PrivateStaticClass->GetClass() == PrivateStaticClass->StaticClass())
        PrivateStaticClass->Register();
}

// FUNCTION: 0x10964540 ?GetPrivateStaticClassAT3AIPawnController@AT3AIPawnController@@SAPAVUClass@@PBD@Z
UClass* AT3AIPawnController::GetPrivateStaticClassAT3AIPawnController(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AT3AIPawnController), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AT3AIPawnController")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AT3AIPawnController::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10964610 ?GetPrivateStaticClassAT3BehaviorModel@AT3BehaviorModel@@SAPAVUClass@@PBD@Z
UClass* AT3BehaviorModel::GetPrivateStaticClassAT3BehaviorModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AT3BehaviorModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AT3BehaviorModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AT3BehaviorModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109646E0 ?GetPrivateStaticClassAT3SensoryModel@AT3SensoryModel@@SAPAVUClass@@PBD@Z
UClass* AT3SensoryModel::GetPrivateStaticClassAT3SensoryModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AT3SensoryModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AT3SensoryModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AT3SensoryModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109647B0 ?GetPrivateStaticClassAT3CombatModel@AT3CombatModel@@SAPAVUClass@@PBD@Z
UClass* AT3CombatModel::GetPrivateStaticClassAT3CombatModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AT3CombatModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AT3CombatModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AT3CombatModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10964880 ?GetPrivateStaticClassAT3MovementModel@AT3MovementModel@@SAPAVUClass@@PBD@Z
UClass* AT3MovementModel::GetPrivateStaticClassAT3MovementModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AT3MovementModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AT3MovementModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AT3MovementModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10964950 ?GetPrivateStaticClassAT3FactionModel@AT3FactionModel@@SAPAVUClass@@PBD@Z
UClass* AT3FactionModel::GetPrivateStaticClassAT3FactionModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AT3FactionModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AT3FactionModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AT3FactionModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}
