#include "Editor.h"

int main(int argc, char* argv[])
{
    GameEngineEditor::Editor* editor = new GameEngineEditor::Editor("Editor", 640, 480);
    editor->initAll();
    editor->start();
    return 0;
}