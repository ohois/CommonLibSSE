#pragma once

#include "skse64/GameRTTI.h"  // RTTI_BSScript__Internal__VirtualMachine

#include "RE/BSScript/Internal/FunctionMessage.h"  // BSScript::Internal::FunctionMessage
#include "RE/BSScript/Internal/SuspendedStack.h"  // BSScript::Internal::SuspendedStack
#include "RE/BSScript/IVirtualMachine.h"  // BSScript::IVirtualMachine
#include "RE/BSScript/IVMDebugInterface.h"  // BSScript::IVMDebugInterface
#include "RE/BSScript/IVMObjectBindInterface.h"  // BSScript::IVMObjectBindInterface
#include "RE/BSScript/IVMSaveLoadInterface.h"  // BSScript::IVMSaveLoadInterface
#include "RE/BSScript/LinkerProcessor.h"  // BSScript::LinkerProcessor
#include "RE/BSScript/StatsEvent.h"  // BSScript::StatsEvent
#include "RE/BSSpinLock.h"  // BSSpinLock
#include "RE/BSTArray.h"  // BSTArray
#include "RE/BSTEvent.h"  // BSTEvent
#include "RE/BSTFreeList.h"  // BSTStaticFreeList
#include "RE/BSTHashMap.h"  // BSTHashMap
#include "RE/BSTMessageQueue.h"  // BSTCommonLLMessageQueue, BSTCommonStaticMessageQueue
#include "RE/BSTSmartPointer.h"  // BSTSmartPointer


namespace RE
{
	namespace BSScript
	{
		class Array;
		class ErrorLogger;
		class ISavePatcherInterface;
		class ObjectBindPolicy;
		class SimpleAllocMemoryPagePolicy;
		struct IObjectHandlePolicy;


		namespace Internal
		{
			class VirtualMachine :
				public IVirtualMachine,			// 0000
				public IVMObjectBindInterface,	// 0010
				public IVMSaveLoadInterface,	// 0018
				public IVMDebugInterface		// 0020
			{
			public:
				inline static const void* RTTI = RTTI_BSScript__Internal__VirtualMachine;


				virtual ~VirtualMachine();

				// override (IVirtualMachine)
				virtual void							Unk_01(void) override;																																														// 01
				virtual void							TraceStack(const char* a_str, UInt32 a_stackID, Severity a_severity = Severity::kInfo) override;																											// 02
				virtual void							Unk_03(void) override;																																														// 03
				virtual void							OnUpdate(float a_arg1) override;																																											// 04
				virtual void							OnUpdateGameTime(float a_arg1) override;																																									// 05
				virtual void							Unk_06(void) override;																																														// 06
				virtual bool							OnChangeVMState() override;																																													// 07
				virtual void							RegisterForm(UInt32 a_formType, const char* a_papyrusClassName) override;																																	// 08
				virtual bool							GetScriptClassByName(const BSFixedString& a_className, BSTSmartPointer<Class>& a_outClassPtr) override;																										// 09
				virtual bool							GetScriptClassByTypeID(UInt32 a_formType, BSTSmartPointer<Class>& a_outClass) override;																														// 0A
				virtual bool							RegisterScriptClass(const BSFixedString& a_className, BSTSmartPointer<Class>& a_classPtr) override;																											// 0B
				virtual void							Unk_0C(void) override;																																														// 0C
				virtual bool							GetFormTypeID(const BSFixedString& a_className, UInt32& a_formType) override;																																// 0D
				virtual void							Unk_0E(void) override;																																														// 0E
				virtual void							Unk_0F(void) override;																																														// 0F
				virtual void							Unk_10(void) override;																																														// 10
				virtual void							Unk_11(void) override;																																														// 11
				virtual void							Unk_12(void) override;																																														// 12
				virtual void							Unk_13(void) override;																																														// 13
				virtual bool							CreateScriptObjectWithProperty(const BSFixedString& a_className, void* a_property, BSTSmartPointer<Object>& a_objPtr) override;																				// 14
				virtual bool							CreateScriptObject(const BSFixedString& a_className, BSTSmartPointer<Object>& a_result) override;																											// 15
				virtual bool							CreateScriptArray(const Type& a_typeID, UInt32 a_size, BSTSmartPointer<Array>& a_arrayPtr) override;																										// 16
				virtual bool							CreateScriptArray2(VMTypeID a_typeID, const BSFixedString& a_className, UInt32 a_size, BSTSmartPointer<Array>& a_arrayPtr) override;																		// 17
				virtual void							RegisterFunction(IFunction* a_fn) override;																																									// 18
				virtual void							SetFunctionFlagsEx(const char* a_className, UInt32 a_arg2, const char* a_fnName, FunctionFlag a_flags) override;																							// 19
				virtual void							SetFunctionFlags(const char* a_className, const char* a_fnName, FunctionFlag a_flags) override;																												// 1A - { SetFunctionFlagsEx(a_className, 0, a_fnName, a_flags); }
				virtual void							VisitScripts(VMHandle a_handle, IForEachScriptObjectFunctor* a_functor) override;																															// 1B
				virtual bool							ResolveScriptObject(VMHandle a_handle, const char* a_className, BSTSmartPointer<Object>& a_result) override;																								// 1C
				virtual void							Unk_1D(void) override;																																														// 1D
				virtual void							Unk_1E(void) override;																																														// 1E
				virtual bool							CastScriptObject(const BSTSmartPointer<Object>& a_fromObjPtr, const BSTSmartPointer<Class>& a_toClassPtr, BSTSmartPointer<Object>& a_toObjPtr) override;													// 1F
				virtual bool							SetObjectProperty(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_setVal) override;																									// 20
				virtual bool							GetObjectProperty(BSTSmartPointer<Object>& a_obj, const char* a_propertyName, Variable& a_getVal) override;																									// 21
				virtual bool							ExtractValue(const BSTSmartPointer<Object>& a_objPtr, UInt32 a_index, Variable& a_out) override;																											// 22
				virtual bool							ExtractValueFromHandle(VMHandle a_handle, const BSFixedString& a_className, SInt32 a_variableIndex, Variable& a_out) override;																				// 23
				virtual void							QueueEvent(VMHandle a_handle, const BSFixedString& a_eventName, IFunctionArguments* a_args) override;																										// 24
				virtual bool							QueueEventAll(const BSFixedString& a_eventName, IFunctionArguments* a_args) override;																														// 25
				virtual bool							CallStaticFunction(const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) override;									// 26
				virtual bool							CallMemberFunction(BSTSmartPointer<Object>& a_obj, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) override;									// 27
				virtual bool							CallMemberFunctionFromHandle(VMHandle a_handle, const BSFixedString& a_className, const BSFixedString& a_fnName, IFunctionArguments* a_args, BSTSmartPointer<IStackCallbackFunctor>& a_result) override;	// 28
				virtual void							Unk_29(void) override;																																														// 29
				virtual bool							IsWaitingStack(UInt32 a_stackID) override;																																									// 2A
				virtual void							SetLatentReturn(UInt32 a_stackID, const Variable& a_val) override;																																			// 2B
				virtual ErrorLogger*					GetLogger() override;																																														// 2C - { return logger; }
				virtual SkyrimScript::HandlePolicy*		GetHandlePolicySK() override;																																												// 2D - { return objectHandlePolicy; }
				virtual IObjectHandlePolicy*			GetHandlePolicyBS() override;																																												// 2E - { return objectHandlePolicy; }
				virtual SkyrimScript::ObjectBindPolicy*	GetObjectBindPolicySK() override;																																											// 2F - { return objectBindPolicy; }
				virtual ObjectBindPolicy*				GetObjectBindPolicyBS() override;																																											// 30 - { return objectBindPolicy; }
				virtual ISavePatcherInterface*			GetSavePatcher() override;																																													// 31 - { return savePatcher; }
				virtual void							AddLogEventSink(BSTEventSink<LogEvent>* a_sink) override;																																					// 32
				virtual void							RemoveLogEventSink(BSTEventSink<LogEvent>* a_sink) override;																																				// 33
				virtual void							AddStatsEventSink(BSTEventSink<StatsEvent>* a_sink) override;																																				// 34
				virtual void							RemoveStatsEventSink(BSTEventSink<StatsEvent>* a_sink) override;																																			// 35

				// override (IVMObjectBindInterface)
				virtual VMHandle						GetHandle(const BSTSmartPointer<Object>& a_objPtr) override;																																				// 01
				virtual void							BindObject(BSTSmartPointer<Object>& a_objPtr, VMHandle a_handle, bool a_counditional) override;																												// 03
				virtual void							RegisterObject(BSTSmartPointer<Object>& a_objPtr, VMHandle a_handle, bool a_counditional) override;																											// 04
				virtual bool							CreateObject(const BSFixedString& a_className, UInt32 a_numProperties, BSTSmartPointer<Object>& a_objPtr) override;																							// 09
				virtual bool							SetProperty(BSTSmartPointer<Object>& a_objPtr, void* a_property, bool a_arg3) override;																														// 0A

				static VirtualMachine*					GetSingleton();

				bool									AllocateArray(const VMTypeID& a_typeID, std::size_t a_size, BSTSmartPointer<Array>& a_array);
				template <class F> void					RegisterFunction(const char* a_fnName, const char* a_className, F* a_callback, FunctionFlag a_flags = FunctionFlag::kNone);


				// members
				BSTEventSource<StatsEvent>							statsEventSource;	// 0028
				ErrorLogger*										logger;				// 0080
				SimpleAllocMemoryPagePolicy*						memoryPagePolicy;	// 0088
				IObjectHandlePolicy*								objectHandlePolicy;	// 0090
				ObjectBindPolicy*									objectBindPolicy;	// 0098
				UInt64												unk00A0;			// 00A0
				UInt64												unk00A8;			// 00A8
				UInt64												unk00B0;			// 00B0
				ISavePatcherInterface*								savePatcher;		// 00B8
				BSSpinLock											unk00C0;			// 00C0
				LinkerProcessor										linkerProcessor;	// 00C8
				BSTHashMap<UnkKey, UnkValue>						unk0158;			// 0158
				BSTHashMap<UnkKey, UnkValue>						unk0188;			// 0188
				BSTHashMap<UnkKey, UnkValue>						unk01B8;			// 01B8
				BSTArray<void*>										unk01E8;			// 01E8
				UInt64												unk0200;			// 0200
				BSTStaticFreeList<FunctionMessage, 1024>			unk0208;			// 0208
				BSTCommonLLMessageQueue<FunctionMessage>			unk8220;			// 8220
				BSTArray<void*>										unk8248;			// 8248
				BSTArray<void*>										unk8260;			// 8260
				UInt64												unk8278;			// 8278
				BSTCommonStaticMessageQueue<SuspendedStack, 128>	unk8280;			// 8280
				BSTCommonStaticMessageQueue<SuspendedStack, 128>	unk8AA0;			// 8AA0
				BSTArray<void*>										unk92C0;			// 92C0
				BSTArray<void*>										unk92D8;			// 92D8
				UInt64												unk92F0;			// 92F0
				void*												unk92F8;			// 92F8
				void*												unk9300;			// 9300
				void*												unk9308;			// 9308
				void*												unk9310;			// 9310
				BSSpinLock											stackLock;			// 9318
				BSTHashMap<UInt32, UnkValue>						allStacks;			// 9320
				BSTHashMap<UInt32, UnkValue>						waitingStacks;		// 9350
				UInt64												unk9380;			// 9380
				UInt64												unk9388;			// 9388
				UInt64												unk9390;			// 9390
				UInt64												unk9398;			// 9398
				UInt64												unk93A0;			// 93A0
				BSTHashMap<UnkKey, UnkValue>						unk93A8;			// 93A8
				UInt64												unk93D8;			// 93D8
				BSTArray<void*>										unk93E0;			// 93E0
				BSSpinLock											unk93F8;			// 93F8
				UInt64												unk9400;			// 9400
				BSTArray<void*>										unk9408;			// 9408
				UInt64												unk9420;			// 9420
				BSTArray<void*>										unk9428;			// 9428
				UInt64												unk9440;			// 9440
				BSTHashMap<UnkKey, UnkValue>						unk9448;			// 9448
				BSTHashMap<UnkKey, UnkValue>						unk9478;			// 9478
				UInt64												unk94A8;			// 94A8
				BSTArray<void*>										unk94B0;			// 94B0
				UInt64												unk94C8;			// 94C8
				UInt64												unk94D0;			// 94D0
				UInt64												unk94D8;			// 94D8
				UInt64												unk94E0;			// 94E0
				UInt64												unk94E8;			// 94E8
				UInt64												unk94F0;			// 94F0
				UInt64												unk94F8;			// 94F8
				UInt64												unk9500;			// 9500
				UInt64												unk9508;			// 9508
				UInt64												unk9518;			// 9510
			};
			STATIC_ASSERT(sizeof(VirtualMachine) == 0x9518);
		}
	}
}
