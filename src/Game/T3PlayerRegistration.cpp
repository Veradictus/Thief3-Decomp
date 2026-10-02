// Game/T3PlayerRegistration.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "T3Player/T3PlayerClasses.h"

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

// FUNCTION: 0x10B12250 ?InitializePrivateStaticClassUT3GameEngine@UT3GameEngine@@SAXXZ
void UT3GameEngine::InitializePrivateStaticClassUT3GameEngine()
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

// FUNCTION: 0x10B12360 ?InitializePrivateStaticClassAGarrett@AGarrett@@SAXXZ
void AGarrett::InitializePrivateStaticClassAGarrett()
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

// FUNCTION: 0x10B12470 ?InitializePrivateStaticClassUAttachment_LinkDataObject@UAttachment_LinkDataObject@@SAXXZ
void UAttachment_LinkDataObject::InitializePrivateStaticClassUAttachment_LinkDataObject()
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

// FUNCTION: 0x10B12580 ?InitializePrivateStaticClassUInvenBook_LinkDataObject@UInvenBook_LinkDataObject@@SAXXZ
void UInvenBook_LinkDataObject::InitializePrivateStaticClassUInvenBook_LinkDataObject()
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

// FUNCTION: 0x10B12690 ?InitializePrivateStaticClassUHUDRenderLinkDataObject@UHUDRenderLinkDataObject@@SAXXZ
void UHUDRenderLinkDataObject::InitializePrivateStaticClassUHUDRenderLinkDataObject()
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

// FUNCTION: 0x10B127A0 ?InitializePrivateStaticClassUGarrettEquipLinkDataObject@UGarrettEquipLinkDataObject@@SAXXZ
void UGarrettEquipLinkDataObject::InitializePrivateStaticClassUGarrettEquipLinkDataObject()
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

// FUNCTION: 0x10B128B0 ?InitializePrivateStaticClassAT3PlayerController@AT3PlayerController@@SAXXZ
void AT3PlayerController::InitializePrivateStaticClassAT3PlayerController()
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

// FUNCTION: 0x10B12C50 ?GetPrivateStaticClassAT3PlayerController@AT3PlayerController@@SAPAVUClass@@PBD@Z
UClass* AT3PlayerController::GetPrivateStaticClassAT3PlayerController(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AT3PlayerController), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AT3PlayerController")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AT3PlayerController::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B12E20 ?GetPrivateStaticClassUAttachment_LinkDataObject@UAttachment_LinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UAttachment_LinkDataObject::GetPrivateStaticClassUAttachment_LinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UAttachment_LinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UAttachment_LinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UAttachment_LinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B12EE0 ?GetPrivateStaticClassUInvenBook_LinkDataObject@UInvenBook_LinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UInvenBook_LinkDataObject::GetPrivateStaticClassUInvenBook_LinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UInvenBook_LinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UInvenBook_LinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UInvenBook_LinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B12FA0 ?GetPrivateStaticClassUHUDRenderLinkDataObject@UHUDRenderLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UHUDRenderLinkDataObject::GetPrivateStaticClassUHUDRenderLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UHUDRenderLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UHUDRenderLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UHUDRenderLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B13060 ?GetPrivateStaticClassUGarrettEquipLinkDataObject@UGarrettEquipLinkDataObject@@SAPAVUClass@@PBD@Z
UClass* UGarrettEquipLinkDataObject::GetPrivateStaticClassUGarrettEquipLinkDataObject(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UGarrettEquipLinkDataObject), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UGarrettEquipLinkDataObject")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UGarrettEquipLinkDataObject::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B13560 ?GetPrivateStaticClassAGarrett@AGarrett@@SAPAVUClass@@PBD@Z
UClass* AGarrett::GetPrivateStaticClassAGarrett(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(AGarrett), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("AGarrett")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&AGarrett::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B136F0 ?GetPrivateStaticClassUT3GameEngine@UT3GameEngine@@SAPAVUClass@@PBD@Z
UClass* UT3GameEngine::GetPrivateStaticClassUT3GameEngine(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UT3GameEngine), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UT3GameEngine")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UT3GameEngine::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}

// FUNCTION: 0x10B13920 ?InitializePrivateStaticClassUT3Game@UT3Game@@SAXXZ
void UT3Game::InitializePrivateStaticClassUT3Game()
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

// FUNCTION: 0x10B15380 ?GetPrivateStaticClassUT3Game@UT3Game@@SAPAVUClass@@PBD@Z
UClass* UT3Game::GetPrivateStaticClassUT3Game(const TCHAR* Package)
{
    FUN_10905aa0()->Virtual8(0, 0);
    UClass* ReturnClass = new(0, 0, 0, 0, 0) UClass(EC_StaticConstructor, sizeof(UT3Game), StaticClassFlags,
                                                    FGuid(0, 0, 0, 0), &TEXT("UT3Game")[1], Package,
                                                    StaticConfigName(),
                                                    RF_Public | RF_Standalone | RF_Transient | RF_Native,
                                                    InternalConstructor,
                                                    (void (UObject::*)())&UT3Game::StaticConstructor);
    FUN_10905aa0()->Virtual9();
    return ReturnClass;
}
