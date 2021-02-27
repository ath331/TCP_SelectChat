// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CHAT_ChatGameMode_generated_h
#error "ChatGameMode.generated.h already included, missing '#pragma once' in ChatGameMode.h"
#endif
#define CHAT_ChatGameMode_generated_h

#define Chat_Source_Chat_ChatGameMode_h_13_SPARSE_DATA
#define Chat_Source_Chat_ChatGameMode_h_13_RPC_WRAPPERS
#define Chat_Source_Chat_ChatGameMode_h_13_RPC_WRAPPERS_NO_PURE_DECLS
#define Chat_Source_Chat_ChatGameMode_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAChatGameMode(); \
	friend struct Z_Construct_UClass_AChatGameMode_Statics; \
public: \
	DECLARE_CLASS(AChatGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Chat"), CHAT_API) \
	DECLARE_SERIALIZER(AChatGameMode)


#define Chat_Source_Chat_ChatGameMode_h_13_INCLASS \
private: \
	static void StaticRegisterNativesAChatGameMode(); \
	friend struct Z_Construct_UClass_AChatGameMode_Statics; \
public: \
	DECLARE_CLASS(AChatGameMode, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient | CLASS_Config), CASTCLASS_None, TEXT("/Script/Chat"), CHAT_API) \
	DECLARE_SERIALIZER(AChatGameMode)


#define Chat_Source_Chat_ChatGameMode_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	CHAT_API AChatGameMode(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AChatGameMode) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(CHAT_API, AChatGameMode); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChatGameMode); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	CHAT_API AChatGameMode(AChatGameMode&&); \
	CHAT_API AChatGameMode(const AChatGameMode&); \
public:


#define Chat_Source_Chat_ChatGameMode_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	CHAT_API AChatGameMode(AChatGameMode&&); \
	CHAT_API AChatGameMode(const AChatGameMode&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(CHAT_API, AChatGameMode); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChatGameMode); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AChatGameMode)


#define Chat_Source_Chat_ChatGameMode_h_13_PRIVATE_PROPERTY_OFFSET
#define Chat_Source_Chat_ChatGameMode_h_10_PROLOG
#define Chat_Source_Chat_ChatGameMode_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Chat_Source_Chat_ChatGameMode_h_13_PRIVATE_PROPERTY_OFFSET \
	Chat_Source_Chat_ChatGameMode_h_13_SPARSE_DATA \
	Chat_Source_Chat_ChatGameMode_h_13_RPC_WRAPPERS \
	Chat_Source_Chat_ChatGameMode_h_13_INCLASS \
	Chat_Source_Chat_ChatGameMode_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Chat_Source_Chat_ChatGameMode_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Chat_Source_Chat_ChatGameMode_h_13_PRIVATE_PROPERTY_OFFSET \
	Chat_Source_Chat_ChatGameMode_h_13_SPARSE_DATA \
	Chat_Source_Chat_ChatGameMode_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	Chat_Source_Chat_ChatGameMode_h_13_INCLASS_NO_PURE_DECLS \
	Chat_Source_Chat_ChatGameMode_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CHAT_API UClass* StaticClass<class AChatGameMode>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Chat_Source_Chat_ChatGameMode_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
