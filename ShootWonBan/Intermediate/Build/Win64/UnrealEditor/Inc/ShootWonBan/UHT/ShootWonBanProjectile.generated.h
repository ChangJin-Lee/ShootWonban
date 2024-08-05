// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ShootWonBanProjectile.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
class UPrimitiveComponent;
struct FHitResult;
#ifdef SHOOTWONBAN_ShootWonBanProjectile_generated_h
#error "ShootWonBanProjectile.generated.h already included, missing '#pragma once' in ShootWonBanProjectile.h"
#endif
#define SHOOTWONBAN_ShootWonBanProjectile_generated_h

#define FID_ShootWonBan_Source_ShootWonBan_ShootWonBanProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execOnHit);


#define FID_ShootWonBan_Source_ShootWonBan_ShootWonBanProjectile_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAShootWonBanProjectile(); \
	friend struct Z_Construct_UClass_AShootWonBanProjectile_Statics; \
public: \
	DECLARE_CLASS(AShootWonBanProjectile, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/ShootWonBan"), NO_API) \
	DECLARE_SERIALIZER(AShootWonBanProjectile) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_ShootWonBan_Source_ShootWonBan_ShootWonBanProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	AShootWonBanProjectile(AShootWonBanProjectile&&); \
	AShootWonBanProjectile(const AShootWonBanProjectile&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AShootWonBanProjectile); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AShootWonBanProjectile); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AShootWonBanProjectile) \
	NO_API virtual ~AShootWonBanProjectile();


#define FID_ShootWonBan_Source_ShootWonBan_ShootWonBanProjectile_h_12_PROLOG
#define FID_ShootWonBan_Source_ShootWonBan_ShootWonBanProjectile_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_ShootWonBan_Source_ShootWonBan_ShootWonBanProjectile_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_ShootWonBan_Source_ShootWonBan_ShootWonBanProjectile_h_15_INCLASS_NO_PURE_DECLS \
	FID_ShootWonBan_Source_ShootWonBan_ShootWonBanProjectile_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SHOOTWONBAN_API UClass* StaticClass<class AShootWonBanProjectile>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_ShootWonBan_Source_ShootWonBan_ShootWonBanProjectile_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
