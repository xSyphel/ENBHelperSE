#pragma once

#include "RE/I/ImageSpaceEffect.h"

namespace RE
{
	class BSReloadShaderI
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSReloadShaderI;
		inline static constexpr auto VTABLE = VTABLE_BSReloadShaderI;

		virtual void ReloadShaders(void* a_stream) = 0;  // 00
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSReloadShaderI) == 0x8);
}
