#include "Internal/NamedPilesAndPuddles.hpp"

// ashpile formids
#define ASHPILE_DEFAULT 0x9142E			  // AshPile01
#define ASHPILE_BLUE 0x187990			  // AshPileBlue
#define ASHPILE_ROBOT 0x181B39			  // AshPileRobot01
#define ASHPILE_PLASMAGOO 0x139F8D		  // GooPile01
#define ASHPILE_MIRELURKQUEENGOO 0x1C6BD1 // MirelurkQueenGooPile01

namespace Internal
{
	// -1 for false, 0 -> 4 for true
	int8_t IsAshPile(RE::TESObjectREFR* a_ref)
	{
		uint32_t refFormID = a_ref->GetBaseObject()->formID;

		switch (refFormID) {
			case ASHPILE_DEFAULT: {
				return 0;
				break;
			}
			case ASHPILE_BLUE: {
				return 1;
				break;
			}
			case ASHPILE_ROBOT: {
				return 2;
				break;
			}
			case ASHPILE_PLASMAGOO: {
				return 3;
				break;
			}
			case ASHPILE_MIRELURKQUEENGOO: {
				return 4;
				break;
			}
			default: {
				return -1;
				break;
			}
		}
	}

	void RenameAshPile(RE::TESObjectREFR* a_ref, int8_t ashPileType)
	{
		auto ownerName = a_ref ? a_ref->GetDisplayFullName() : std::string();
		if (!ownerName.empty()) {
			std::string finalName = std::string();

			switch (ashPileType) {
				case 0: {
					finalName = ownerName + "'s Ash Pile";
					break;
				}
				case 1: {
					finalName = ownerName + "'s Ash Pile";
					break;
				}
				case 2: {
					finalName = ownerName + "'s Ash Pile";
					break;
				}
				case 3: {
					finalName = ownerName + "'s Goo Puddle";
					break;
				}
				case 4: {
					finalName = ownerName + "'s Acid Puddle";
					break;
				}
				default: {
					break;
				}
			}
			// const char* finalName_const = finalName.c_str();

			auto extraList = a_ref->extraList.get();
			if (!extraList) {
				logger::info("extraList was none");
				return;
			}
			// extraList->SetOverrideName(finalName_const);
			RE::TESFullName::SetFullName(a_ref->GetBaseObject(), finalName);
			logger::info("extraListText->displayName set to {}", finalName);

			// bool nameSetResult = RE::TESFullName::SetFullName(a_ref, finalName_sv);
		}
		// auto ownerName = owner ? owner->GetDisplayFullName() : std::string();
		// if (!ownerName.empty()) {
		// 	auto finalName = NameManager::GetSingleton()->GetName(ownerName, a_ref->GetName());
		// 	a_ref->SetDisplayName(finalName, true);
		// }
	}
}

// auto obj = a_ref ? a_ref.get() : nullptr;
// if (!a_ref || !obj) {
// 	logger::info("IsAshPile return false: a_ref or obj was null");
// 	return false;
// }

// if (obj->Is(RE::ENUM_FORMTYPE::kACTI)) {
// 	logger::info("IsAshPile: was activator");
// 	auto ashPile = a_ref.get()->extraList->HasType(RE::kAshpileRef);
// 	if (!ashPile) {
// 		logger::info("IsAshPile return false: ashPile was null");
// 		return false;
// 	}

// 	return !a_ref.get()->extraList->HasType(RE::kTextDisplayData);
// }
// else {
// 	logger::info("IsAshPile: was not activator");
// }

// logger::info("IsAshPile return false: fail case");
// return false;
