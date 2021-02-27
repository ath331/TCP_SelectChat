// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Chat/ClientSocket.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeClientSocket() {}
// Cross Module References
	CHAT_API UClass* Z_Construct_UClass_AClientSocket_NoRegister();
	CHAT_API UClass* Z_Construct_UClass_AClientSocket();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_Chat();
// End Cross Module References
	void AClientSocket::StaticRegisterNativesAClientSocket()
	{
	}
	UClass* Z_Construct_UClass_AClientSocket_NoRegister()
	{
		return AClientSocket::StaticClass();
	}
	struct Z_Construct_UClass_AClientSocket_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AClientSocket_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_Chat,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AClientSocket_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "ClientSocket.h" },
		{ "ModuleRelativePath", "ClientSocket.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AClientSocket_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AClientSocket>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AClientSocket_Statics::ClassParams = {
		&AClientSocket::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AClientSocket_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AClientSocket_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AClientSocket()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AClientSocket_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AClientSocket, 1999578646);
	template<> CHAT_API UClass* StaticClass<AClientSocket>()
	{
		return AClientSocket::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AClientSocket(Z_Construct_UClass_AClientSocket, &AClientSocket::StaticClass, TEXT("/Script/Chat"), TEXT("AClientSocket"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AClientSocket);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
