// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
struct FKey;
#ifdef CHAT_ChatBlock_generated_h
#error "ChatBlock.generated.h already included, missing '#pragma once' in ChatBlock.h"
#endif
#define CHAT_ChatBlock_generated_h

#define Chat_Source_Chat_ChatBlock_h_13_SPARSE_DATA
#define Chat_Source_Chat_ChatBlock_h_13_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnFingerPressedBlock); \
	DECLARE_FUNCTION(execBlockClicked);


#define Chat_Source_Chat_ChatBlock_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnFingerPressedBlock); \
	DECLARE_FUNCTION(execBlockClicked);


#define Chat_Source_Chat_ChatBlock_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAChatBlock(); \
	friend struct Z_Construct_UClass_AChatBlock_Statics; \
public: \
	DECLARE_CLASS(AChatBlock, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Chat"), CHAT_API) \
	DECLARE_SERIALIZER(AChatBlock)


#define Chat_Source_Chat_ChatBlock_h_13_INCLASS \
private: \
	static void StaticRegisterNativesAChatBlock(); \
	friend struct Z_Construct_UClass_AChatBlock_Statics; \
public: \
	DECLARE_CLASS(AChatBlock, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Chat"), CHAT_API) \
	DECLARE_SERIALIZER(AChatBlock)


#define Chat_Source_Chat_ChatBlock_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	CHAT_API AChatBlock(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AChatBlock) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(CHAT_API, AChatBlock); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChatBlock); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	CHAT_API AChatBlock(AChatBlock&&); \
	CHAT_API AChatBlock(const AChatBlock&); \
public:


#define Chat_Source_Chat_ChatBlock_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	CHAT_API AChatBlock(AChatBlock&&); \
	CHAT_API AChatBlock(const AChatBlock&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(CHAT_API, AChatBlock); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChatBlock); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AChatBlock)


#define Chat_Source_Chat_ChatBlock_h_13_PRIVATE_PROPERTY_OFFSET \
	FORCEINLINE static uint32 __PPO__DummyRoot() { return STRUCT_OFFSET(AChatBlock, DummyRoot); } \
	FORCEINLINE static uint32 __PPO__BlockMesh() { return STRUCT_OFFSET(AChatBlock, BlockMesh); }


#define Chat_Source_Chat_ChatBlock_h_10_PROLOG
#define Chat_Source_Chat_ChatBlock_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Chat_Source_Chat_ChatBlock_h_13_PRIVATE_PROPERTY_OFFSET \
	Chat_Source_Chat_ChatBlock_h_13_SPARSE_DATA \
	Chat_Source_Chat_ChatBlock_h_13_RPC_WRAPPERS \
	Chat_Source_Chat_ChatBlock_h_13_INCLASS \
	Chat_Source_Chat_ChatBlock_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Chat_Source_Chat_ChatBlock_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Chat_Source_Chat_ChatBlock_h_13_PRIVATE_PROPERTY_OFFSET \
	Chat_Source_Chat_ChatBlock_h_13_SPARSE_DATA \
	Chat_Source_Chat_ChatBlock_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	Chat_Source_Chat_ChatBlock_h_13_INCLASS_NO_PURE_DECLS \
	Chat_Source_Chat_ChatBlock_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CHAT_API UClass* StaticClass<class AChatBlock>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Chat_Source_Chat_ChatBlock_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
