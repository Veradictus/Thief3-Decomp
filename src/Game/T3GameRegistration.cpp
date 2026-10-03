// Game/T3GameRegistration.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "T3Game/T3GameClasses.h"

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

// FUNCTION: 0x10AB4020 ??_GASpellProjectile@@UAEPAXI@Z
// Compiler-generated: emitted with the class's vtable by 0x10AB4050's definition in this unit.

// FUNCTION: 0x10AB4050 ??1ASpellProjectile@@UAE@XZ
ASpellProjectile::~ASpellProjectile()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10AB40A0 ?GetPrivateStaticClassUT3GameRegistrar@UT3GameRegistrar@@SAPAVUClass@@PBD@Z
UClass* UT3GameRegistrar::GetPrivateStaticClassUT3GameRegistrar(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UT3GameRegistrar), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("UT3GameRegistrar")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&UT3GameRegistrar::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10AB4170 ?InitializePrivateStaticClassUT3GameRegistrar@UT3GameRegistrar@@SAXXZ
void UT3GameRegistrar::InitializePrivateStaticClassUT3GameRegistrar()
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

// FUNCTION: 0x10AB4280 ?InitializePrivateStaticClassULockLinkDataObject@ULockLinkDataObject@@SAXXZ
void ULockLinkDataObject::InitializePrivateStaticClassULockLinkDataObject()
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

// FUNCTION: 0x10AB4390 ?InitializePrivateStaticClassUSpawnPoolLinkDataObject@USpawnPoolLinkDataObject@@SAXXZ
void USpawnPoolLinkDataObject::InitializePrivateStaticClassUSpawnPoolLinkDataObject()
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

// FUNCTION: 0x10AB44A0 ?InitializePrivateStaticClassULockTickLinkDataObject@ULockTickLinkDataObject@@SAXXZ
void ULockTickLinkDataObject::InitializePrivateStaticClassULockTickLinkDataObject()
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

// FUNCTION: 0x10AB45B0 ?InitializePrivateStaticClassUInventorySwitchLinkDataObject@UInventorySwitchLinkDataObject@@SAXXZ
void UInventorySwitchLinkDataObject::InitializePrivateStaticClassUInventorySwitchLinkDataObject()
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

// FUNCTION: 0x10AB46C0 ?InitializePrivateStaticClassURopeArrowSpawnLinkDataObject@URopeArrowSpawnLinkDataObject@@SAXXZ
void URopeArrowSpawnLinkDataObject::InitializePrivateStaticClassURopeArrowSpawnLinkDataObject()
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

// FUNCTION: 0x10AB47D0 ?InitializePrivateStaticClassADifficultyInfo@ADifficultyInfo@@SAXXZ
void ADifficultyInfo::InitializePrivateStaticClassADifficultyInfo()
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

// FUNCTION: 0x10AB48E0 ?InitializePrivateStaticClassAEnterMissionInfo@AEnterMissionInfo@@SAXXZ
void AEnterMissionInfo::InitializePrivateStaticClassAEnterMissionInfo()
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

// FUNCTION: 0x10AB49F0 ?InitializePrivateStaticClassAExitMissionInfo@AExitMissionInfo@@SAXXZ
void AExitMissionInfo::InitializePrivateStaticClassAExitMissionInfo()
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

// FUNCTION: 0x10AB4B00 ?InitializePrivateStaticClassASpellProjectile@ASpellProjectile@@SAXXZ
void ASpellProjectile::InitializePrivateStaticClassASpellProjectile()
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

// FUNCTION: 0x10AB4C10 ?InitializePrivateStaticClassAWakeupCameraPoint@AWakeupCameraPoint@@SAXXZ
void AWakeupCameraPoint::InitializePrivateStaticClassAWakeupCameraPoint()
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

// FUNCTION: 0x10AB5070 ?GetPrivateStaticClassADifficultyInfo@ADifficultyInfo@@SAPAVUClass@@PBD@Z
UClass* ADifficultyInfo::GetPrivateStaticClassADifficultyInfo(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ADifficultyInfo), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("ADifficultyInfo")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&ADifficultyInfo::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10AB5140 ?GetPrivateStaticClassAExitMissionInfo@AExitMissionInfo@@SAPAVUClass@@PBD@Z
UClass* AExitMissionInfo::GetPrivateStaticClassAExitMissionInfo(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AExitMissionInfo), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AExitMissionInfo")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AExitMissionInfo::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10AB5210 ?GetPrivateStaticClassASpellProjectile@ASpellProjectile@@SAPAVUClass@@PBD@Z
UClass* ASpellProjectile::GetPrivateStaticClassASpellProjectile(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ASpellProjectile), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("ASpellProjectile")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&ASpellProjectile::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10AB52E0 ?GetPrivateStaticClassAWakeupCameraPoint@AWakeupCameraPoint@@SAPAVUClass@@PBD@Z
UClass* AWakeupCameraPoint::GetPrivateStaticClassAWakeupCameraPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AWakeupCameraPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AWakeupCameraPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AWakeupCameraPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10AB5400 ?GetPrivateStaticClassULockLinkDataObject@ULockLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* ULockLinkDataObject::GetPrivateStaticClassULockLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ULockLinkDataObject), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("ULockLinkDataObject")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&ULockLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10AB54C0 ?GetPrivateStaticClassUSpawnPoolLinkDataObject@USpawnPoolLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* USpawnPoolLinkDataObject::GetPrivateStaticClassUSpawnPoolLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(USpawnPoolLinkDataObject), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("USpawnPoolLinkDataObject")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&USpawnPoolLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10AB5580 ?GetPrivateStaticClassULockTickLinkDataObject@ULockTickLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* ULockTickLinkDataObject::GetPrivateStaticClassULockTickLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ULockTickLinkDataObject), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("ULockTickLinkDataObject")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&ULockTickLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10AB5640 ?GetPrivateStaticClassUInventorySwitchLinkDataObject@UInventorySwitchLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UInventorySwitchLinkDataObject::GetPrivateStaticClassUInventorySwitchLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UInventorySwitchLinkDataObject), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("UInventorySwitchLinkDataObject")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&UInventorySwitchLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10AB5700 ?GetPrivateStaticClassURopeArrowSpawnLinkDataObject@URopeArrowSpawnLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* URopeArrowSpawnLinkDataObject::GetPrivateStaticClassURopeArrowSpawnLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(URopeArrowSpawnLinkDataObject), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("URopeArrowSpawnLinkDataObject")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&URopeArrowSpawnLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10AB59B0 ?GetPrivateStaticClassAEnterMissionInfo@AEnterMissionInfo@@SAPAVUClass@@PBD@Z
UClass* AEnterMissionInfo::GetPrivateStaticClassAEnterMissionInfo(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AEnterMissionInfo), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AEnterMissionInfo")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AEnterMissionInfo::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}
