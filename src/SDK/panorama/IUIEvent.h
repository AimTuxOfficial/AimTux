#pragma once
#include "IUIPanel.h"
//#include <v8.h>
namespace panorama
{
    class IUIEvent
    {
    public:
        /*
        virtual void DESTROY() = 0;
        virtual void DESTROY2() = 0;
        virtual IUIPanel* GetTargetPanel(void);
        virtual void SetTargetPanel(IUIPanel const *);
        virtual CPanoramaSymbol* GetEventType(void);
        virtual bool CanBubble(void);
        virtual void Dispatch(CUtlAbstractDelegate);
        virtual void Copy(void);
        virtual void GetJavaScriptArgs(int *,v8::Handle<v8::Value> value);
        */
        panorama::IUIPanel* pos1; //0x0000
        char pad_0008[8]; //0x0008
        panorama::IUIPanel* pos2; //0x0010
        panorama::IUIPanel* pos3; //0x0018
        char pad_0020[24]; //0x0020
        panorama::IUIPanel* pos4; //0x0038
        char pad_0040[8]; //0x0040
        panorama::IUIPanel* pos5; //0x0048
        panorama::IUIPanel* pos6; //0x0050
        char pad_0058[8]; //0x0058
        panorama::IUIPanel* pos7; //0x0060
        panorama::IUIPanel* pos8; //0x0068
        char pad_0070[16]; //0x0070
        panorama::IUIPanel* pos9; //0x0080
        panorama::IUIPanel* pos10; //0x0088
        panorama::IUIPanel* pos11; //0x0090
        char pad_0098[24]; //0x0098
        panorama::IUIPanel* pos12; //0x00B0
        panorama::IUIPanel* pos13; //0x00B8
        char pad_00C0[8]; //0x00C0
        panorama::IUIPanel* pos14; //0x00C8
        char pad_00D0[16]; //0x00D0
        panorama::IUIPanel* pos15; //0x00E0
        char pad_00E8[8]; //0x00E8
        char* eventName; //0x00F0
        char pad_00F8[16]; //0x00F8
        panorama::IUIPanel* pos16; //0x0108
        char pad_0110[8]; //0x0110
        panorama::IUIPanel* pos17; //0x0118
        char pad_0120[40]; //0x0120
        panorama::IUIPanel* pos18; //0x0148
        char pad_0150[8]; //0x0150
        panorama::IUIPanel* pos19; //0x0158
        char pad_0160[8]; //0x0160
        panorama::IUIPanel* pos20; //0x0168
        char pad_0170[32]; //0x0170
        panorama::IUIPanel* pos21; //0x0190
        char pad_0198[360]; //0x0198
    };
}
