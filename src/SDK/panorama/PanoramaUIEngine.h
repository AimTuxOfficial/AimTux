#pragma once

#include "../IAppSystem.h"
#include "IUIPanel.h"
#include "IUIEvent.h"

// Xref "english" to first function, then vtable.
// OR xref "Panorama Cache Summary" 2x to PrintCacheStatus()
namespace panorama
{
    extern PanelArray* panelArray;
    class UIEngine
    {
    public:
        virtual void DESTROY() = 0; // 0
        virtual void DESTROY2() = 0;
        virtual void StartupSubsystems(panorama::IUISettings *,void* PlatWindow_t__) = 0;
        virtual void ConCommandInit(void* IConCommandBaseAccessor) = 0;
        virtual void Shutdown(void) = 0;
        virtual void RequestShutdown(void) = 0;
        virtual void Run(void) = 0;
        virtual void RunFrame(void) = 0;
        virtual void SetAggressiveFrameRateLimit(bool) = 0;
        virtual bool IsRunning(void) = 0;
        virtual bool HasFocus(void) = 0;
        virtual double GetCurrentFrameTime(void) = 0;
        virtual void unk0() = 0; // getter
        virtual void unk1() = 0; // setter ^^
        virtual void INT3_WRAPPER() = 0;
        virtual void INT3_WRAPPER2() = 0;
        virtual void INT3_WRAPPER3() = 0;// probably windows specific
        virtual void INT3_WRAPPER4() = 0;
        virtual void INT3_WRAPPER5() = 0;
        virtual void CreateTextLayout(char const*,char const*,float,float,panorama::EFontWeight,panorama::EFontStyle,panorama::ETextAlign,bool,bool,int,float,float) = 0;
        virtual void CreateTextLayout(wchar_t const*,char const*,float,float,panorama::EFontWeight,panorama::EFontStyle,panorama::ETextAlign,bool,bool,int,float,float) = 0;
        virtual void FreeTextLayout(panorama::IUITextLayout *) = 0;
        virtual void GetSomeFontThing(void) = 0; //similar to function below
        virtual void GetSortedValidFontNames(void) = 0;
        virtual IUIInputEngine* UIInputEngine(void) = 0;
        virtual IUILocalize* UILocalize(void) = 0;
        virtual IUISoundSystem* UISoundSystem(void) = 0;
        virtual IUISettings*  UISettings(void) = 0;
        virtual IUILayoutManager* UILayoutManager(void) = 0;
        virtual IUIFileSystem* UIFileSystem(void) = 0;
        virtual void INT3_WRAPPER6() = 0;
        virtual void RegisterFrameFunc(void (*)(void)) = 0;
        virtual void ReloadLayoutFile(panorama::CPanoramaSymbol) = 0;
        virtual void ToggleDebugMode(void) = 0;
        virtual const char* GetConsoleHistory(void) = 0;
        virtual PanelWrapper* CreatePanel(void) = 0;
        virtual void PanelDestroyed(panorama::IUIPanel *,panorama::IUIPanel *) = 0;
        virtual bool IsValidPanelPointer(panorama::IUIPanel const*) = 0;
        virtual PanelHandle_t* GetPanelHandle(panorama::IUIPanel const*) = 0;
        virtual IUIPanel* GetPanelPtr(panorama::PanelHandle_t const&) = 0;
        virtual void CallBeforeStyleAndLayout(panorama::IUIPanel *) = 0;
        virtual void RegisterForPanelDestroyed();//CUtlDelegate<void ()(panorama::IUIPanel const*,panorama::IUIPanel*)>) = 0;
        virtual void UnregisterForPanelDestroyed();//CUtlDelegate<void ()(panorama::IUIPanel const*,panorama::IUIPanel*)>) = 0;
        virtual void RegisterEventHandler(panorama::CPanoramaSymbol,panorama::IUIPanel *,CUtlAbstractDelegate) = 0;
        virtual void UnregisterEventHandler(panorama::CPanoramaSymbol,panorama::IUIPanel *,CUtlAbstractDelegate) = 0;
        virtual void RegisterEventHandler(panorama::CPanoramaSymbol,panorama::IUIPanelClient *,CUtlAbstractDelegate) = 0;
        virtual void UnregisterEventHandler(panorama::CPanoramaSymbol,panorama::IUIPanelClient *,CUtlAbstractDelegate) = 0;
        virtual void UnregisterEventHandlersForPanel(panorama::IUIPanel *) = 0;
        virtual void RegisterForUnhandledEvent(panorama::CPanoramaSymbol,CUtlAbstractDelegate) = 0;
        virtual void UnregisterForUnhandledEvent(panorama::CPanoramaSymbol,CUtlAbstractDelegate) = 0;
        virtual void UnregisterForUnhandledEvents(void *) = 0;
        virtual bool HaveEventHandlersRegisteredForType(panorama::CPanoramaSymbol) = 0;
        virtual void RegisterPanelTypeEventHandler(panorama::CPanoramaSymbol,panorama::CPanoramaSymbol,CUtlAbstractDelegate,bool) = 0;
        virtual void DispatchEvent(panorama::IUIEvent *) = 0;
        virtual void DispatchEventAsync(float,panorama::IUIEvent *) = 0;
        virtual bool AnyHandlerRegisteredForEvent(panorama::CPanoramaSymbol const&) = 0;
        virtual CPanoramaSymbol* GetLastDispatchedEventSymbol(void) = 0;
        virtual IUIPanel* GetLastDispatchedEventTargetPanel(void) = 0; // This function can fail sometimes and you need to check the result/call it later (YUCK!)
        virtual void RegisterEventFilter(CUtlAbstractDelegate) = 0;
        virtual void UnregisterEventFilter(CUtlAbstractDelegate) = 0;
        virtual void LayoutAndPaintWindows(void) = 0;
        virtual const char* GetApplicationInstallPath(void) = 0;
        virtual const char* GetApplicationUserDataPath(void) = 0;
        virtual void RegisterNamedLocalPath(char const*,char const*,bool,bool) = 0;
        virtual void RegisterNamedUserPath(char const*,char const*,bool,bool) = 0;
        virtual void RegisterCustomFontPath(char const*) = 0;
        virtual void GetLocalPathForNamedPath(char const*) = 0;
        virtual void GetLocalPathForRelativePath(char const*,char const*,void* CUtlString) = 0;
        virtual void RegisterNamedRemoteHost(char const*,char const*) = 0;
        virtual void GetRemoteHostForNamedHost(char const*) = 0;
        virtual void RegisterXHeader(char const*,char const*) = 0;
        virtual int GetXHeaderCount(void) = 0;
        virtual void GetXHeader(int,void* CUtlString,void* CUtlString2) = 0;
        virtual void SetCookieHeaderForNamedRemoteHost();//char const*,CUtlVector<CUtlString,CUtlMemory<CUtlString,int>> const&) = 0;
        virtual void SetCookieHeaderForRemoteHost();//char const*,CUtlVector<CUtlString,CUtlMemory<CUtlString,int>> const&) = 0;
        virtual void GetCookieHeadersForNamedRemoteHost(char const*) = 0;
        virtual void GetCookieHeadersForRemoteHost(char const*) = 0;
        virtual void GetCookieValueForRemoteHost(char const*,char const*,void* CUtlString) = 0;
        virtual void BSetCookieForWebRequests(char const*,char const*,char const*) = 0;
        virtual void BClearCookieForWebRequests(char const*,char const*,char const*) = 0;
        virtual void* AccessHTMLController(void) = 0;
        virtual void unk() = 0; // _SDL_ShowSimpleMessageBox with yes/no
        virtual void AddFrameListener(panorama::IUIEngineFrameListener *) = 0;
        virtual void RemoveFrameListener(panorama::IUIEngineFrameListener *) = 0;
        virtual void RegisterMouseCanActivateParent(panorama::IUIPanel *,char const*) = 0;
        virtual void UnregisterMouseCanActivateParent(panorama::IUIPanel *) = 0;
        virtual void GetMouseCanActivateParent(panorama::IUIPanel *) = 0;
        virtual bool AnyWindowHasFocus(void) = 0;
        virtual bool AnyVisibleWindowHasFocus(void) = 0;
        virtual bool AnyOverlayWindowHasFocus(void) = 0;
        virtual IUIWindow* GetFocusedWindow(void) = 0;
        virtual float GetLastInputTime(void) = 0;
        virtual float UpdateLastInputTime(void) = 0;
        virtual void ClearClipboard(void) = 0;
        virtual void CopyToClipboard(char const*,char const*) = 0;
        virtual void GetClipboardText(void* CUtlString,void* CUtlString2) = 0;
        virtual const char* GetDisplayLanguage(void) = 0;
        virtual void unk2() = 0;
        virtual void unk3() = 0;
        virtual void unk4() = 0;
        virtual bool HasOverlayForApp(unsigned long long,unsigned long long) = 0;
        virtual void TrackOverlayForApp(unsigned long long,unsigned long long,void *) = 0;
        virtual void DeleteOverlayInstanceForApp(unsigned long long,unsigned long long,void *) = 0;
        virtual void OverlayForApp(unsigned long long,unsigned long long) = 0;
        virtual void unk5() = 0;
        virtual IUIPanelStyle* AllocPanelStyle(panorama::IUIPanel *,float) = 0;
        virtual void FreePanelStyle(panorama::IUIPanelStyle *) = 0;
        virtual void SetPanelWaitingAsyncDelete(panorama::IUIPanel *) = 0;
        virtual bool IsPanelWaitingAsyncDelete(panorama::IUIPanel *) = 0;
        virtual void PulseActiveControllerHaptic();//panorama::IUIEngine::EHapticFeedbackPosition,panorama::IUIEngine::EHapticFeedbackStrength) = 0;
        virtual void SomethingControllerHapticRelated() = 0;
        virtual void MarkLayerToRepaintThreadSafe(unsigned long long) = 0;
        virtual void AddDirectoryChangeWatch(char const*) = 0;
        virtual int GetWheelScrollLines(void) = 0; // default 3
        virtual int RunScript(panorama::IUIPanel *panel,char const *entireJSCode,char const *pathToXMLContext,int,int,bool alreadyCompiled) = 0;
        virtual void ExposeObjectTypeToJavaScript(char const*,CUtlAbstractDelegate &) = 0;
        virtual bool IsObjectTypeExposedToJavaScript(char const*) = 0;
        virtual void ExposeGlobalObjectToJavaScript(char const*,void *,char const*,bool) = 0;
        virtual void ClearGlobalObjectForJavaScript(char const*,void *) = 0;
        virtual void DeleteJSObjectInstance(panorama::IUIJSObject *) = 0;
        virtual IUIPanel* GetPanelForJavaScriptContext();//v8::Context *) = 0;
        virtual void* GetJavaScriptContextForPanel(panorama::IUIPanel *) = 0;
        virtual void OutputJSExceptionToConsole();//v8::TryCatch &,panorama::IUIPanel *) = 0;
        virtual void AddGlobalV8FunctionTemplate();//char const*,v8::Handle<v8::FunctionTemplate> *,bool) = 0;
        virtual void* GetV8GlobalContext(void) = 0;
        virtual void GetCurrentV8ObjectTemplateToSetup(void) = 0; //gets offset.
        virtual void GetCurrentV8ObjectTemplateToSetup2(void) = 0; //gets offset and calls some function.
        virtual void Grabber3(void) = 0; // returns offset in class
        virtual void Grabber4(void) = 0; // returns offset in class.
        virtual void UIStyleFactory(void) = 0;
        virtual void GetV8Isolate(void) = 0;
        virtual void RunFunction() = 0;
        virtual void RunFunction2() = 0; //different args
        virtual void CreateV8PanelInstance(panorama::IUIPanel *) = 0;
        virtual void CreateV8PanelStyleInstance(panorama::IUIPanelStyle *) = 0;
        virtual void CreateV8ObjectInstance(char const*,void *,panorama::IUIJSObject *) = 0;
        virtual void _unk() = 0;
        virtual void InitiateAsyncJSONWebAPIRequest();//EHTTPMethod,CUtlString,panorama::IUIPanel *,void *,panorama::CJSONWebAPIParams *,uint) = 0;
        virtual void InitiateAsyncJSONWebAPIRequest(int overloadMeme);//EHTTPMethod,CUtlString,CUtlDelegate<void ()(unsigned long long,KeyValues *,void *)>,void *,panorama::CJSONWebAPIParams *,uint) = 0;
        virtual void CancelAsyncJSONWebAPIRequest(unsigned int) = 0;
        virtual void ResolvePath(char const*) = 0;
        virtual void RegisterEventWithEngine(panorama::CPanoramaSymbol,panorama::UIEventFactory) = 0;
        virtual bool IsValidEventName(panorama::CPanoramaSymbol) = 0;
        virtual bool IsValidPanelEvent(panorama::CPanoramaSymbol,int *) = 0;
        virtual void CreateInputEventFromSymbol(panorama::CPanoramaSymbol,panorama::IUIPanel *,panorama::EPanelEventSource_t,int) = 0;
        virtual void CreateEventFromString(panorama::IUIPanel *,char const*,char const**) = 0;
        virtual void unk11();
        virtual void RegisterPanelFactoryWithEngine(panorama::CPanoramaSymbol,panorama::CPanel2DFactory *) = 0;
        virtual bool RegisteredPanelType(panorama::CPanoramaSymbol) = 0;
        virtual PanelWrapper* CreatePanel(panorama::CPanoramaSymbol *panelType,char const* id,panorama::IUIPanel *createInThisParent) = 0; // paneltype (ex: Panel, Label), id (ex: <Label id="swag">)
        virtual void CreateDebuggerWindow(void) = 0;
        virtual void CloseDebuggerWindow(void) = 0;
        virtual void RegisterScheduledDelegate();// double,CUtlDelegate<void ()(void)> ) = 0;
        virtual void CancelScheduledDelegate(int) = 0;
        virtual float GetLastScheduledDelegateRunTime(void) = 0;
        virtual CPanoramaSymbol MakeSymbol(char const*) = 0; // if the symbol already exists, you'll get that one.
        virtual const char *ResolveSymbol(unsigned short) = 0; // if you pass an invalid number into here, it can crash the program.
        virtual void QueueDecrementRefNextFrame();//CRefCounted<CRefCountServiceBase<true,CRefMT>> *) = 0;
        virtual void RegisterJSGenericCallback();//panorama::IUIPanel *,v8::Handle<v8::Function>) = 0;
        virtual void InvokeJSGenericCallback();//int,int,v8::Handle<v8::Value> *,v8::Handle<v8::Value> *) = 0;
        virtual void UnregisterJSGenericCallback(int) = 0;
        virtual int GetNumRegisterJSScopes(void) = 0;
        virtual void GetRegisterJSScopeInfo(int,panorama::RegisterJSScopeInfo_t *) = 0;
        virtual void GetRegisterJSEntryInfo(int,int,panorama::RegisterJSEntryInfo_t *) = 0;
        virtual void StartRegisterJSScope(char const*,char const*) = 0;
        virtual void EndRegisterJSScope(void) = 0;
        virtual void NewRegisterJSEntry(char const*,uint,char const*,panorama::RegisterJSType_t) = 0;
        virtual void SetRegisterJSEntryParams(int,unsigned char,panorama::RegisterJSType_t *) = 0;
        virtual void _padding() = 0;
        virtual void ClearFileCache(void) = 0;
        virtual void PrintCacheStatus(void) = 0;
        virtual void GetWindowsForDebugger();//CUtlVector<panorama::IUIWindow *,CUtlMemory<panorama::IUIWindow *,int>> &) = 0;
        virtual void SetPaintCountTrackingEnabled(bool) = 0;
        virtual bool GetPaintCountTrackingEnabled(void) = 0;
        virtual void IncrementPaintCountForPanel(unsigned long long,bool,double) = 0;
        virtual void GetPanelPaintInfo(unsigned long long,unsigned int &,bool &,double &) = 0;
        virtual bool HasAnyWindows(void) = 0;
        virtual void TextEntryFocusChange(panorama::IUIPanel *) = 0;
        virtual void TextEntryInvalid(panorama::IUIPanel *) = 0;
        virtual void SetClipboardText(const char* text) = 0; // wrapper for _SDL_SetClipboardText
        virtual const char* GetClipboardText() = 0; // wrapper for _SDL_GetClipboardText
        virtual void OnFileCacheRemoved(panorama::CPanoramaSymbol) = 0;
        virtual void RunPlatformFrame(void) = 0;
        virtual void CreateSoundSystem(void) = 0;
    };
}


class IPanoramaUIEngine : IAppSystem
{
public:
    virtual void SetupUIEngine(void);
    virtual void ShutdownUIEngine(void);
    virtual panorama::UIEngine* AccessUIEngine(void);
    virtual void HandleInputEvent();
    virtual void unk1(); // calls this function in PanoramaUIEngine -- call    qword ptr [rax+0A0h]
    virtual void unk2();
};
