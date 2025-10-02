#pragma once

#include "RE/B/BSString.h"
#include "RE/B/BSTArray.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/I/IUIMessageData.h"

namespace RE
{
	class IMessageBoxCallback;

	class MessageBoxData : public IUIMessageData
	{
	public:
		inline static constexpr auto RTTI = RTTI_MessageBoxData;
		inline static constexpr auto VTABLE = VTABLE_MessageBoxData;

		~MessageBoxData() override;  // 00

		void QueueMessage()
		{
			using func_t = decltype(&MessageBoxData::QueueMessage);
			static REL::Relocation<func_t> func{ RELOCATION_ID(51422, 52271) };
			return func(this);
		}

		// members
		BSString                             bodyText;           // 10
		BSTArray<BSString>                   buttonText;         // 20
		std::uint32_t                        type;               // 38 - some sort of identifier ranging from 0-29, being 25 the one with the "highest priority"
		std::int32_t                         cancelOptionIndex;  // 3C
		BSTSmartPointer<IMessageBoxCallback> callback;           // 40
		std::uint32_t                        menuDepth;          // 48
		std::uint8_t                         optionIndexOffset;  // 4C
		bool                                 useHtml;            // 4D
		bool                                 verticalButtons;    // 4E
		bool                                 isCancellable;      // 4F
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(MessageBoxData) == 0x50);
}
