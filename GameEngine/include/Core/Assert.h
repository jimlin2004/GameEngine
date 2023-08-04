#ifndef GAMEENGINE_ASSERT_H
#define GAMEENGINE_ASSERT_H

#include <cassert>

#ifdef NDEBUG
    #define GAME_ENGINE_ASSERT(_expr, _msg) (void(0))
#else
    #define GAME_ENGINE_ASSERT(_expr, _msg) \
        assert((_expr) && (_msg))
#endif /* !defined (NDEBUG) */

#endif //GAMEENGINE_ASSERT_H