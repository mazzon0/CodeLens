#include <iostream>
#include "Editor/Editor.h"

using namespace std;

int main() {
    Editor::Init();
    Editor::Run();
    Editor::Destroy();
}