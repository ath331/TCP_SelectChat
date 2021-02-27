// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CHAT_ChatPlayerController_generated_h
#error "ChatPlayerController.generated.h already included, missing '#pragma once' in ChatPlayerController.h"
#endif
#define CHAT_ChatPlayerController_generated_h

#define Chat_Source_Chat_ChatPlayerController_h_13_SPARSE_DATA
#define Chat_Source_Chat_ChatPlayerController_h_13_RPC_WRAPPERS
#define Chat_Source_Chat_ChatPlayerController_h_13_RPC_WRAPPERS_NO_PURE_DECLS
#define Chat_Source_Chat_ChatPlayerController_h_13_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAChatPlayerController(); \
	friend struct Z_Construct_UClass_AChatPlayerController_Statics; \
public: \
	DECLARE_CLASS(AChatPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Chat"), NO_API) \
	DECLARE_SERIALIZER(AChatPlayerController)


#define Chat_Source_Chat_ChatPlayerController_h_13_INCLASS \
private: \
	static void StaticRegisterNativesAChatPlayerController(); \
	friend struct Z_Construct_UClass_AChatPlayerController_Statics; \
public: \
	DECLARE_CLASS(AChatPlayerController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Chat"), NO_API) \
	DECLARE_SERIALIZER(AChatPlayerController)


#define Chat_Source_Chat_ChatPlayerController_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AChatPlayerController(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AChatPlayerController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AChatPlayerController); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChatPlayerController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AChatPlayerController(AChatPlayerController&&); \
	NO_API AChatPlayerController(const AChatPlayerController&); \
public:


#define Chat_Source_Chat_ChatPlayerController_h_13_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AChatPlayerController(AChatPlayerController&&); \
	NO_API AChatPlayerController(const AChatPlayerController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AChatPlayerController); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AChatPlayerController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AChatPlayerController)


#define Chat_Source_Chat_ChatPlayerController_h_13_PRIVATE_PROPERTY_OFFSET
#define Chat_Source_Chat_ChatPlayerController_h_10_PROLOG
#define Chat_Source_Chat_ChatPlayerController_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Chat_Source_Chat_ChatPlayerController_h_13_PRIVATE_PROPERTY_OFFSET \
	Chat_Source_Chat_ChatPlayerController_h_13_SPARSE_DATA \
	Chat_Source_Chat_ChatPlayerController_h_13_RPC_WRAPPERS \
	Chat_Source_Chat_ChatPlayerController_h_13_INCLASS \
	Chat_Source_Chat_ChatPlayerController_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Chat_Source_Chat_ChatPlayerController_h_13_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Chat_Source_Chat_ChatPlayerController_h_13_PRIVATE_PROPERTY_OFFSET \
	Chat_Source_Chat_ChatPlayerController_h_13_SPARSE_DATA \
	Chat_Source_Chat_ChatPlayerController_h_13_RPC_WRAPPERS_NO_PURE_DECLS \
	Chat_Source_Chat_ChatPlayerController_h_13_INCLASS_NO_PURE_DECLS \
	Chat_Source_Chat_ChatPlayerController_h_13_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CHAT_API UClass* StaticClass<class AChatPlayerController>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Chat_Source_Chat_ChatPlayerController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
