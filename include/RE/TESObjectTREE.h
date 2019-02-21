#pragma once

#include "RE/FormTypes.h"  // FormType
#include "RE/TESBoundObject.h"  // TESBoundObject
#include "RE/TESFullName.h"  // TESFullName
#include "RE/TESModel.h"  // TESModel
#include "RE/TESProduceForm.h"  // TESProduceForm


namespace RE
{
	class TESObjectTREE :
		public TESBoundObject,	// 00
		public TESModel,		// 30
		public TESFullName,		// 58
		public TESProduceForm	// 68
	{
	public:
		enum { kTypeID = FormType::Tree };


		struct LocalFlags
		{
			enum LocalFlag : UInt32
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kHasDistantLOD = 1 << 15
			};
		};


		struct Data	// CNAM
		{
			float	trunkFlexibility;	// 00
			float	branchFlexibility;	// 04
			float	unk08;				// 08
			float	unk0C;				// 0C
			float	unk10;				// 10
			float	unk14;				// 14
			float	unk18;				// 18
			float	unk1C;				// 1C
			float	unk20;				// 20
			float	unk24;				// 24
			float	leafAmplitude;		// 28
			float	leafFrequency;		// 2C
		};
		STATIC_ASSERT(sizeof(Data) == 0x30);


		virtual ~TESObjectTREE();																															// 00

		// override (TESBoundObject)
		virtual void	InitDefaults() override;																											// 04
		virtual bool	LoadForm(TESFile* a_mod) override;																									// 06
		virtual void	InitItem() override;																												// 13
		virtual bool	ActivateReference(TESObjectREFR* a_targetRef, TESObjectREFR* a_activatorRef, UInt8 a_arg3, UInt64 a_arg4, UInt32 a_arg5) override;	// 37
		virtual bool	GetCrosshairText(TESObjectREFR* a_ref, BSString* a_dst) override;																	// 4C


		// members
		Data	data;	// 88
		UInt64	unkB8;	// B8
		UInt64	unkC0;	// C0
	};
	STATIC_ASSERT(sizeof(TESObjectTREE) == 0xC8);
}