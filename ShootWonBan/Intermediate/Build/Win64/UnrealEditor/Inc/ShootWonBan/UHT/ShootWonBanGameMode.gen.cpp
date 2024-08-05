// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ShootWonBan/ShootWonBanGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeShootWonBanGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
SHOOTWONBAN_API UClass* Z_Construct_UClass_AShootWonBanGameMode();
SHOOTWONBAN_API UClass* Z_Construct_UClass_AShootWonBanGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_ShootWonBan();
// End Cross Module References

// Begin Class AShootWonBanGameMode
void AShootWonBanGameMode::StaticRegisterNativesAShootWonBanGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AShootWonBanGameMode);
UClass* Z_Construct_UClass_AShootWonBanGameMode_NoRegister()
{
	return AShootWonBanGameMode::StaticClass();
}
struct Z_Construct_UClass_AShootWonBanGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "ShootWonBanGameMode.h" },
		{ "ModuleRelativePath", "ShootWonBanGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AShootWonBanGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AShootWonBanGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_ShootWonBan,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AShootWonBanGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AShootWonBanGameMode_Statics::ClassParams = {
	&AShootWonBanGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AShootWonBanGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AShootWonBanGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AShootWonBanGameMode()
{
	if (!Z_Registration_Info_UClass_AShootWonBanGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AShootWonBanGameMode.OuterSingleton, Z_Construct_UClass_AShootWonBanGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AShootWonBanGameMode.OuterSingleton;
}
template<> SHOOTWONBAN_API UClass* StaticClass<AShootWonBanGameMode>()
{
	return AShootWonBanGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AShootWonBanGameMode);
AShootWonBanGameMode::~AShootWonBanGameMode() {}
// End Class AShootWonBanGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_ShootWonBan_Source_ShootWonBan_ShootWonBanGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AShootWonBanGameMode, AShootWonBanGameMode::StaticClass, TEXT("AShootWonBanGameMode"), &Z_Registration_Info_UClass_AShootWonBanGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AShootWonBanGameMode), 1180729514U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_ShootWonBan_Source_ShootWonBan_ShootWonBanGameMode_h_458176017(TEXT("/Script/ShootWonBan"),
	Z_CompiledInDeferFile_FID_ShootWonBan_Source_ShootWonBan_ShootWonBanGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_ShootWonBan_Source_ShootWonBan_ShootWonBanGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
