#include "RE/Bethesda/BSScaleformManager.hpp"

#include "RE/Bethesda/BSSystemFileStreamer.hpp"
#include "RE/Bethesda/IMenu.hpp"
#include "RE/Bethesda/Settings.hpp"
#include "RE/Scaleform/GFx/GFx_Loader.hpp"
#include "RE/Scaleform/GFx/GFx_Player.hpp"

namespace RE
{
	bool BSScaleformManager::LoadMovieEx(
		IMenu& a_menu,
		stl::zstring a_filePath,
		stl::zstring a_menuObjPath,
		ScaleModeType a_scaleMode,
		float a_backgroundAlpha)
	{
		if (REL::Relocation<SettingT<INISettingCollection>*> fileUncacheOnMenuOpen{ REL::ID(454316) };
			fileUncacheOnMenuOpen->GetBinary()) {
			BSSystemFileStreamer::UncacheAll(true);
		}

		using LoadConstants = Scaleform::GFx::Loader::LoadConstants;
		REX::EnumSet loadConstants{ LoadConstants::kWaitFrame1, LoadConstants::kKeepBindData };
		const Scaleform::Ptr def{ loader->CreateMovie(a_filePath.data(), loadConstants.get()) };
		if (!def) {
			return false;
		}
		def->Release(); // dumb scaleform thing

		auto& movie = a_menu.uiMovie;
		movie.reset(def->CreateInstance(true));
		if (!movie) {
			return false;
		}
		movie->Release(); // dumb scaleform thing

		movie->SetViewScaleMode(a_scaleMode);
		movie->SetBackgroundAlpha(a_backgroundAlpha);
		a_menu.DoAdvanceMovie(0.0);
		if (!a_menuObjPath.empty()) {
			a_menu.SetMenuCodeObject(*movie, a_menuObjPath);
		}
		a_menu.RefreshPlatform();
		InitMovieViewport(*movie, 1.0F, 1.0F);
		a_menu.OnSetSafeRect();

		return true;
	}
}
