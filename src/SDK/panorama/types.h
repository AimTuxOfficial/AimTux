#pragma once

#include "IUIPanel.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wreorder"
#include "../Valve/tier1/utldelegateimpl.h"
#pragma GCC diagnostic pop
namespace panorama
{
    class IUIPanel;
    class IUIEvent;
    class IUIEngineFrameListener;
    class IUIPanelStyle;
    class IUIJSObject;
    class IUIWindow;
    class IUISettings;
    class IUITextLayout;
    class IUIInputEngine;
    class IUILocalize;
    class IUISoundSystem;
    class IUISettings;
    class IUILayoutManager;
    class IUIFileSystem;
    class IUIPanelClient;

    // E Prefix for enums?
    class EFontStyle;
    class EFontWeight;
    class ETextAlign;
    class EPanelRepaint;
    class EStyleRepaint;
    class EStyleFlags;
    class EFocusMoveDirection;
    class EMouseCanActivate;
    class EAnimationTimingFunction;
    class EAnimationDirection;

    class CUILength;
    class CLayoutFile;
    typedef unsigned short CPanoramaSymbol;
    class PanelHandle_t;
    class CJSONWebAPIParams;
    class UIEventFactory;
    class EPanelEventSource_t;
    class CPanel2DFactory;
    class RegisterJSType_t;
    class RegisterJSScopeInfo_t;
    class RegisterJSEntryInfo_t;


    // Returned by the CreatePanel functions. TODO: Look at panelRefs this might be that.
    class PanelWrapper{
    public:
        void* vtable;
        IUIPanel* panel;
    };


    struct ScrollBehavior_t;
}