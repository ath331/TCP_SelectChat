// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CHAT_ChatGameModeBase_generated_h
#error "ChatGameModeBase.generated.h already included, missing '#pragma once' in ChatGameModeBase.h"
#endif
#define CHAT_ChatGameModeBase_generated_h

#define Chat_Source_Chat_ChatGameModeBase_h_15_SPARSE_DATA
#define Chat_Source_Chat_ChatGameModeBase_h_15_RPC_WRAPPERS
#define Chat_Source_Chat_ChatGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define Chat_Source_Chat_ChatGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAChatGameModeBase(); \
	friend struct Z_Construct_UClass_AChatGameModeBase_Statics; \
public: \
	DECLARE_CLASS(AChatGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Chat"), NO_API) \
	DECLARE_SERIALIZER(AChatGameModeBase)


#define Chat_Source_Chat_ChatGameModeBase_h_15_INCLASS \
private: \
	static void StaticRegisterNativesAChatGameModeBase(); \
	friend struct Z_Construct_UClass_AChatGameModeBase_Statics; \
public: \
	DECLARE_CLASS(AChatGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Chat"), NO_API) \
	DECLARE_SERIALIZER(AChatGameModeBase)


#define Chat_Source_Chat_ChatGameModeBase_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AChatGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AChatGameModeBase) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AChatGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChatGameModeBase); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AChatGameModeBase(AChatGameModeBase&&); \
	NO_API AChatGameModeBase(const AChatGameModeBase&); \
public:


#define Chat_Source_Chat_ChatGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AChatGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AChatGameModeBase(AChatGameModeBase&&); \
	NO_API AChatGameModeBase(const AChatGameModeBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AChatGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChatGameModeBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AChatGameModeBase)


#define Chat_Source_Chat_ChatGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET
#define Chat_Source_Chat_ChatGameModeBase_h_12_PROLOG
#define Chat_Source_Chat_ChatGameModeBase_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Chat_Source_Chat_ChatGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	Chat_Source_Chat_ChatGameModeBase_h_15_SPARSE_DATA \
	Chat_Source_Chat_ChatGameModeBase_h_15_RPC_WRAPPERS \
	Chat_Source_Chat_ChatGameModeBase_h_15_INCLASS \
	Chat_Source_Chat_ChatGameModeBase_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Chat_Source_Chat_ChatGameModeBase_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Chat_Source_Chat_ChatGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	Chat_Source_Chat_ChatGameModeBase_h_15_SPARSE_DATA \
	Chat_Source_Chat_ChatGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	Chat_Source_Chat_ChatGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
	Chat_Source_Chat_ChatGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CHAT_API UClass* StaticClass<class AChatGameModeBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Chat_Source_Chat_ChatGameModeBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
