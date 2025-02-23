#include "Internal/CrosshairRefChange.hpp"
#include "Internal/NamedPilesAndPuddles.hpp"

namespace Internal::Events
{
	namespace Callbacks
	{
		CrosshairRefHandler::~CrosshairRefHandler()
		{
			Unregister();
		}

		void CrosshairRefHandler::Register()
		{
			RE::ViewCasterUpdateEvent::GetEventSource()->RegisterSink(this);
		}

		void CrosshairRefHandler::Unregister()
		{
			RE::ViewCasterUpdateEvent::GetEventSource()->UnregisterSink(this);
		}

		RE::ObjectRefHandle CrosshairRefHandler::GetPreviousRef() const
		{
			const auto lock = std::shared_lock{ _mutex };
			return _previousRef;
		}

		RE::ObjectRefHandle CrosshairRefHandler::GetCurrentRef() const
		{
			const auto lock = std::shared_lock{ _mutex };
			return _currentRef;
		}

		void CrosshairRefHandler::Clear()
		{
			const auto lock = std::unique_lock{ _mutex };

			_previousRef = {};
			_currentRef = {};
		}

		RE::BSEventNotifyControl CrosshairRefHandler::ProcessEvent(const RE::ViewCasterUpdateEvent& a_event, RE::BSTEventSource<RE::ViewCasterUpdateEvent>*)
		{
			logger::info("crosshair ref event (callbacks) recieved");

			const auto lock = std::unique_lock{ _mutex };
			const auto& value = a_event.optionalValue;

			_previousRef = _currentRef;
			_currentRef = value ? value->currentVCData.activatePickRef : RE::ObjectRefHandle();

			if (_currentRef.get().get() == nullptr) {
				logger::info("_currentRef was nullptr");
				return RE::BSEventNotifyControl::kContinue;
			}

			auto currentRefName = _currentRef.get().get()->GetDisplayFullName();
			bool isAshPile = Internal::IsAshPile(_currentRef);
			logger::info("name: {}, isAshPile: {}", currentRefName, isAshPile);

			return RE::BSEventNotifyControl::kContinue;
		}
	}
}
