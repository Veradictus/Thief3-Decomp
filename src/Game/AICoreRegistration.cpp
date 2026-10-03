// Game/AICoreRegistration.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "AICore/AICoreClasses.h"

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

// FUNCTION: 0x10B93900 ??1AAddAIPoint@@UAE@XZ
AAddAIPoint::~AAddAIPoint()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B939A0 ??1AChangeDirectionPoint@@UAE@XZ
AChangeDirectionPoint::~AChangeDirectionPoint()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B93A40 ??1AFormationPoint@@UAE@XZ
AFormationPoint::~AFormationPoint()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B93AE0 ??1AFormationPointAbsolute@@UAE@XZ
AFormationPointAbsolute::~AFormationPointAbsolute()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B93B80 ??1AHeadTurnPoint@@UAE@XZ
AHeadTurnPoint::~AHeadTurnPoint()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B93BD0 ??1ALookPoint@@UAE@XZ
ALookPoint::~ALookPoint()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B93CC0 ??1APlayAnimPoint@@UAE@XZ
APlayAnimPoint::~APlayAnimPoint()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B93D60 ??1APlayBarkPoint@@UAE@XZ
APlayBarkPoint::~APlayBarkPoint()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B93DB0 ??1APatrolPoint@@UAE@XZ
APatrolPoint::~APatrolPoint()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B93EA0 ??1ACityPopPoint@@UAE@XZ
ACityPopPoint::~ACityPopPoint()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B93F40 ??1AWanderPoint@@UAE@XZ
AWanderPoint::~AWanderPoint()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B94170 ?InitializePrivateStaticClassAAIModel@AAIModel@@SAXXZ
void AAIModel::InitializePrivateStaticClassAAIModel()
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

// FUNCTION: 0x10B94280 ?InitializePrivateStaticClassAAIPathPoint@AAIPathPoint@@SAXXZ
void AAIPathPoint::InitializePrivateStaticClassAAIPathPoint()
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

// FUNCTION: 0x10B94390 ?InitializePrivateStaticClassAFocusPoint@AFocusPoint@@SAXXZ
void AFocusPoint::InitializePrivateStaticClassAFocusPoint()
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

// FUNCTION: 0x10B944A0 ?InitializePrivateStaticClassAAIPawnController@AAIPawnController@@SAXXZ
void AAIPawnController::InitializePrivateStaticClassAAIPawnController()
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

// FUNCTION: 0x10B945B0 ?InitializePrivateStaticClassAAIPawn@AAIPawn@@SAXXZ
void AAIPawn::InitializePrivateStaticClassAAIPawn()
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

// FUNCTION: 0x10B946C0 ?InitializePrivateStaticClassAAIContextVolume@AAIContextVolume@@SAXXZ
void AAIContextVolume::InitializePrivateStaticClassAAIContextVolume()
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

// FUNCTION: 0x10B947D0 ?InitializePrivateStaticClassAAITaggedVolume@AAITaggedVolume@@SAXXZ
void AAITaggedVolume::InitializePrivateStaticClassAAITaggedVolume()
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

// FUNCTION: 0x10B948E0 ?GetPrivateStaticClassUAI@UAI@@SAPAVUClass@@PBD@Z
UClass* UAI::GetPrivateStaticClassUAI(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UAI), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("UAI")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&UAI::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B949B0 ?InitializePrivateStaticClassUAI@UAI@@SAXXZ
void UAI::InitializePrivateStaticClassUAI()
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

// FUNCTION: 0x10B94AC0 ?InitializePrivateStaticClassAEnumStateType@AEnumStateType@@SAXXZ
void AEnumStateType::InitializePrivateStaticClassAEnumStateType()
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

// FUNCTION: 0x10B94BD0 ?InitializePrivateStaticClassAEnumEvidenceType@AEnumEvidenceType@@SAXXZ
void AEnumEvidenceType::InitializePrivateStaticClassAEnumEvidenceType()
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

// FUNCTION: 0x10B94CE0 ?InitializePrivateStaticClassAEnumInferenceType@AEnumInferenceType@@SAXXZ
void AEnumInferenceType::InitializePrivateStaticClassAEnumInferenceType()
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

// FUNCTION: 0x10B94DF0 ?InitializePrivateStaticClassANavMeshSubtractionVolume@ANavMeshSubtractionVolume@@SAXXZ
void ANavMeshSubtractionVolume::InitializePrivateStaticClassANavMeshSubtractionVolume()
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

// FUNCTION: 0x10B94F00 ?InitializePrivateStaticClassANavMeshInsertionPoint@ANavMeshInsertionPoint@@SAXXZ
void ANavMeshInsertionPoint::InitializePrivateStaticClassANavMeshInsertionPoint()
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

// FUNCTION: 0x10B95010 ?InitializePrivateStaticClassACitySectionPopulationInfo@ACitySectionPopulationInfo@@SAXXZ
void ACitySectionPopulationInfo::InitializePrivateStaticClassACitySectionPopulationInfo()
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

// FUNCTION: 0x10B952E0 ?GetPrivateStaticClassAAIModel@AAIModel@@SAPAVUClass@@PBD@Z
UClass* AAIModel::GetPrivateStaticClassAAIModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAIModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAIModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAIModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B953B0 ?GetPrivateStaticClassAAISensoryModel@AAISensoryModel@@SAPAVUClass@@PBD@Z
UClass* AAISensoryModel::GetPrivateStaticClassAAISensoryModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAISensoryModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAISensoryModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAISensoryModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95480 ?GetPrivateStaticClassAAIBehaviorModel@AAIBehaviorModel@@SAPAVUClass@@PBD@Z
UClass* AAIBehaviorModel::GetPrivateStaticClassAAIBehaviorModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAIBehaviorModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAIBehaviorModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAIBehaviorModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95550 ?GetPrivateStaticClassAAIMovementModel@AAIMovementModel@@SAPAVUClass@@PBD@Z
UClass* AAIMovementModel::GetPrivateStaticClassAAIMovementModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAIMovementModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAIMovementModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAIMovementModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95620 ?GetPrivateStaticClassAAICombatModel@AAICombatModel@@SAPAVUClass@@PBD@Z
UClass* AAICombatModel::GetPrivateStaticClassAAICombatModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAICombatModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAICombatModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAICombatModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B956F0 ?GetPrivateStaticClassAAIFactionModel@AAIFactionModel@@SAPAVUClass@@PBD@Z
UClass* AAIFactionModel::GetPrivateStaticClassAAIFactionModel(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAIFactionModel), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAIFactionModel")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAIFactionModel::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B957C0 ?GetPrivateStaticClassAAIPathPoint@AAIPathPoint@@SAPAVUClass@@PBD@Z
UClass* AAIPathPoint::GetPrivateStaticClassAAIPathPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAIPathPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAIPathPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAIPathPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95890 ?GetPrivateStaticClassAFocusPoint@AFocusPoint@@SAPAVUClass@@PBD@Z
UClass* AFocusPoint::GetPrivateStaticClassAFocusPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AFocusPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AFocusPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AFocusPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95960 ?GetPrivateStaticClassAPatrolPoint@APatrolPoint@@SAPAVUClass@@PBD@Z
UClass* APatrolPoint::GetPrivateStaticClassAPatrolPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(APatrolPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("APatrolPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&APatrolPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95A30 ?GetPrivateStaticClassAWanderPoint@AWanderPoint@@SAPAVUClass@@PBD@Z
UClass* AWanderPoint::GetPrivateStaticClassAWanderPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AWanderPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AWanderPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AWanderPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95B00 ?GetPrivateStaticClassAAddAIPoint@AAddAIPoint@@SAPAVUClass@@PBD@Z
UClass* AAddAIPoint::GetPrivateStaticClassAAddAIPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAddAIPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAddAIPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAddAIPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95BD0 ?GetPrivateStaticClassAFormationPoint@AFormationPoint@@SAPAVUClass@@PBD@Z
UClass* AFormationPoint::GetPrivateStaticClassAFormationPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AFormationPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AFormationPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AFormationPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95CA0 ?GetPrivateStaticClassAFormationPointAbsolute@AFormationPointAbsolute@@SAPAVUClass@@PBD@Z
UClass* AFormationPointAbsolute::GetPrivateStaticClassAFormationPointAbsolute(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AFormationPointAbsolute), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AFormationPointAbsolute")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AFormationPointAbsolute::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95D70 ?GetPrivateStaticClassAChangeDirectionPoint@AChangeDirectionPoint@@SAPAVUClass@@PBD@Z
UClass* AChangeDirectionPoint::GetPrivateStaticClassAChangeDirectionPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AChangeDirectionPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AChangeDirectionPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AChangeDirectionPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95E40 ?GetPrivateStaticClassALookPoint@ALookPoint@@SAPAVUClass@@PBD@Z
UClass* ALookPoint::GetPrivateStaticClassALookPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ALookPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("ALookPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&ALookPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95F10 ?GetPrivateStaticClassAPlayAnimPoint@APlayAnimPoint@@SAPAVUClass@@PBD@Z
UClass* APlayAnimPoint::GetPrivateStaticClassAPlayAnimPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(APlayAnimPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("APlayAnimPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&APlayAnimPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B95FE0 ?GetPrivateStaticClassAPlayBarkPoint@APlayBarkPoint@@SAPAVUClass@@PBD@Z
UClass* APlayBarkPoint::GetPrivateStaticClassAPlayBarkPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(APlayBarkPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("APlayBarkPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&APlayBarkPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B960B0 ?GetPrivateStaticClassAHeadTurnPoint@AHeadTurnPoint@@SAPAVUClass@@PBD@Z
UClass* AHeadTurnPoint::GetPrivateStaticClassAHeadTurnPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AHeadTurnPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AHeadTurnPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AHeadTurnPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B96180 ?GetPrivateStaticClassAAIPawnController@AAIPawnController@@SAPAVUClass@@PBD@Z
UClass* AAIPawnController::GetPrivateStaticClassAAIPawnController(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAIPawnController), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAIPawnController")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAIPawnController::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B96250 ?GetPrivateStaticClassAAIContextVolume@AAIContextVolume@@SAPAVUClass@@PBD@Z
UClass* AAIContextVolume::GetPrivateStaticClassAAIContextVolume(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAIContextVolume), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAIContextVolume")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAIContextVolume::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B96320 ?GetPrivateStaticClassAAITaggedVolume@AAITaggedVolume@@SAPAVUClass@@PBD@Z
UClass* AAITaggedVolume::GetPrivateStaticClassAAITaggedVolume(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAITaggedVolume), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAITaggedVolume")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAITaggedVolume::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B963F0 ?GetPrivateStaticClassAEnumStateType@AEnumStateType@@SAPAVUClass@@PBD@Z
UClass* AEnumStateType::GetPrivateStaticClassAEnumStateType(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AEnumStateType), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AEnumStateType")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AEnumStateType::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B964C0 ?GetPrivateStaticClassAEnumEvidenceType@AEnumEvidenceType@@SAPAVUClass@@PBD@Z
UClass* AEnumEvidenceType::GetPrivateStaticClassAEnumEvidenceType(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AEnumEvidenceType), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AEnumEvidenceType")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AEnumEvidenceType::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B96590 ?GetPrivateStaticClassAEnumInferenceType@AEnumInferenceType@@SAPAVUClass@@PBD@Z
UClass* AEnumInferenceType::GetPrivateStaticClassAEnumInferenceType(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AEnumInferenceType), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AEnumInferenceType")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AEnumInferenceType::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B96660 ?GetPrivateStaticClassANavMeshSubtractionVolume@ANavMeshSubtractionVolume@@SAPAVUClass@@PBD@Z
UClass* ANavMeshSubtractionVolume::GetPrivateStaticClassANavMeshSubtractionVolume(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ANavMeshSubtractionVolume), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("ANavMeshSubtractionVolume")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&ANavMeshSubtractionVolume::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B96730 ?GetPrivateStaticClassANavMeshInsertionPoint@ANavMeshInsertionPoint@@SAPAVUClass@@PBD@Z
UClass* ANavMeshInsertionPoint::GetPrivateStaticClassANavMeshInsertionPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ANavMeshInsertionPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("ANavMeshInsertionPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&ANavMeshInsertionPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B96800 ?GetPrivateStaticClassACitySectionPopulationInfo@ACitySectionPopulationInfo@@SAPAVUClass@@PBD@Z
UClass* ACitySectionPopulationInfo::GetPrivateStaticClassACitySectionPopulationInfo(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ACitySectionPopulationInfo), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("ACitySectionPopulationInfo")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&ACitySectionPopulationInfo::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B968D0 ?GetPrivateStaticClassACityPopPoint@ACityPopPoint@@SAPAVUClass@@PBD@Z
UClass* ACityPopPoint::GetPrivateStaticClassACityPopPoint(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(ACityPopPoint), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("ACityPopPoint")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&ACityPopPoint::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B969A0 ?InitializePrivateStaticClassAAISensoryModel@AAISensoryModel@@SAXXZ
void AAISensoryModel::InitializePrivateStaticClassAAISensoryModel()
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

// FUNCTION: 0x10B96AB0 ?InitializePrivateStaticClassAAIBehaviorModel@AAIBehaviorModel@@SAXXZ
void AAIBehaviorModel::InitializePrivateStaticClassAAIBehaviorModel()
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

// FUNCTION: 0x10B96BC0 ?InitializePrivateStaticClassAAIMovementModel@AAIMovementModel@@SAXXZ
void AAIMovementModel::InitializePrivateStaticClassAAIMovementModel()
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

// FUNCTION: 0x10B96CD0 ?InitializePrivateStaticClassAAICombatModel@AAICombatModel@@SAXXZ
void AAICombatModel::InitializePrivateStaticClassAAICombatModel()
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

// FUNCTION: 0x10B96DE0 ?InitializePrivateStaticClassAAIFactionModel@AAIFactionModel@@SAXXZ
void AAIFactionModel::InitializePrivateStaticClassAAIFactionModel()
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

// FUNCTION: 0x10B96EF0 ?InitializePrivateStaticClassAPatrolPoint@APatrolPoint@@SAXXZ
void APatrolPoint::InitializePrivateStaticClassAPatrolPoint()
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

// FUNCTION: 0x10B97000 ?InitializePrivateStaticClassAAddAIPoint@AAddAIPoint@@SAXXZ
void AAddAIPoint::InitializePrivateStaticClassAAddAIPoint()
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

// FUNCTION: 0x10B97110 ?InitializePrivateStaticClassAFormationPoint@AFormationPoint@@SAXXZ
void AFormationPoint::InitializePrivateStaticClassAFormationPoint()
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

// FUNCTION: 0x10B97220 ?InitializePrivateStaticClassAFormationPointAbsolute@AFormationPointAbsolute@@SAXXZ
void AFormationPointAbsolute::InitializePrivateStaticClassAFormationPointAbsolute()
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

// FUNCTION: 0x10B97330 ?InitializePrivateStaticClassAChangeDirectionPoint@AChangeDirectionPoint@@SAXXZ
void AChangeDirectionPoint::InitializePrivateStaticClassAChangeDirectionPoint()
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

// FUNCTION: 0x10B97440 ?InitializePrivateStaticClassALookPoint@ALookPoint@@SAXXZ
void ALookPoint::InitializePrivateStaticClassALookPoint()
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

// FUNCTION: 0x10B97550 ?InitializePrivateStaticClassAHeadTurnPoint@AHeadTurnPoint@@SAXXZ
void AHeadTurnPoint::InitializePrivateStaticClassAHeadTurnPoint()
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

// FUNCTION: 0x10B976B0 ??1AAIPawn@@UAE@XZ
AAIPawn::~AAIPawn()
{
    ConditionalDestroy();
}

// FUNCTION: 0x10B97700 ?InitializePrivateStaticClassAWanderPoint@AWanderPoint@@SAXXZ
void AWanderPoint::InitializePrivateStaticClassAWanderPoint()
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

// FUNCTION: 0x10B97810 ?InitializePrivateStaticClassAPlayAnimPoint@APlayAnimPoint@@SAXXZ
void APlayAnimPoint::InitializePrivateStaticClassAPlayAnimPoint()
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

// FUNCTION: 0x10B97920 ?InitializePrivateStaticClassAPlayBarkPoint@APlayBarkPoint@@SAXXZ
void APlayBarkPoint::InitializePrivateStaticClassAPlayBarkPoint()
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

// FUNCTION: 0x10B97A30 ?InitializePrivateStaticClassACityPopPoint@ACityPopPoint@@SAXXZ
void ACityPopPoint::InitializePrivateStaticClassACityPopPoint()
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

// FUNCTION: 0x10B97B50 ?GetPrivateStaticClassAAIPawn@AAIPawn@@SAPAVUClass@@PBD@Z
UClass* AAIPawn::GetPrivateStaticClassAAIPawn(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = ::new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AAIPawn), StaticClassFlags,
                                                      FGuid(0, 0, 0, 0), &TEXT("AAIPawn")[1], Package,
                                                      StaticConfigName(),
                                                      RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                      InternalConstructor,
                                                      (void (UObject::*)())&AAIPawn::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}
