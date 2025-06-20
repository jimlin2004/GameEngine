#ifndef IMTERMINAL_H
#define IMTERMINAL_H

#include <cstddef>
#include <vector>
#include <string>

namespace GameEngineEditor
{
    class ImTerminal
    {
    public:
        void render();
        void append(const std::string& text);
        void clear();
    private:
        char inputBuffer[256] = "\0";
        size_t inputBufferSize = 256;
        std::vector<std::string> textData;
    };
}

#endif