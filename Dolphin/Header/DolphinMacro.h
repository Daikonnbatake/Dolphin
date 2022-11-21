#pragma once


// ä¾¿åˆ©ãƒžã‚¯ãƒ
#define FOR(index, maxCount)       for (int index = 0; index < maxCount; ++index)
#define FOREACH(element, iterable) for (auto* element : iterable)
#define RELEASE(target)    \
    if (target != nullptr) \
    {                      \
        delete target;     \
        target = nullptr;  \
    }