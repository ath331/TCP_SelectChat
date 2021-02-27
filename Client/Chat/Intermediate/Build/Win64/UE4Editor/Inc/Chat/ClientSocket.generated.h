// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef CHAT_ClientSocket_generated_h
#error "ClientSocket.generated.h already included, missing '#pragma once' in ClientSocket.h"
#endif
#define CHAT_ClientSocket_generated_h

#define Chat_Source_Chat_ClientSocket_h_16_SPARSE_DATA
#define Chat_Source_Chat_ClientSocket_h_16_RPC_WRAPPERS
#define Chat_Source_Chat_ClientSocket_h_16_RPC_WRAPPERS_NO_PURE_DECLS
#define Chat_Source_Chat_ClientSocket_h_16_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAClientSocket(); \
	friend struct Z_Construct_UClass_AClientSocket_Statics; \
public: \
	DECLARE_CLASS(AClientSocket, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Chat"), NO_API) \
	DECLARE_SERIALIZER(AClientSocket)


#define Chat_Source_Chat_ClientSocket_h_16_INCLASS \
private: \
	static void StaticRegisterNativesAClientSocket(); \
	friend struct Z_Construct_UClass_AClientSocket_Statics; \
public: \
	DECLARE_CLASS(AClientSocket, AActor, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/Chat"), NO_API) \
	DECLARE_SERIALIZER(AClientSocket)


#define Chat_Source_Chat_ClientSocket_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API AClientSocket(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(AClientSocket) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AClientSocket); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AClientSocket); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AClientSocket(AClientSocket&&); \
	NO_API AClientSocket(const AClientSocket&); \
public:


#define Chat_Source_Chat_ClientSocket_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API AClientSocket(AClientSocket&&); \
	NO_API AClientSocket(const AClientSocket&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, AClientSocket); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(AClientSocket); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(AClientSocket)


#define Chat_Source_Chat_ClientSocket_h_16_PRIVATE_PROPERTY_OFFSET
#define Chat_Source_Chat_ClientSocket_h_13_PROLOG
#define Chat_Source_Chat_ClientSocket_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Chat_Source_Chat_ClientSocket_h_16_PRIVATE_PROPERTY_OFFSET \
	Chat_Source_Chat_ClientSocket_h_16_SPARSE_DATA \
	Chat_Source_Chat_ClientSocket_h_16_RPC_WRAPPERS \
	Chat_Source_Chat_ClientSocket_h_16_INCLASS \
	Chat_Source_Chat_ClientSocket_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Chat_Source_Chat_ClientSocket_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Chat_Source_Chat_ClientSocket_h_16_PRIVATE_PROPERTY_OFFSET \
	Chat_Source_Chat_ClientSocket_h_16_SPARSE_DATA \
	Chat_Source_Chat_ClientSocket_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	Chat_Source_Chat_ClientSocket_h_16_INCLASS_NO_PURE_DECLS \
	Chat_Source_Chat_ClientSocket_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> CHAT_API UClass* StaticClass<class AClientSocket>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Chat_Source_Chat_ClientSocket_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
