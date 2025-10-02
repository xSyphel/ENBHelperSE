#pragma once
#ifdef ENABLE_SKYRIM_VR
#	include "RE/I/IMenu.h"
#	include "RE/M/MenuEventHandler.h"

namespace RE
{
	class CalibrationOptionMenu :
		public IMenu,            // 00
		public MenuEventHandler  // 40
	{
	public:
		inline static constexpr auto RTTI = RTTI_CalibrationOptionMenu;

		using MenuEventHandler::operator delete;

		// override (IMenu)
		void               Accept(CallbackProcessor* a_processor) override;  // 01
		UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;    // 04

		// override (MenuEventHandler)
		bool CanProcess(InputEvent* a_event) override;  // 01

		// members
		bool unk50;     // 50 - Set in ProcessMessage, cleared in CanProcess
		char pad51[7];  // 51
	private:
		KEEP_FOR_RE()
	};
#	if defined(EXCLUSIVE_SKYRIM_VR)
	static_assert(sizeof(CalibrationOptionMenu) == 0x58);
#	else
	static_assert(sizeof(CalibrationOptionMenu) == 0x48);
#	endif
}
#endif
