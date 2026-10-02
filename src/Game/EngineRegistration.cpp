// Game/EngineRegistration.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Engine/EngineClasses.h"

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

// FUNCTION: 0x109771B0 ?GetPrivateStaticClassUAISubsystem@UAISubsystem@@SAPAVUClass@@PBD@Z
UClass* UAISubsystem::GetPrivateStaticClassUAISubsystem(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UAISubsystem), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UAISubsystem")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UAISubsystem::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10977280 ?InitializePrivateStaticClassUAISubsystem@UAISubsystem@@SAXXZ
void UAISubsystem::InitializePrivateStaticClassUAISubsystem()
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

// FUNCTION: 0x10977390 ?GetPrivateStaticClassUPhysicsSubsystem@UPhysicsSubsystem@@SAPAVUClass@@PBD@Z
UClass* UPhysicsSubsystem::GetPrivateStaticClassUPhysicsSubsystem(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UPhysicsSubsystem), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UPhysicsSubsystem")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UPhysicsSubsystem::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10977460 ?InitializePrivateStaticClassUPhysicsSubsystem@UPhysicsSubsystem@@SAXXZ
void UPhysicsSubsystem::InitializePrivateStaticClassUPhysicsSubsystem()
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

// FUNCTION: 0x10977570 ?GetPrivateStaticClassUGameSubsystem@UGameSubsystem@@SAPAVUClass@@PBD@Z
UClass* UGameSubsystem::GetPrivateStaticClassUGameSubsystem(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UGameSubsystem), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UGameSubsystem")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UGameSubsystem::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10977930 ?GetPrivateStaticClassUTriggerRegistrar@UTriggerRegistrar@@SAPAVUClass@@PBD@Z
UClass* UTriggerRegistrar::GetPrivateStaticClassUTriggerRegistrar(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UTriggerRegistrar), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UTriggerRegistrar")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UTriggerRegistrar::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1098AAE0 ?InitializePrivateStaticClassUCARDEntry@UCARDEntry@@SAXXZ
void UCARDEntry::InitializePrivateStaticClassUCARDEntry()
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

// FUNCTION: 0x1098ACB0 ?GetPrivateStaticClassUCARDEntry@UCARDEntry@@SAPAVUClass@@PBD@Z
UClass* UCARDEntry::GetPrivateStaticClassUCARDEntry(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UCARDEntry), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UCARDEntry")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UCARDEntry::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1098CD30 ?GetPrivateStaticClassAPlayerPawn@APlayerPawn@@SAPAVUClass@@PBD@Z
UClass* APlayerPawn::GetPrivateStaticClassAPlayerPawn(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(APlayerPawn), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("APlayerPawn")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&APlayerPawn::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1098F540 ?GetPrivateStaticClassAObjSysTest@AObjSysTest@@SAPAVUClass@@PBD@Z
UClass* AObjSysTest::GetPrivateStaticClassAObjSysTest(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AObjSysTest), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AObjSysTest")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AObjSysTest::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1098F610 ?InitializePrivateStaticClassAObjSysTest@AObjSysTest@@SAXXZ
void AObjSysTest::InitializePrivateStaticClassAObjSysTest()
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

// FUNCTION: 0x1098F720 ?GetPrivateStaticClassAObjSysTestChild@AObjSysTestChild@@SAPAVUClass@@PBD@Z
UClass* AObjSysTestChild::GetPrivateStaticClassAObjSysTestChild(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AObjSysTestChild), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AObjSysTestChild")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AObjSysTestChild::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1098F7F0 ?GetPrivateStaticClassAMarker@AMarker@@SAPAVUClass@@PBD@Z
UClass* AMarker::GetPrivateStaticClassAMarker(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AMarker), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AMarker")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AMarker::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1098F8C0 ?InitializePrivateStaticClassAMarker@AMarker@@SAXXZ
void AMarker::InitializePrivateStaticClassAMarker()
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

// FUNCTION: 0x1098F9D0 ?GetPrivateStaticClassAMetaProperty@AMetaProperty@@SAPAVUClass@@PBD@Z
UClass* AMetaProperty::GetPrivateStaticClassAMetaProperty(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AMetaProperty), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AMetaProperty")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AMetaProperty::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1098FAA0 ?InitializePrivateStaticClassAMetaProperty@AMetaProperty@@SAXXZ
void AMetaProperty::InitializePrivateStaticClassAMetaProperty()
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

// FUNCTION: 0x1098FBB0 ?GetPrivateStaticClassAFX@AFX@@SAPAVUClass@@PBD@Z
UClass* AFX::GetPrivateStaticClassAFX(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AFX), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AFX")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AFX::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1098FC80 ?InitializePrivateStaticClassAFX@AFX@@SAXXZ
void AFX::InitializePrivateStaticClassAFX()
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

// FUNCTION: 0x1098FD90 ?GetPrivateStaticClassAMetaData@AMetaData@@SAPAVUClass@@PBD@Z
UClass* AMetaData::GetPrivateStaticClassAMetaData(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AMetaData), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AMetaData")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AMetaData::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1098FE60 ?InitializePrivateStaticClassAMetaData@AMetaData@@SAXXZ
void AMetaData::InitializePrivateStaticClassAMetaData()
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

// FUNCTION: 0x1098FF70 ?GetPrivateStaticClassAMissingArch@AMissingArch@@SAPAVUClass@@PBD@Z
UClass* AMissingArch::GetPrivateStaticClassAMissingArch(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AMissingArch), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AMissingArch")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AMissingArch::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10990040 ?InitializePrivateStaticClassAMissingArch@AMissingArch@@SAXXZ
void AMissingArch::InitializePrivateStaticClassAMissingArch()
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

// FUNCTION: 0x10990150 ?GetPrivateStaticClassAElevatorFloors@AElevatorFloors@@SAPAVUClass@@PBD@Z
UClass* AElevatorFloors::GetPrivateStaticClassAElevatorFloors(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AElevatorFloors), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AElevatorFloors")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AElevatorFloors::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10990220 ?GetPrivateStaticClassAZoneProperties@AZoneProperties@@SAPAVUClass@@PBD@Z
UClass* AZoneProperties::GetPrivateStaticClassAZoneProperties(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AZoneProperties), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AZoneProperties")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AZoneProperties::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109902F0 ?GetPrivateStaticClassASpecialOptions@ASpecialOptions@@SAPAVUClass@@PBD@Z
UClass* ASpecialOptions::GetPrivateStaticClassASpecialOptions(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ASpecialOptions), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("ASpecialOptions")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&ASpecialOptions::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10995000 ?GetPrivateStaticClassAAmbientLightVolume@AAmbientLightVolume@@SAPAVUClass@@PBD@Z
UClass* AAmbientLightVolume::GetPrivateStaticClassAAmbientLightVolume(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAmbientLightVolume), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AAmbientLightVolume")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AAmbientLightVolume::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1099BD50 ?InitializePrivateStaticClassUSpawnLinkDataObject@USpawnLinkDataObject@@SAXXZ
void USpawnLinkDataObject::InitializePrivateStaticClassUSpawnLinkDataObject()
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

// FUNCTION: 0x1099BE60 ?InitializePrivateStaticClassUAlarmLinkDataObject@UAlarmLinkDataObject@@SAXXZ
void UAlarmLinkDataObject::InitializePrivateStaticClassUAlarmLinkDataObject()
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

// FUNCTION: 0x1099BF70 ?InitializePrivateStaticClassULightLinkDataObject@ULightLinkDataObject@@SAXXZ
void ULightLinkDataObject::InitializePrivateStaticClassULightLinkDataObject()
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

// FUNCTION: 0x1099C080 ?InitializePrivateStaticClassUPowerLinkDataObject@UPowerLinkDataObject@@SAXXZ
void UPowerLinkDataObject::InitializePrivateStaticClassUPowerLinkDataObject()
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

// FUNCTION: 0x1099C190 ?InitializePrivateStaticClassUBreakingBeamLinkDataObject@UBreakingBeamLinkDataObject@@SAXXZ
void UBreakingBeamLinkDataObject::InitializePrivateStaticClassUBreakingBeamLinkDataObject()
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

// FUNCTION: 0x1099C2A0 ?InitializePrivateStaticClassUAmmoLinkDataObject@UAmmoLinkDataObject@@SAXXZ
void UAmmoLinkDataObject::InitializePrivateStaticClassUAmmoLinkDataObject()
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

// FUNCTION: 0x1099C3B0 ?InitializePrivateStaticClassUUserLinkDataObject@UUserLinkDataObject@@SAXXZ
void UUserLinkDataObject::InitializePrivateStaticClassUUserLinkDataObject()
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

// FUNCTION: 0x1099C4C0 ?InitializePrivateStaticClassUTargetLinkDataObject@UTargetLinkDataObject@@SAXXZ
void UTargetLinkDataObject::InitializePrivateStaticClassUTargetLinkDataObject()
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

// FUNCTION: 0x1099C5D0 ?InitializePrivateStaticClassUFrobLinkDataObject@UFrobLinkDataObject@@SAXXZ
void UFrobLinkDataObject::InitializePrivateStaticClassUFrobLinkDataObject()
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

// FUNCTION: 0x1099C6E0 ?InitializePrivateStaticClassUAttachmentLinkDataObject@UAttachmentLinkDataObject@@SAXXZ
void UAttachmentLinkDataObject::InitializePrivateStaticClassUAttachmentLinkDataObject()
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

// FUNCTION: 0x1099C7F0 ?InitializePrivateStaticClassUElevatorLinkDataObject@UElevatorLinkDataObject@@SAXXZ
void UElevatorLinkDataObject::InitializePrivateStaticClassUElevatorLinkDataObject()
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

// FUNCTION: 0x1099C900 ?InitializePrivateStaticClassUElevatorFloorMarkerLinkDataObject@UElevatorFloorMarkerLinkDataObject@@SAXXZ
void UElevatorFloorMarkerLinkDataObject::InitializePrivateStaticClassUElevatorFloorMarkerLinkDataObject()
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

// FUNCTION: 0x1099CA10 ?InitializePrivateStaticClassUAssociationLinkDataObject@UAssociationLinkDataObject@@SAXXZ
void UAssociationLinkDataObject::InitializePrivateStaticClassUAssociationLinkDataObject()
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

// FUNCTION: 0x1099CB20 ?InitializePrivateStaticClassUUserArmImplementationLinkDataObject@UUserArmImplementationLinkDataObject@@SAXXZ
void UUserArmImplementationLinkDataObject::InitializePrivateStaticClassUUserArmImplementationLinkDataObject()
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

// FUNCTION: 0x1099CC30 ?InitializePrivateStaticClassUFireEffectLinkDataObject@UFireEffectLinkDataObject@@SAXXZ
void UFireEffectLinkDataObject::InitializePrivateStaticClassUFireEffectLinkDataObject()
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

// FUNCTION: 0x1099CD40 ?InitializePrivateStaticClassURuntimeFireEffectLinkDataObject@URuntimeFireEffectLinkDataObject@@SAXXZ
void URuntimeFireEffectLinkDataObject::InitializePrivateStaticClassURuntimeFireEffectLinkDataObject()
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

// FUNCTION: 0x1099CE50 ?InitializePrivateStaticClassUFillLightLinkDataObject@UFillLightLinkDataObject@@SAXXZ
void UFillLightLinkDataObject::InitializePrivateStaticClassUFillLightLinkDataObject()
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

// FUNCTION: 0x1099CF60 ?InitializePrivateStaticClassUTriggerScriptLinkDataObject@UTriggerScriptLinkDataObject@@SAXXZ
void UTriggerScriptLinkDataObject::InitializePrivateStaticClassUTriggerScriptLinkDataObject()
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

// FUNCTION: 0x1099D070 ?InitializePrivateStaticClassUDoorLinkDataObject@UDoorLinkDataObject@@SAXXZ
void UDoorLinkDataObject::InitializePrivateStaticClassUDoorLinkDataObject()
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

// FUNCTION: 0x1099D180 ?InitializePrivateStaticClassUProjectileLinkDataObject@UProjectileLinkDataObject@@SAXXZ
void UProjectileLinkDataObject::InitializePrivateStaticClassUProjectileLinkDataObject()
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

// FUNCTION: 0x1099D290 ?InitializePrivateStaticClassUPlayerSetupInfoLinkDataObject@UPlayerSetupInfoLinkDataObject@@SAXXZ
void UPlayerSetupInfoLinkDataObject::InitializePrivateStaticClassUPlayerSetupInfoLinkDataObject()
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

// FUNCTION: 0x1099D3A0 ?GetPrivateStaticClassAVulnerabilityObject@AVulnerabilityObject@@SAPAVUClass@@PBD@Z
UClass* AVulnerabilityObject::GetPrivateStaticClassAVulnerabilityObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AVulnerabilityObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AVulnerabilityObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AVulnerabilityObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1099D470 ?InitializePrivateStaticClassAVulnerabilityObject@AVulnerabilityObject@@SAXXZ
void AVulnerabilityObject::InitializePrivateStaticClassAVulnerabilityObject()
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

// FUNCTION: 0x1099D580 ?GetPrivateStaticClassAStimulusModifierObject@AStimulusModifierObject@@SAPAVUClass@@PBD@Z
UClass* AStimulusModifierObject::GetPrivateStaticClassAStimulusModifierObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AStimulusModifierObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AStimulusModifierObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AStimulusModifierObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1099D650 ?InitializePrivateStaticClassAStimulusModifierObject@AStimulusModifierObject@@SAXXZ
void AStimulusModifierObject::InitializePrivateStaticClassAStimulusModifierObject()
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

// FUNCTION: 0x1099D760 ?InitializePrivateStaticClassUVulnerabilityLinkDataObject@UVulnerabilityLinkDataObject@@SAXXZ
void UVulnerabilityLinkDataObject::InitializePrivateStaticClassUVulnerabilityLinkDataObject()
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

// FUNCTION: 0x1099D870 ?InitializePrivateStaticClassUStimulusModifierLinkDataObject@UStimulusModifierLinkDataObject@@SAXXZ
void UStimulusModifierLinkDataObject::InitializePrivateStaticClassUStimulusModifierLinkDataObject()
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

// FUNCTION: 0x1099D980 ?GetPrivateStaticClassASwooshEffectObject@ASwooshEffectObject@@SAPAVUClass@@PBD@Z
UClass* ASwooshEffectObject::GetPrivateStaticClassASwooshEffectObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ASwooshEffectObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("ASwooshEffectObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&ASwooshEffectObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x1099DA50 ?InitializePrivateStaticClassASwooshEffectObject@ASwooshEffectObject@@SAXXZ
void ASwooshEffectObject::InitializePrivateStaticClassASwooshEffectObject()
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

// FUNCTION: 0x1099DB60 ?InitializePrivateStaticClassUSwooshLinkDataObject@USwooshLinkDataObject@@SAXXZ
void USwooshLinkDataObject::InitializePrivateStaticClassUSwooshLinkDataObject()
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

// FUNCTION: 0x1099DC70 ?InitializePrivateStaticClassUHighlightEventLinkDataObject@UHighlightEventLinkDataObject@@SAXXZ
void UHighlightEventLinkDataObject::InitializePrivateStaticClassUHighlightEventLinkDataObject()
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

// FUNCTION: 0x1099DD80 ?InitializePrivateStaticClassUFrobEventLinkDataObject@UFrobEventLinkDataObject@@SAXXZ
void UFrobEventLinkDataObject::InitializePrivateStaticClassUFrobEventLinkDataObject()
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

// FUNCTION: 0x1099DE90 ?InitializePrivateStaticClassUHardpointLinkDataObject@UHardpointLinkDataObject@@SAXXZ
void UHardpointLinkDataObject::InitializePrivateStaticClassUHardpointLinkDataObject()
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

// FUNCTION: 0x1099DFA0 ?InitializePrivateStaticClassUBotDominationLinkDataObject@UBotDominationLinkDataObject@@SAXXZ
void UBotDominationLinkDataObject::InitializePrivateStaticClassUBotDominationLinkDataObject()
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

// FUNCTION: 0x1099E0B0 ?InitializePrivateStaticClassUMovementModeLinkDataObject@UMovementModeLinkDataObject@@SAXXZ
void UMovementModeLinkDataObject::InitializePrivateStaticClassUMovementModeLinkDataObject()
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

// FUNCTION: 0x1099E1C0 ?InitializePrivateStaticClassULockAssociationLinkDataObject@ULockAssociationLinkDataObject@@SAXXZ
void ULockAssociationLinkDataObject::InitializePrivateStaticClassULockAssociationLinkDataObject()
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

// FUNCTION: 0x1099E2D0 ?InitializePrivateStaticClassUCinematicLightLinkDataObject@UCinematicLightLinkDataObject@@SAXXZ
void UCinematicLightLinkDataObject::InitializePrivateStaticClassUCinematicLightLinkDataObject()
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

// FUNCTION: 0x1099E3E0 ?InitializePrivateStaticClassUReferenceLinkDataObject@UReferenceLinkDataObject@@SAXXZ
void UReferenceLinkDataObject::InitializePrivateStaticClassUReferenceLinkDataObject()
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

// FUNCTION: 0x1099E4F0 ?InitializePrivateStaticClassULoadoutLinkDataObject@ULoadoutLinkDataObject@@SAXXZ
void ULoadoutLinkDataObject::InitializePrivateStaticClassULoadoutLinkDataObject()
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

// FUNCTION: 0x1099E600 ?InitializePrivateStaticClassUWeaponModLinkDataObject@UWeaponModLinkDataObject@@SAXXZ
void UWeaponModLinkDataObject::InitializePrivateStaticClassUWeaponModLinkDataObject()
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

// FUNCTION: 0x1099E710 ?InitializePrivateStaticClassUSittingLinkDataObject@USittingLinkDataObject@@SAXXZ
void USittingLinkDataObject::InitializePrivateStaticClassUSittingLinkDataObject()
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

// FUNCTION: 0x1099E820 ?InitializePrivateStaticClassUSleepingLinkDataObject@USleepingLinkDataObject@@SAXXZ
void USleepingLinkDataObject::InitializePrivateStaticClassUSleepingLinkDataObject()
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

// FUNCTION: 0x1099E930 ?InitializePrivateStaticClassUDestroyOnDeathLinkDataObject@UDestroyOnDeathLinkDataObject@@SAXXZ
void UDestroyOnDeathLinkDataObject::InitializePrivateStaticClassUDestroyOnDeathLinkDataObject()
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

// FUNCTION: 0x1099EA40 ?InitializePrivateStaticClassUSkeletalFireEffectLinkDataObject@USkeletalFireEffectLinkDataObject@@SAXXZ
void USkeletalFireEffectLinkDataObject::InitializePrivateStaticClassUSkeletalFireEffectLinkDataObject()
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

// FUNCTION: 0x1099EB50 ?InitializePrivateStaticClassUWaypointInterpolationLinkDataObject@UWaypointInterpolationLinkDataObject@@SAXXZ
void UWaypointInterpolationLinkDataObject::InitializePrivateStaticClassUWaypointInterpolationLinkDataObject()
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

// FUNCTION: 0x1099EC60 ?InitializePrivateStaticClassUHitSpangLinkDataObject@UHitSpangLinkDataObject@@SAXXZ
void UHitSpangLinkDataObject::InitializePrivateStaticClassUHitSpangLinkDataObject()
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

// FUNCTION: 0x1099ED70 ?InitializePrivateStaticClassUOwnershipLinkDataObject@UOwnershipLinkDataObject@@SAXXZ
void UOwnershipLinkDataObject::InitializePrivateStaticClassUOwnershipLinkDataObject()
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

// FUNCTION: 0x1099EE80 ?InitializePrivateStaticClassUInterestLinkDataObject@UInterestLinkDataObject@@SAXXZ
void UInterestLinkDataObject::InitializePrivateStaticClassUInterestLinkDataObject()
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

// FUNCTION: 0x1099EF90 ?InitializePrivateStaticClassUPuddleMarkLinkDataObject@UPuddleMarkLinkDataObject@@SAXXZ
void UPuddleMarkLinkDataObject::InitializePrivateStaticClassUPuddleMarkLinkDataObject()
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

// FUNCTION: 0x1099F0A0 ?InitializePrivateStaticClassUPuddleConnectorLinkDataObject@UPuddleConnectorLinkDataObject@@SAXXZ
void UPuddleConnectorLinkDataObject::InitializePrivateStaticClassUPuddleConnectorLinkDataObject()
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

// FUNCTION: 0x109A19F0 ?GetPrivateStaticClassUSpawnLinkDataObject@USpawnLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* USpawnLinkDataObject::GetPrivateStaticClassUSpawnLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(USpawnLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("USpawnLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&USpawnLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A1AB0 ?GetPrivateStaticClassUFlinderizeLinkDataObject@UFlinderizeLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UFlinderizeLinkDataObject::GetPrivateStaticClassUFlinderizeLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UFlinderizeLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UFlinderizeLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UFlinderizeLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A1B70 ?GetPrivateStaticClassUAlarmLinkDataObject@UAlarmLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UAlarmLinkDataObject::GetPrivateStaticClassUAlarmLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UAlarmLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UAlarmLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UAlarmLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A1C30 ?GetPrivateStaticClassULightLinkDataObject@ULightLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* ULightLinkDataObject::GetPrivateStaticClassULightLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ULightLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("ULightLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&ULightLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A1CF0 ?GetPrivateStaticClassUPowerLinkDataObject@UPowerLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UPowerLinkDataObject::GetPrivateStaticClassUPowerLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UPowerLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UPowerLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UPowerLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A1DB0 ?GetPrivateStaticClassUBreakingBeamLinkDataObject@UBreakingBeamLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UBreakingBeamLinkDataObject::GetPrivateStaticClassUBreakingBeamLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UBreakingBeamLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UBreakingBeamLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UBreakingBeamLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A1E70 ?GetPrivateStaticClassUAmmoLinkDataObject@UAmmoLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UAmmoLinkDataObject::GetPrivateStaticClassUAmmoLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UAmmoLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UAmmoLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UAmmoLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A1F30 ?GetPrivateStaticClassUUserLinkDataObject@UUserLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UUserLinkDataObject::GetPrivateStaticClassUUserLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UUserLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UUserLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UUserLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A1FF0 ?GetPrivateStaticClassUTargetLinkDataObject@UTargetLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UTargetLinkDataObject::GetPrivateStaticClassUTargetLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UTargetLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UTargetLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UTargetLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A20B0 ?GetPrivateStaticClassUFrobLinkDataObject@UFrobLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UFrobLinkDataObject::GetPrivateStaticClassUFrobLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UFrobLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UFrobLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UFrobLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2170 ?GetPrivateStaticClassUAttachmentLinkDataObject@UAttachmentLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UAttachmentLinkDataObject::GetPrivateStaticClassUAttachmentLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UAttachmentLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UAttachmentLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UAttachmentLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2230 ?GetPrivateStaticClassURigidAttachmentLinkDataObject@URigidAttachmentLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* URigidAttachmentLinkDataObject::GetPrivateStaticClassURigidAttachmentLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(URigidAttachmentLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("URigidAttachmentLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&URigidAttachmentLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2300 ?GetPrivateStaticClassUSlidingAttachmentLinkDataObject@USlidingAttachmentLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* USlidingAttachmentLinkDataObject::GetPrivateStaticClassUSlidingAttachmentLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(USlidingAttachmentLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("USlidingAttachmentLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&USlidingAttachmentLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A23D0 ?GetPrivateStaticClassUHingedAttachmentLinkDataObject@UHingedAttachmentLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UHingedAttachmentLinkDataObject::GetPrivateStaticClassUHingedAttachmentLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UHingedAttachmentLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UHingedAttachmentLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UHingedAttachmentLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A24A0 ?GetPrivateStaticClassUPointAttachmentLinkDataObject@UPointAttachmentLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UPointAttachmentLinkDataObject::GetPrivateStaticClassUPointAttachmentLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UPointAttachmentLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UPointAttachmentLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UPointAttachmentLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2570 ?GetPrivateStaticClassUElevatorLinkDataObject@UElevatorLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UElevatorLinkDataObject::GetPrivateStaticClassUElevatorLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UElevatorLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UElevatorLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UElevatorLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2630 ?GetPrivateStaticClassUElevatorFloorMarkerLinkDataObject@UElevatorFloorMarkerLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UElevatorFloorMarkerLinkDataObject::GetPrivateStaticClassUElevatorFloorMarkerLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UElevatorFloorMarkerLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UElevatorFloorMarkerLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UElevatorFloorMarkerLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A26F0 ?GetPrivateStaticClassURuntimeAttachmentLinkDataObject@URuntimeAttachmentLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* URuntimeAttachmentLinkDataObject::GetPrivateStaticClassURuntimeAttachmentLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(URuntimeAttachmentLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("URuntimeAttachmentLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&URuntimeAttachmentLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A27B0 ?GetPrivateStaticClassUDeathSpawnLinkDataObject@UDeathSpawnLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UDeathSpawnLinkDataObject::GetPrivateStaticClassUDeathSpawnLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UDeathSpawnLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UDeathSpawnLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UDeathSpawnLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2870 ?GetPrivateStaticClassUCreationSpawnLinkDataObject@UCreationSpawnLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UCreationSpawnLinkDataObject::GetPrivateStaticClassUCreationSpawnLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UCreationSpawnLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UCreationSpawnLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UCreationSpawnLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2930 ?GetPrivateStaticClassUAssociationLinkDataObject@UAssociationLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UAssociationLinkDataObject::GetPrivateStaticClassUAssociationLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UAssociationLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UAssociationLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UAssociationLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A29F0 ?GetPrivateStaticClassUUserArmImplementationLinkDataObject@UUserArmImplementationLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UUserArmImplementationLinkDataObject::GetPrivateStaticClassUUserArmImplementationLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UUserArmImplementationLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UUserArmImplementationLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UUserArmImplementationLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2AB0 ?GetPrivateStaticClassUFireEffectLinkDataObject@UFireEffectLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UFireEffectLinkDataObject::GetPrivateStaticClassUFireEffectLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UFireEffectLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UFireEffectLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UFireEffectLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2B70 ?GetPrivateStaticClassURuntimeFireEffectLinkDataObject@URuntimeFireEffectLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* URuntimeFireEffectLinkDataObject::GetPrivateStaticClassURuntimeFireEffectLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(URuntimeFireEffectLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("URuntimeFireEffectLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&URuntimeFireEffectLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2C30 ?GetPrivateStaticClassUFillLightLinkDataObject@UFillLightLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UFillLightLinkDataObject::GetPrivateStaticClassUFillLightLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UFillLightLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UFillLightLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UFillLightLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2CF0 ?GetPrivateStaticClassUTriggerScriptLinkDataObject@UTriggerScriptLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UTriggerScriptLinkDataObject::GetPrivateStaticClassUTriggerScriptLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UTriggerScriptLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UTriggerScriptLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UTriggerScriptLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2DB0 ?GetPrivateStaticClassUDoorLinkDataObject@UDoorLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UDoorLinkDataObject::GetPrivateStaticClassUDoorLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UDoorLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UDoorLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UDoorLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2E70 ?GetPrivateStaticClassUProjectileLinkDataObject@UProjectileLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UProjectileLinkDataObject::GetPrivateStaticClassUProjectileLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UProjectileLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UProjectileLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UProjectileLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2F30 ?GetPrivateStaticClassUPlayerSetupInfoLinkDataObject@UPlayerSetupInfoLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UPlayerSetupInfoLinkDataObject::GetPrivateStaticClassUPlayerSetupInfoLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UPlayerSetupInfoLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UPlayerSetupInfoLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UPlayerSetupInfoLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A2FF0 ?GetPrivateStaticClassUCollisionSpawnLinkDataObject@UCollisionSpawnLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UCollisionSpawnLinkDataObject::GetPrivateStaticClassUCollisionSpawnLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UCollisionSpawnLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UCollisionSpawnLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UCollisionSpawnLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A30C0 ?GetPrivateStaticClassUVulnerabilityLinkDataObject@UVulnerabilityLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UVulnerabilityLinkDataObject::GetPrivateStaticClassUVulnerabilityLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UVulnerabilityLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UVulnerabilityLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UVulnerabilityLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3180 ?GetPrivateStaticClassUStimulusModifierLinkDataObject@UStimulusModifierLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UStimulusModifierLinkDataObject::GetPrivateStaticClassUStimulusModifierLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UStimulusModifierLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UStimulusModifierLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UStimulusModifierLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3240 ?GetPrivateStaticClassUSwooshLinkDataObject@USwooshLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* USwooshLinkDataObject::GetPrivateStaticClassUSwooshLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(USwooshLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("USwooshLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&USwooshLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3300 ?GetPrivateStaticClassUHighlightEventLinkDataObject@UHighlightEventLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UHighlightEventLinkDataObject::GetPrivateStaticClassUHighlightEventLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UHighlightEventLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UHighlightEventLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UHighlightEventLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A33C0 ?GetPrivateStaticClassUFrobEventLinkDataObject@UFrobEventLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UFrobEventLinkDataObject::GetPrivateStaticClassUFrobEventLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UFrobEventLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UFrobEventLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UFrobEventLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3480 ?GetPrivateStaticClassUHardpointLinkDataObject@UHardpointLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UHardpointLinkDataObject::GetPrivateStaticClassUHardpointLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UHardpointLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UHardpointLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UHardpointLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3540 ?GetPrivateStaticClassUBotDominationLinkDataObject@UBotDominationLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UBotDominationLinkDataObject::GetPrivateStaticClassUBotDominationLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UBotDominationLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UBotDominationLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UBotDominationLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3600 ?GetPrivateStaticClassUMovementModeLinkDataObject@UMovementModeLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UMovementModeLinkDataObject::GetPrivateStaticClassUMovementModeLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UMovementModeLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UMovementModeLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UMovementModeLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A36C0 ?GetPrivateStaticClassUDelaySpawnLinkDataObject@UDelaySpawnLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UDelaySpawnLinkDataObject::GetPrivateStaticClassUDelaySpawnLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UDelaySpawnLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UDelaySpawnLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UDelaySpawnLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3780 ?GetPrivateStaticClassULockAssociationLinkDataObject@ULockAssociationLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* ULockAssociationLinkDataObject::GetPrivateStaticClassULockAssociationLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ULockAssociationLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("ULockAssociationLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&ULockAssociationLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3840 ?GetPrivateStaticClassUCinematicLightLinkDataObject@UCinematicLightLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UCinematicLightLinkDataObject::GetPrivateStaticClassUCinematicLightLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UCinematicLightLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UCinematicLightLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UCinematicLightLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3900 ?GetPrivateStaticClassUReferenceLinkDataObject@UReferenceLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UReferenceLinkDataObject::GetPrivateStaticClassUReferenceLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UReferenceLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UReferenceLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UReferenceLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A39C0 ?GetPrivateStaticClassULoadoutLinkDataObject@ULoadoutLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* ULoadoutLinkDataObject::GetPrivateStaticClassULoadoutLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ULoadoutLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("ULoadoutLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&ULoadoutLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3A80 ?GetPrivateStaticClassUSpawnableHardpointLinkDataObject@USpawnableHardpointLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* USpawnableHardpointLinkDataObject::GetPrivateStaticClassUSpawnableHardpointLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(USpawnableHardpointLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("USpawnableHardpointLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&USpawnableHardpointLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3B40 ?GetPrivateStaticClassUWeaponModLinkDataObject@UWeaponModLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UWeaponModLinkDataObject::GetPrivateStaticClassUWeaponModLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UWeaponModLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UWeaponModLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UWeaponModLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3C00 ?GetPrivateStaticClassUFragRoundLinkDataObject@UFragRoundLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UFragRoundLinkDataObject::GetPrivateStaticClassUFragRoundLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UFragRoundLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UFragRoundLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UFragRoundLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3CC0 ?GetPrivateStaticClassUSittingLinkDataObject@USittingLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* USittingLinkDataObject::GetPrivateStaticClassUSittingLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(USittingLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("USittingLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&USittingLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3D80 ?GetPrivateStaticClassUSleepingLinkDataObject@USleepingLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* USleepingLinkDataObject::GetPrivateStaticClassUSleepingLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(USleepingLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("USleepingLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&USleepingLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3E40 ?GetPrivateStaticClassUDestroyOnDeathLinkDataObject@UDestroyOnDeathLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UDestroyOnDeathLinkDataObject::GetPrivateStaticClassUDestroyOnDeathLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UDestroyOnDeathLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UDestroyOnDeathLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UDestroyOnDeathLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3F00 ?GetPrivateStaticClassUSkeletalFireEffectLinkDataObject@USkeletalFireEffectLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* USkeletalFireEffectLinkDataObject::GetPrivateStaticClassUSkeletalFireEffectLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(USkeletalFireEffectLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("USkeletalFireEffectLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&USkeletalFireEffectLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A3FC0 ?GetPrivateStaticClassUWaypointInterpolationLinkDataObject@UWaypointInterpolationLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UWaypointInterpolationLinkDataObject::GetPrivateStaticClassUWaypointInterpolationLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UWaypointInterpolationLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UWaypointInterpolationLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UWaypointInterpolationLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A4080 ?GetPrivateStaticClassUHitSpangLinkDataObject@UHitSpangLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UHitSpangLinkDataObject::GetPrivateStaticClassUHitSpangLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UHitSpangLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UHitSpangLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UHitSpangLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A4140 ?GetPrivateStaticClassUOwnershipLinkDataObject@UOwnershipLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UOwnershipLinkDataObject::GetPrivateStaticClassUOwnershipLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UOwnershipLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UOwnershipLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UOwnershipLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A4200 ?GetPrivateStaticClassUInterestLinkDataObject@UInterestLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UInterestLinkDataObject::GetPrivateStaticClassUInterestLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UInterestLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UInterestLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UInterestLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A42C0 ?GetPrivateStaticClassUPuddleMarkLinkDataObject@UPuddleMarkLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UPuddleMarkLinkDataObject::GetPrivateStaticClassUPuddleMarkLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UPuddleMarkLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UPuddleMarkLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UPuddleMarkLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x109A4380 ?GetPrivateStaticClassUPuddleConnectorLinkDataObject@UPuddleConnectorLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UPuddleConnectorLinkDataObject::GetPrivateStaticClassUPuddleConnectorLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UPuddleConnectorLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UPuddleConnectorLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UPuddleConnectorLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}
