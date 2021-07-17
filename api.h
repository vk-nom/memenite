#pragma once
#define RVA(addr, size) ((uintptr_t)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))


bool IsValidPointer(uintptr_t address) {
	if (!IsBadWritePtr((LPVOID)address, (UINT_PTR)8)) return TRUE;
	else return false;
}

template<typename ReadT>
ReadT read(uintptr_t address, const ReadT& def = ReadT()) {
	if (IsValidPointer(address)) {
		return *(ReadT*)address;
	}
}

template<typename WriteT>
WriteT write(uintptr_t address, WriteT value, const WriteT& def = WriteT()) {
	if (IsValidPointer(address)) {
		*(WriteT*)((PBYTE)address) = value;
	}
	return 1;
}

class UClass {
public:
	BYTE _padding_0[0x40];
	UClass* SuperClass;
};

class UObject {
public:
	PVOID VTableObject;
	DWORD ObjectFlags;
	DWORD InternalIndex;
	UClass* Class;
	BYTE _padding_0[0x8];
	UObject* Outer;
	/*
	inline void ProcessEvent(void* fn, void* parms)
	{
		auto vtable = *reinterpret_cast<void***>(this);
		auto processEventFn = static_cast<void(*)(void*, void*, void*)>(vtable[0x44]);
		processEventFn(this, fn, parms);
	}
	*/
	inline BOOLEAN IsA(PVOID parentClass) {
		for (auto super = this->Class; super; super = super->SuperClass) {
			if (super == parentClass) {
				return TRUE;
			}
		}

		return FALSE;
	}
};

class FUObjectItem {
public:
	UObject* Object;
	DWORD Flags;
	DWORD ClusterIndex;
	DWORD SerialNumber;
	DWORD SerialNumber2;
};

class TUObjectArray {
public:
	FUObjectItem* Objects[9];
};

class GObjects {
public:
	TUObjectArray* ObjectArray;
	BYTE _padding_0[0xC];
	DWORD ObjectCount;
};

GObjects* objects = nullptr;
bool once = false;
namespace Framework {
	namespace Structs {


		struct FMatrix
		{
			float M[4][4];
		};
		static FMatrix* myMatrix = new FMatrix();


		template<class T>
		struct TArray
		{
			friend struct FString;

		public:
			inline TArray()
			{
				Data = nullptr;
				Count = Max = 0;
			};

			inline int Num() const
			{
				return Count;
			};

			inline T& operator[](int i)
			{
				return Data[i];
			};

			inline const T& operator[](int i) const
			{
				return Data[i];
			};

			inline bool IsValidIndex(int i) const
			{
				return i < Num();
			}

		private:
			T* Data;
			int32_t Count;
			int32_t Max;
		};

		struct FString : private TArray<wchar_t>
		{
			inline FString()
			{
			};

			FString(const wchar_t* other)
			{
				Max = Count = *other ? std::wcslen(other) + 1 : 0;

				if (Count)
				{
					Data = const_cast<wchar_t*>(other);
				}
			};

			inline bool IsValid() const
			{
				return Data != nullptr;
			}

			inline const wchar_t* c_str() const
			{
				return Data;
			}

			std::string ToString() const
			{
				auto length = std::wcslen(Data);
				std::string str(length, '\0');
				std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);
				return str;
			}
		};
	}
	namespace Objects {

		static void FreeObjectName(__int64 address) {
			auto func = reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(FreeFn);
			SpoofCall(func, address);
		}

		static const char* GetUintObjectName(uintptr_t Object)
		{
			if (Object == NULL) return "";

			auto fGetObjName = reinterpret_cast<Structs::FString * (__fastcall*)(int* index, Structs::FString * res)>(GetNameByIndex);

			int index = *(int*)(Object + 0x18);

			Structs::FString result;
			SpoofCall(fGetObjName, &index, &result);

			if (result.c_str() == NULL) return "";

			auto result_str = result.ToString();

			if (result.c_str() != NULL)
				FreeObjectName((__int64)result.c_str());

			return result_str.c_str();
		}


		static const char* GetUObjectName(UObject* Object)
		{
			if (Object == NULL) return "";

			auto fGetObjName = reinterpret_cast<Structs::FString * (__fastcall*)(int* index, Structs::FString * res)>(GetNameByIndex);

			int index = *(int*)(reinterpret_cast<uint64_t>(Object) + 0x18);

			Structs::FString result;
			SpoofCall(fGetObjName, &index, &result);

			if (result.c_str() == NULL) return "";

			auto result_str = result.ToString();

			if (result.c_str() != NULL)
				FreeObjectName((__int64)result.c_str());

			return result_str.c_str();
		}


		static const char* GetUObjectNameLoop(UObject* Object) {
			std::string name("");
			for (auto i = 0; Object; Object = Object->Outer, ++i) {

				auto fGetObjName = reinterpret_cast<Structs::FString * (__fastcall*)(int* index, Structs::FString * res)>(GetNameByIndex);

				int index = *(int*)(reinterpret_cast<uint64_t>(Object) + 0x18);

				Structs::FString fObjectName;
				SpoofCall(fGetObjName, &index, &fObjectName);

				if (!fObjectName.IsValid()) {
					break;
				}

				auto objectName = fObjectName.ToString();


				name = objectName + std::string(i > 0 ? "." : "") + name;
				FreeObjectName((uintptr_t)fObjectName.c_str());
			}

			return name.c_str();
		}

		PVOID FindObject(std::string name) {
			bool once = false;
			if (!once)
			{
				auto UObjectPtr = MemoryHelper::PatternScan(signatures::Gobject_Sig);
				objects = decltype(objects)(RVA(UObjectPtr, 7));
				//std::cout << "obj  " << std::hex << objects << "\n";
				//std::cout << "base  " << std::hex << GetModuleHandleA(0) << "\n";

				once = true;
			}
			for (auto array : objects->ObjectArray->Objects) {
				auto fuObject = array;
				//Sleep(1);
				for (auto i = 0; i < 0x10000 && fuObject->Object; ++i, ++fuObject) {
					//Sleep(1);
					auto object = fuObject->Object;
					if (object->ObjectFlags != 0x41) {}
					else {
						std::cout << "";
						if (strstr(GetUObjectNameLoop(object), name.c_str())) return object;
					}

					//log << GetUObjectName(object) << "\n";
				}
			}
			return 0;
		}

	}

}