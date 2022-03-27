#pragma once

#include "IAppSystem.h"
#include <cstdint>

#define PseudoGLContextPtr void*

class ILauncherMgr : public IAppSystem
{
public:
    virtual bool Connect( CreateInterfaceFn factory ) = 0;
    virtual void Disconnect() = 0;

    virtual void *QueryInterface( const char *pInterfaceName ) = 0;

    // Init, shutdown
    virtual InitReturnVal_t Init() = 0;
    virtual void Shutdown() = 0;

    // Create the window.
    virtual bool CreateGameWindow( const char *pTitle, bool bWindowed, int width, int height, bool bDesktopFriendlyFullscreen ) = 0;

    virtual void GetDesiredPixelFormatAttribsAndRendererInfo( unsigned int **ptrOut, unsigned int  *countOut, void *rendInfoOut ) = 0;

    // Get the NSGLContext for a window's main view - note this is the carbon windowref as an argument
    virtual void* GetGLContextForWindow( void* windowref ) = 0;

    // Get the next N events. The function returns the number of events that were filled into your array.
    virtual int GetEvents( void *pEvents, int nMaxEventsToReturn, bool debugEvents = false ) = 0;

    // Set the mouse cursor position.
    virtual void SetCursorPosition( int x, int y ) = 0;

    virtual void ShowPixels( void *params ) = 0;

    virtual void SetWindowFullScreen( bool bFullScreen, int nWidth, int nHeight, bool bDesktopFriendlyFullscreen ) = 0;

    virtual bool IsWindowFullScreen() = 0;
    virtual void MoveWindow( int x, int y ) = 0;
    virtual void SizeWindow( int width, int tall ) = 0;
    virtual void PumpWindowsMessageLoop() = 0;

    virtual void DestroyGameWindow() = 0;
    virtual void SetApplicationIcon( const char *pchAppIconFile ) = 0;

    virtual void GetMouseDelta( int &x, int &y, bool bIgnoreNextMouseDelta = false ) = 0;

    virtual void GetNativeDisplayInfo( int nDisplay, uint &nWidth, uint &nHeight, uint &nRefreshHz ) = 0; // Retrieve the size of the monitor (desktop)
    virtual void RenderedSize( uint &width, uint &height, bool set ) = 0;	// either set or retrieve rendered size value (from dxabstract)
    virtual void DisplayedSize( uint &width, uint &height ) = 0;			// query backbuffer size (window size whether FS or windowed)

    virtual void *GetDisplayDB( void ) = 0;

    virtual void WaitUntilUserInput( int msSleepTime ) = 0;

    virtual PseudoGLContextPtr	GetMainContext() = 0;
    virtual PseudoGLContextPtr CreateExtraContext() = 0;
    virtual void DeleteContext( PseudoGLContextPtr hContext ) = 0;
    virtual bool MakeContextCurrent( PseudoGLContextPtr hContext ) = 0;

    virtual void GetStackCrawl( void *params ) = 0;

    virtual void *GetWindowRef() = 0;

    virtual void SetMouseVisible( bool bState ) = 0;
    virtual int GetActiveDisplayIndex() = 0;
    virtual void SetMouseCursor( void* hCursor ) = 0;
    virtual void SetForbidMouseGrab( bool bForbidMouseGrab ) = 0;
    virtual void OnFrameRendered() = 0;

    virtual void SetGammaRamp( const uint16_t *pRed, const uint16_t *pGreen, const uint16_t *pBlue ) = 0;

    virtual void ForceSystemCursorVisible() = 0;
    virtual void UnforceSystemCursorVisible() = 0;

    virtual double GetPrevGLSwapWindowTime() = 0;
};
