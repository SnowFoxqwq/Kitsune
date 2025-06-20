#pragma once

#include "kitsune_pch.h"
#include "kitsune/core.h"

namespace kitsune
{
	template<class FuncSign>
	using Function = std::function<FuncSign>;

	//-----------------------------------------------------------------------------------------
	//  Events in Kitsune are currently blocking, meaning when an event occurs 
	//  it immediately gets dispatched and must be dealt with right then an there.
	//  For the future, a better strategy might be to buffer events in an event bus 
	//  and process them during the "event" part of the update stage.
	//-----------------------------------------------------------------------------------------

#undef MOUSE_MOVED

	enum class EventType
	{
		NONE = 0,
		//window related:
		WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
		//application related
		APPLICATION_TICK, APPLICATION_UPDATE, APPLICATION_RENDER,
		//keyboard related
		KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
		//mouse related
		MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
	};

	enum EventCategory
	{
		EVENT_CATEGORY_NONE            = 0,
		EVENT_CATEGORY_APPLICATION     = BIT(0),
		EVENT_CATEGORY_INPUT           = BIT(1),
		EVENT_CATEGORY_KEYBOARD        = BIT(2),
		EVENT_CATEGORY_MOUSE           = BIT(3),
		EVENT_CATEGORY_MOUSE_BUTTON    = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType get_static_event_type() { return EventType::##type; } \
							   virtual EventType get_event_type() const override { return get_static_event_type(); } \
							   virtual const char* get_name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override { return category; }

	//Event base class
	class KITSUNE_API Event
	{
		friend class EventDispather;
	public:
		virtual EventType get_event_type() const = 0;
		virtual const char* get_name() const = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string message() const { return get_name(); }

		bool is_in_category(EventCategory category) const
		{
			return get_category_flags() & category;
		}

	protected:
		bool _handled = false;
	};

	class EventDispatcher
	{
		template<class T>
		using EventFunction = Function<bool(T&)>;
	public:
		EventDispatcher(Event& event) :_event(event) {}

		template<class T>
		bool dispatch(EventFunction<T> function)
		{
			static_assert(std::is_base_of_v<Event, T>, "Type must inherit from Event!");
			if (_event.get_event_type() == T::get_static_event_type())
			{
				//using pointers and polymorphism to convert the type of _event to T and call functions
				_event._handled = function(*(T*)&_event);
				return true;
			}
			return false;
		}
	private:
		Event& _event;
	};

	static std::ostream& operator<<(std::ostream& os, const Event& event);

}