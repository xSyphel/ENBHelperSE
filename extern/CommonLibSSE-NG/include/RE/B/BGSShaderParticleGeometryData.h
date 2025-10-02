#pragma once

#include "RE/B/BSTArray.h"
#include "RE/F/FormTypes.h"
#include "RE/T/TESForm.h"
#include "RE/T/TESTexture.h"

namespace RE
{
	class BGSShaderParticleGeometryData : public TESForm
	{
	public:
		inline static constexpr auto RTTI = RTTI_BGSShaderParticleGeometryData;
		inline static constexpr auto VTABLE = VTABLE_BGSShaderParticleGeometryData;
		inline static constexpr auto FORMTYPE = FormType::ShaderParticleGeometryData;

		union SETTING_VALUE
		{
			float         f;
			std::uint32_t i;
		};
		static_assert(sizeof(SETTING_VALUE) == 0x4);

		struct SETTINGS_VALUE_VR
		{
			SETTING_VALUE value;
			std::uint8_t  pad[0x4];
		};
		static_assert(sizeof(SETTINGS_VALUE_VR) == 0x8);

		struct RUNTIME_DATA
		{
#define RUNTIME_DATA_CONTENT                                                          \
	BSTArray<SETTING_VALUE> data;            /* 20 - DATA - size == DataID::kTotal */ \
	TESTexture              particleTexture; /* 38 - ICON */
            RUNTIME_DATA_CONTENT
		};

		struct RUNTIME_DATA_VR
		{
#define RUNTIME_DATA_CONTENT_VR                                                           \
	BSTArray<SETTINGS_VALUE_VR> data;            /* 20 - DATA - size == DataID::kTotal */ \
	TESTexture                  particleTexture; /* 38 - ICON */
            RUNTIME_DATA_CONTENT_VR
		};

		enum class DataID
		{
			kGravityVelocity = 0,
			kRotationVelocity,
			kParticleSizeX,
			kParticleSizeY,
			kCenterOffsetMin,
			kCenterOffsetMax,
			kStartRotationRange,
			kNumSubtexturesX,
			kNumSubtexturesY,
			kParticleType,
			kBoxSize,
			kParticleDensity,

			kTotal
		};

		enum class ParticleType
		{
			kRain = 0,
			kSnow = 1
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};

		[[nodiscard]] inline RUNTIME_DATA& GetRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA>(this, 0x20, 0x20);
		}

		[[nodiscard]] inline RUNTIME_DATA_VR& GetVRRuntimeData() noexcept
		{
			return REL::RelocateMember<RUNTIME_DATA_VR>(this, 0x20, 0x20);
		}

		[[nodiscard]] SETTING_VALUE GetSettingValue(DataID id)
		{
			if (REL::Module::IsVR()) {
				return GetVRRuntimeData().data[(std::uint32_t)id].value;
			} else {
				return GetRuntimeData().data[(std::uint32_t)id];
			}
		}

		~BGSShaderParticleGeometryData() override;  // 00

		// override (TESForm)
		void InitializeData() override;      // 04
		void ClearData() override;           // 05
		bool Load(TESFile* a_mod) override;  // 06
		void InitItemImpl() override;        // 13

#if defined(EXCLUSIVE_SKYRIM_FLAT)
		RUNTIME_DATA_CONTENT;  // 20
#elif defined(EXCLUSIVE_SKYRIM_VR)
		RUNTIME_DATA_CONTENT_VR;  // 20
#endif
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT) || defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BGSShaderParticleGeometryData) == 0x48);
#else
	static_assert(sizeof(BGSShaderParticleGeometryData) == 0x20);
#endif
}

#undef RUNTIME_DATA_CONTENT
#undef RUNTIME_DATA_CONTENT_VR