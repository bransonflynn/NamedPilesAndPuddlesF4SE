#include "Internal/NamedPilesAndPuddles.hpp"

namespace Internal
{
	bool IsAshPile(RE::ObjectRefHandle& a_ref)
	{
		auto obj = a_ref ? a_ref.get() : nullptr;
		if (!a_ref || !obj) {
			logger::info("IsAshPile return false: a_ref or obj was null");
			return false;
		}

		if (obj->Is(RE::ENUM_FORMTYPE::kACTI)) {
			auto ashPile = a_ref.get()->extraList->HasType(RE::kAshpileRef);
			if (!ashPile) {
				logger::info("IsAshPile return false: ashPile was null");
				return false;
			}

			return !a_ref.get()->extraList->HasType(RE::kTextDisplayData);
		}

		logger::info("IsAshPile return false: fail case");
		return false;
	}
}
