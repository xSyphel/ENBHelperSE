#pragma once

#include "RE/B/BSString.h"
#include "RE/H/HUDMessageTypes.h"
#include "RE/I/IUIMessageData.h"

namespace RE
{
	class TESQuest;
	class TESWordOfPower;

	class HUDData : public IUIMessageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_HUDData;
		inline static constexpr auto VTABLE = VTABLE_HUDData;

		~HUDData() override;  // 00

		// members
		REX::EnumSet<HUD_MESSAGE_TYPE, std::uint32_t> type;          // 10
		std::uint32_t                                 pad14;         // 14
		BSString                                      text;          // 18
		ObjectRefHandle                               crosshairRef;  // 28
		std::uint32_t                                 pad2C;         // 2C
		TESQuest*                                     quest;         // 30
		TESWordOfPower*                               wordOfPower;   // 38
		bool                                          show;          // 40
		std::uint8_t                                  pad41;         // 41
		std::uint16_t                                 pad42;         // 42
		REX::EnumSet<MARKER_TYPE, std::uint32_t>      discovery;     // 44
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(HUDData) == 0x48);
}
