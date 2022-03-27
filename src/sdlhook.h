#pragma once

namespace SDL2
{
    void HookSwapWindow();
    void UnhookWindow();

    void HookPollEvent();
    void UnhookPollEvent();

    inline int mouseX = 500;
    inline int mouseY = 500;
    inline bool isMouseDown = false;
}
