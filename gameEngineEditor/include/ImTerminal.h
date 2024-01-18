#ifndef IMTERMINAL_H
#define IMTERMINAL_H

#include <cstddef>

namespace GameEngineEditor
{
    class ImTerminal
    {
    public:
        void render();
    private:
        char outputBuffer[4096] = "\0";
        size_t outputBufferSize = 4096;
        char inputBuffer[256] = "\0";
        size_t inputBufferSize = 256;
    };
}

#endif