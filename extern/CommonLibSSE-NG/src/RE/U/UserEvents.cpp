#include "RE/U/UserEvents.h"

namespace RE
{
	UserEvents* UserEvents::GetSingleton()
	{
		static REL::Relocation<UserEvents**> singleton{ RELOCATION_ID(516458, 402638) };
		return *singleton;
	}
}
