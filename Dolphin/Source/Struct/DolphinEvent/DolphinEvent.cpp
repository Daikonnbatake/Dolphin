#include "pch.h"
#include "DolphinEvent.h"

template<class... Args>
inline Dolphin::Struct::DolphinEvent<Args...>::DolphinEvent()
{
    this->callbackSet = unordered_set<callback<Args...>>();
}


template<class... Args>
inline void Dolphin::Struct::DolphinEvent<Args...>::Invoke(Args... args)
{
    FOREACH(e, this->callbackSet) e(args);
}


template<class... Args>
inline void
Dolphin::Struct::DolphinEvent<Args...>::AddEvent(callback<Args...> callback)
{
    this->callbackSet.insert(callback);
}


template<class... Args>
inline void
Dolphin::Struct::DolphinEvent<Args...>::PopEvent(callback<Args...> callback)
{
    this->callbackSet.erase(callback);
}