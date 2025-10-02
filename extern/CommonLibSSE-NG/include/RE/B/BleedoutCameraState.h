#pragma once

#include "RE/B/BSSoundHandle.h"
#include "RE/N/NiMatrix3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/T/ThirdPersonState.h"

#include "REL/Common.h"

namespace RE
{
	class NiAVObject;

	class BleedoutCameraState : public ThirdPersonState
	{
	public:
		inline static constexpr auto RTTI = RTTI_BleedoutCameraState;
		inline static constexpr auto VTABLE = VTABLE_BleedoutCameraState;

		~BleedoutCameraState() override;  // 00

		// override (ThirdPersonState)
		void Begin() override;  // 01
		void End() override;    // 02
#if defined(EXCLUSIVE_SKYRIM_FLAT)
		// Function doesn't exist in SE/AE-only builds
#elif defined(EXCLUSIVE_SKYRIM_VR)
		void Unk_03() override;  // 03 - VR only
#else
		void Unk_03();  // 03 - Multi-runtime
#endif
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override;  // 03/04

		// members
		NiMatrix3             rotationMtx;        // 0E8
		float                 zoom;               // 10C
		float                 pitch;              // 110
		float                 yaw;                // 114
		float                 randHeading;        // 118
		std::uint32_t         pad11C;             // 11C
		NiPointer<NiAVObject> animatedBone;       // 120
		BSSoundHandle         activeSound;        // 128
		bool                  useCurrentHeading;  // 134
		std::uint8_t          pad135;             // 135
		std::uint16_t         pad136;             // 136
	private:
		KEEP_FOR_RE()
	};
#if defined(EXCLUSIVE_SKYRIM_FLAT)
	static_assert(sizeof(BleedoutCameraState) == 0x138);
#elif defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(BleedoutCameraState) == 0x150);
#else
	static_assert(sizeof(BleedoutCameraState) == 0x138);
#endif
}
