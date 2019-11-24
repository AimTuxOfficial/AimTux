#include "hooker.h"

#include <link.h>
#include "Utils/patternfinder.h"
#include "Utils/util.h"
#include "Utils/vmt.h"
#include "Utils/xorstring.h"
#include "glhook.h"
#include "interfaces.h"
#include "offsets.h"


int* nPredictionRandomSeed = nullptr;
CMoveData* g_MoveData = nullptr;
bool* s_bOverridePostProcessingDisable = nullptr;

VMT* panelVMT = nullptr;
VMT* clientVMT = nullptr;
VMT* modelRenderVMT = nullptr;
VMT* clientModeVMT = nullptr;
VMT* gameEventsVMT = nullptr;
VMT* viewRenderVMT = nullptr;
VMT* inputInternalVMT = nullptr;
VMT* materialVMT = nullptr;
VMT* surfaceVMT = nullptr;
VMT* launcherMgrVMT = nullptr;
VMT* engineVGuiVMT = nullptr;
VMT* soundVMT = nullptr;
VMT* uiEngineVMT = nullptr;

uintptr_t oSwapWindow;
uintptr_t* swapWindowJumpAddress = nullptr;

uintptr_t oPollEvent;
uintptr_t* polleventJumpAddress = nullptr;

MsgFunc_ServerRankRevealAllFn MsgFunc_ServerRankRevealAll;
SendClanTagFn SendClanTag;
SetLocalPlayerReadyFn SetLocalPlayerReady;

RecvVarProxyFn fnSequenceProxyFn;

StartDrawingFn StartDrawing;
FinishDrawingFn FinishDrawing;

GetLocalClientFn GetLocalClient;

LineGoesThroughSmokeFn LineGoesThroughSmoke;
InitKeyValuesFn InitKeyValues;
LoadFromBufferFn LoadFromBuffer;

panorama::PanelArray* panorama::panelArray = nullptr;

unsigned int Offsets::playerAnimStateOffset = 0;
unsigned int Offsets::playerAnimOverlayOffset = 0;

GetSequenceActivityFn GetSeqActivity;

uintptr_t SetAbsOriginFnAddr;

//RandomSeedFn RandomSeed;
//RandomFloatFn RandomFloat;
//RandomFloatExpFn RandomFloatExp;
//RandomIntFn RandomInt;
//RandomGaussianFloatFn RandomGaussianFloat;

SetNamedSkyBoxFn SetNamedSkyBox;

std::vector<dlinfo_t> libraries;

// taken form aixxe's cstrike-basehook-linux
bool Hooker::GetLibraryInformation(const char* library, uintptr_t* address, size_t* size) {
	if (libraries.size() == 0) {
		dl_iterate_phdr([] (struct dl_phdr_info* info, size_t, void*) {
			dlinfo_t library_info = {};

			library_info.library = info->dlpi_name;
			library_info.address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
			library_info.size = info->dlpi_phdr[0].p_memsz;

			libraries.push_back(library_info);

			return 0;
		}, nullptr);
	}

	for (const dlinfo_t& current: libraries) {
		if (!strcasestr(current.library, library))
			continue;

		if (address)
			*address = current.address;

		if (size)
			*size = current.size;

		return true;
	}

	return false;
}

bool Hooker::HookRecvProp(const char* className, const char* propertyName, std::unique_ptr<RecvPropHook>& recvPropHook)
{
	// FIXME: Does not search recursively.. yet.
	// Recursion is a meme, stick to reddit mcswaggens.
	for (ClientClass* pClass = client->GetAllClasses(); pClass; pClass = pClass->m_pNext)
	{
		if (strcmp(pClass->m_pNetworkName, className) == 0)
		{
			RecvTable* pClassTable = pClass->m_pRecvTable;

			for (int nIndex = 0; nIndex < pClassTable->m_nProps; nIndex++)
			{
				RecvProp* pProp = &pClassTable->m_pProps[nIndex];

				if (!pProp || strcmp(pProp->m_pVarName, propertyName) != 0)
					continue;

				recvPropHook = std::make_unique<RecvPropHook>(pProp);

				return true;
			}

			break;
		}
	}

	return false;
}

void Hooker::FindIClientMode()
{
    uintptr_t hudprocessinput = reinterpret_cast<uintptr_t>(getvtable(client)[10]);
	GetClientModeFn GetClientMode = reinterpret_cast<GetClientModeFn>(GetAbsoluteAddress(hudprocessinput + 11, 1, 5));

	clientMode = GetClientMode();
}

void Hooker::FindGlobalVars()
{
	uintptr_t HudUpdate = reinterpret_cast<uintptr_t>(getvtable(client)[11]);

	globalVars = *reinterpret_cast<CGlobalVars**>(GetAbsoluteAddress(HudUpdate + 13, 3, 7));
}

void Hooker::FindCInput()
{
	uintptr_t IN_ActivateMouse = reinterpret_cast<uintptr_t>(getvtable(client)[16]);

	input = **reinterpret_cast<CInput***>(GetAbsoluteAddress(IN_ActivateMouse, 3, 7));
}

void Hooker::FindGlowManager()
{
    // Call right above "Music.StopAllExceptMusic"
	uintptr_t instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																	(unsigned char*) XORSTR("\xE8\x00\x00\x00\x00\x48\x8B\x3D\x00\x00\x00\x00\xBE\x01\x00\x00\x00\xC7"),
																	XORSTR("x????xxx????xxxxxx"));

	glowManager = reinterpret_cast<GlowObjectManagerFn>(GetAbsoluteAddress(instruction_addr, 1, 5))();
}

void Hooker::FindPlayerResource()
{
	uintptr_t instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																	(unsigned char*) XORSTR("\x48\x8B\x05\x00\x00\x00\x00\x55\x48\x89\xE5\x48\x85\xC0\x74\x10\x48"),
																	XORSTR("xxx????xxxxxxxxxx"));

	csPlayerResource = reinterpret_cast<C_CSPlayerResource**>(GetAbsoluteAddress(instruction_addr, 3, 7));
}

void Hooker::FindGameRules()
{
	uintptr_t instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																	(unsigned char*) XORSTR("\x48\x8B\x05"
																									"\x00\x00\x00\x00"
																									"\x48\x8B\x38\x0F\x84"),
																	XORSTR("xxx????xxxxx"));

	csGameRules = *reinterpret_cast<C_CSGameRules***>(GetAbsoluteAddress(instruction_addr, 3, 7));
}

void Hooker::FindRankReveal()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																(unsigned char*) XORSTR("\x55\x48\x89\xE5\x41\x54\x53\x48\x89\xFB\x48\x8B\x3D\x00\x00\x00\x00\x48\x85\xFF"),
																XORSTR("xxxxxxxxxxxxx????xxx"));

	MsgFunc_ServerRankRevealAll = reinterpret_cast<MsgFunc_ServerRankRevealAllFn>(func_address);
}

// "ClanTagChanged"
void Hooker::FindSendClanTag()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("engine_client.so"),
																(unsigned char*) XORSTR("\x55\x48\x89\xE5\x41\x55\x49\x89\xFD\x41\x54\xBF\x48\x00\x00\x00\x49\x89\xF4\x53\x48\x83\xEC\x08\xE8"
                                                                                                "\x00\x00\x00\x00"
                                                                                                "\x48\x8D\x35"
                                                                                                "\x00\x00\x00\x00"
                                                                                                "\x48\x89\xC7\x48\x89\xC3\xE8"
                                                                                                "\x00\x00\x00\x00"
                                                                                                "\x48\x8D\x35"
                                                                                                "\x00\x00\x00\x00"
                                                                                                "\x4C\x89\xEA"),
																XORSTR("xxxxxxxxxxxxxxxxxxxxxxxxx"
                                                                               "????"
                                                                               "xxx"
                                                                               "????"
                                                                               "xxxxxxx"
                                                                               "????"
                                                                               "xxx"
                                                                               "????"
                                                                               "xxx" ));

	SendClanTag = reinterpret_cast<SendClanTagFn>(func_address);
}
// "PrecacheCSViewScene"
void Hooker::FindViewRender()
{
	// 55 48 8D 15 ?? ?? ?? ?? 31 C9 48 8D 35 ?? ?? ?? ?? 48 89 E5 53 48 8D 3D ?? ?? ?? ?? 48 83 EC ?? 0F 57 C0
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																(unsigned char*) XORSTR("\x55\x48\x8D\x15"
																								"\x00\x00\x00\x00"
																								"\x31\xC9\x48\x8D\x35"
																								"\x00\x00\x00\x00"
																								"\x48\x89\xE5\x53\x48\x8D\x3D"
																								"\x00\x00\x00\x00"
																								"\x48\x83\xEC"
																								"\x00"
																								"\x0F\x57\xC0"),
																XORSTR("xxxx????xxxxx????xxxxxxx????xxx?xxx"));

	viewRender = reinterpret_cast<CViewRender*>(GetAbsoluteAddress(func_address + 294, 3, 7));
}

void Hooker::FindPrediction()
{
	uintptr_t seed_instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																		 (unsigned char*) XORSTR("\x48\x8B\x05"
                                                                                                         "\x00\x00\x00\x00"
                                                                                                         "\x8B\x38\xE8"
                                                                                                         "\x00\x00\x00\x00"
                                                                                                         "\x89\xC7"),
																		 XORSTR("xxx????xxx????xx"));
	uintptr_t helper_instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																		   (unsigned char*) XORSTR("\x00\x48\x89\x3D\x00\x00\x00\x00\xC3"),
																		   XORSTR("xxxx????x"));
	uintptr_t movedata_instruction_addr = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																			 (unsigned char*) XORSTR("\x48\x8B\x0D"
																											 "\x00\x00\x00\x00"
																											 "\x4C\x89\xEA"),
																			 XORSTR("xxx????xxx"));

	nPredictionRandomSeed = *reinterpret_cast<int**>(GetAbsoluteAddress(seed_instruction_addr, 3, 7));
	moveHelper = *reinterpret_cast<IMoveHelper**>(GetAbsoluteAddress(helper_instruction_addr + 1, 3, 7));
	g_MoveData = **reinterpret_cast<CMoveData***>(GetAbsoluteAddress(movedata_instruction_addr, 3, 7));
}

void Hooker::FindSetLocalPlayerReady()
{
	// xref: "deferred"
	uintptr_t func_address = PatternFinder::FindPatternInModule((XORSTR("client_panorama_client.so")),    
																(unsigned char*) XORSTR("\x55\x48\x89\xF7\x48\x8D\x35\x00\x00\x00\x00\x48\x89\xE5\xE8\x00\x00\x00\x00\x85\xC0"),
																XORSTR("xxxxxxx????xxxx????xx"));

	SetLocalPlayerReady = reinterpret_cast<SetLocalPlayerReadyFn>(func_address);
}

void Hooker::FindSurfaceDrawing()
{
	uintptr_t start_func_address = PatternFinder::FindPatternInModule(XORSTR("vguimatsurface_client.so"),
																	  (unsigned char*) XORSTR("\x55\x48\x89\xE5\x53\x48\x89\xFB\x48\x83\xEC\x28\x80\x3D"),
																	  XORSTR("xxxxxxxxxxxxxx"));
	StartDrawing = reinterpret_cast<StartDrawingFn>(start_func_address);

	uintptr_t finish_func_address = PatternFinder::FindPatternInModule(XORSTR("vguimatsurface_client.so"),
																	   (unsigned char*) XORSTR("\x55\x31\xFF\x48\x89\xE5\x53"),
																	   XORSTR("xxxxxxx"));
	FinishDrawing = reinterpret_cast<FinishDrawingFn>(finish_func_address);
}

void Hooker::FindGetLocalClient()
{
	uintptr_t GetLocalPlayer = reinterpret_cast<uintptr_t>(getvtable(engine)[12]);
	GetLocalClient = reinterpret_cast<GetLocalClientFn>(GetAbsoluteAddress(GetLocalPlayer + 9, 1, 5));
}

void Hooker::FindLineGoesThroughSmoke()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																(unsigned char*) XORSTR("\x40\x0F\xB6\xFF\x55"),
																XORSTR("xxxxx"));
	LineGoesThroughSmoke = reinterpret_cast<LineGoesThroughSmokeFn>(func_address);
}

void Hooker::FindInitKeyValues()
{
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																(unsigned char*) XORSTR("\x81\x27\x00\x00\x00\xFF\x55\x31\xC0\x48\x89\xE5\x5D"),
																XORSTR("xxxxxxxxxxxxx"));
	InitKeyValues = reinterpret_cast<InitKeyValuesFn>(func_address);
}

void Hooker::FindLoadFromBuffer()
{
	// xref "%s.ctx" to ReadEncryptedKVFile()
	// LoadFromBuffer is called near the end, right before _MemFreeScratch()
	// 55 48 89 E5 41 57 41 56 41 55 41 54 49 89 D4 53 48 81 EC ?? ?? ?? ?? 48 85
	// Start of LoadFromBuffer()
	// 55                      push    rbp
	// 48 89 E5                mov     rbp, rsp
	// 41 57                   push    r15
	// 41 56                   push    r14
	// 41 55                   push    r13
	// 41 54                   push    r12
	// 49 89 D4                mov     r12, rdx
	// 53                      push    rbx
	// 48 81 EC 88 00 00 00    sub     rsp, 88h
	// 48 85 D2                test    rdx, rdx
	uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																(unsigned char*) XORSTR("\x55"
																						"\x48\x89\xE5"
																						"\x41\x57"
																						"\x41\x56"
																						"\x41\x55"
																						"\x41\x54"
																						"\x49\x89\xD4"
																						"\x53"
																						"\x48\x81\xEC\x00\x00\x00\x00"
																						"\x48\x85"),
																XORSTR("xxxxxxxxxxxxxxxxxxx????xx"));
	LoadFromBuffer = reinterpret_cast<LoadFromBufferFn>(func_address);
}
/*
void Hooker::FindVstdlibFunctions()
{
	void* handle = dlopen(XORSTR("./bin/linux64/libvstdlib_client.so"), RTLD_NOLOAD | RTLD_NOW);

	RandomSeed = reinterpret_cast<RandomSeedFn>(dlsym(handle, XORSTR("RandomSeed")));
	RandomFloat = reinterpret_cast<RandomFloatFn>(dlsym(handle, XORSTR("RandomFloat")));
	RandomFloatExp = reinterpret_cast<RandomFloatExpFn>(dlsym(handle, XORSTR("RandomFloatExp")));
	RandomInt = reinterpret_cast<RandomIntFn>(dlsym(handle, XORSTR("RandomInt")));
	RandomGaussianFloat = reinterpret_cast<RandomGaussianFloatFn>(dlsym(handle, XORSTR("RandomGaussianFloat")));

	dlclose(handle);
}
 */

void Hooker::FindOverridePostProcessingDisable()
{
	uintptr_t bool_address = PatternFinder::FindPatternInModule(XORSTR("client_panorama_client.so"),
																(unsigned char*) XORSTR("\x80\x3D"
                                                                                                "\x00\x00\x00\x00\x00"
                                                                                                "\x89\xB5"
                                                                                                "\x00\x00"
                                                                                                "\xFF\xFF"),
																XORSTR("xx?????xx??xx"));
	bool_address = GetAbsoluteAddress(bool_address, 2, 7);

	s_bOverridePostProcessingDisable = reinterpret_cast<bool*>(bool_address);
}

void Hooker::HookSwapWindow()
{
	uintptr_t swapwindowFn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, XORSTR("SDL_GL_SwapWindow")));
	swapWindowJumpAddress = reinterpret_cast<uintptr_t*>(GetAbsoluteAddress(swapwindowFn, 3, 7));
	oSwapWindow = *swapWindowJumpAddress;
	*swapWindowJumpAddress = reinterpret_cast<uintptr_t>(&SDL2::SwapWindow);
}

void Hooker::HookPollEvent()
{
	uintptr_t polleventFn = reinterpret_cast<uintptr_t>(dlsym(RTLD_NEXT, XORSTR("SDL_PollEvent")));
	polleventJumpAddress = reinterpret_cast<uintptr_t*>(GetAbsoluteAddress(polleventFn, 3, 7));
	oPollEvent = *polleventJumpAddress;
	*polleventJumpAddress = reinterpret_cast<uintptr_t>(&SDL2::PollEvent);
}

void Hooker::FindSDLInput()
{
	/*
	    0F 95 83 AC 01 00 00    setnz   byte ptr [rbx+1ACh]
		E8 E2 B7 FF FF          call    _memcpy
		E8 FD D8 02 00          call    LauncherMgrCreateFunc <------
	 */
	uintptr_t startAddr = PatternFinder::FindPatternInModule(XORSTR("launcher_client.so"),
																(unsigned char*) XORSTR("\x0F\x95\x83"
																								"\x00\x00\x00\x00"
																								"\xE8"
																								"\x00\x00\x00\x00"
																								"\xE8"),
																XORSTR("xxx????x????x"));
	ILauncherMgrCreateFn createFunc = reinterpret_cast<ILauncherMgrCreateFn>(GetAbsoluteAddress(startAddr + 12, 1, 5));
	launcherMgr = createFunc();
}

void Hooker::FindSetNamedSkybox()
{
	//55 4C 8D 05 ?? ?? ?? ?? 48 89 E5 41
    // xref for "skybox/%s%s"
    uintptr_t func_address = PatternFinder::FindPatternInModule(XORSTR("engine_client.so"),
                                                                (unsigned char*) XORSTR("\x55\x4C\x8D\x05"
                                                                                                "\x00\x00\x00\x00" //??
                                                                                                "\x48\x89\xE5\x41"),
                                                                XORSTR("xxxx????xxxx"));

    SetNamedSkyBox = reinterpret_cast<SetNamedSkyBoxFn>(func_address);
}

void Hooker::FindPanelArrayOffset()
{
	/*
	 * CUIEngine::IsValidPanelPointer()
	 *
	   55                      push    rbp
	   48 81 C7 B8 01 00 00    add     rdi, 1B8h <--------
	 */
	uintptr_t IsValidPanelPointer = reinterpret_cast<uintptr_t>(getvtable( panoramaEngine->AccessUIEngine() )[37]);
	int32_t offset = *(unsigned int*)(IsValidPanelPointer + 4);
	panorama::panelArray = *(panorama::PanelArray**) ( ((uintptr_t)panoramaEngine->AccessUIEngine()) + offset + 8);
}

void Hooker::FindPlayerAnimStateOffset()
{
	// In C_CSPlayer::Spawn, it references the offset of each player's animation state so it can do a reset.
	// mov     rdi, [rbx+4148h] <----- this offset(0x4148)
	// test    rdi, rdi
	// jz      short loc_C50837
	// call    AnimState__Reset
	// 55 48 89 E5 53 48 89 FB 48 83 EC 28 48 8B 05 ?? ?? ?? ?? 48 8B 00
	uintptr_t C_CSPlayer__Spawn = PatternFinder::FindPatternInModule( XORSTR( "client_panorama_client.so" ),
																	  ( unsigned char* ) XORSTR("\x55\x48\x89\xE5\x53\x48\x89\xFB\x48\x83\xEC\x28\x48\x8B\x05"
																										"\x00\x00\x00\x00" //??
																										"\x48\x8B\x00"),
																	  XORSTR( "xxxxxxxxxxxxxxx????xxx" ) );
	Offsets::playerAnimStateOffset = *(unsigned int*)(C_CSPlayer__Spawn + 52);
}

void Hooker::FindPlayerAnimOverlayOffset( )
{
    // C_BaseAnimatingOverlay::GetAnimOverlay - Adding 35 to get to the offset
    // 55 48 89 E5 41 56 41 55 41 89 F5 41 54 53 48 89 FB 8B
    Offsets::playerAnimOverlayOffset = *(unsigned int*)(PatternFinder::FindPatternInModule( XORSTR( "client_panorama_client.so" ),
                                                                               ( unsigned char* ) XORSTR("\x55\x48\x89\xE5\x41\x56\x41\x55\x41\x89\xF5\x41\x54\x53\x48\x89\xFB\x8B"),
                                                                               XORSTR( "xxxxxxxxxxxxxxxxxx" ) ) + 35);
}

void Hooker::FindSequenceActivity()
{
    // C_BaseAnimating::GetSequenceActivity()
    // 83 FE FF                                cmp     esi, 0FFFFFFFFh
    // 74 6B                                   jz      short loc_7A1F40
    // 55                                      push    rbp
    // 48 89 E5                                mov     rbp, rsp
    // 53                                      push    rbx
    // 48 89 FB                                mov     rbx, rdi
    // 48 83 EC 18                             sub     rsp, 18h
    // 48 8B BF D0 2F 00 00                    mov     rdi, [rdi+2FD0h]
    // 48 85 FF                                test    rdi, rdi
    // 74 13                                   jz      short loc_7A1F00
    // loc_7A1EED:                             ; CODE XREF: GetSequenceActivity+5F↓j
    // 48 83 3F 00                             cmp     qword ptr [rdi], 0
    // 74 3E                                   jz      short loc_7A1F31
    // 48 83 C4 18                             add     rsp, 18h
    // 31 D2                                   xor     edx, edx
    // 83 FE FF 74 ?? 55 48 89 E5 53 48 89 FB 48 83 EC ?? 48 8B BF ?? ?? ?? ?? 48 85 FF 74 ?? 48 83 3F 00 74 ?? 48 83 C4 ?? 31
    uintptr_t funcAddr = PatternFinder::FindPatternInModule( XORSTR( "client_panorama_client.so" ), (unsigned char*) XORSTR( "\x83\xFE\xFF"
                                                                                                            "\x74\x00"
                                                                                                            "\x55"
                                                                                                            "\x48\x89\xE5"
                                                                                                            "\x53"
                                                                                                            "\x48\x89\xFB"
                                                                                                            "\x48\x83\xEC\x00"
                                                                                                            "\x48\x8B\xBF\x00\x00\x00\x00"
                                                                                                            "\x48\x85\xFF"
                                                                                                            "\x74\x00"
                                                                                                            "\x48\x83\x3F\x00"
                                                                                                            "\x74\x00"
                                                                                                            "\x48\x83\xC4\x00"
                                                                                                            "\x31"), XORSTR( "xxxx?xxxxxxxxxxx?xxx????xxxx?xxxxx?xxx?x" ) );

    GetSeqActivity = reinterpret_cast<GetSequenceActivityFn>( funcAddr );
}

void Hooker::FindAbsFunctions()
{
	// C_BaseEntity::SetAbsOrigin( )
	// 55 48 89 E5 41 55 41 54 49 89 F4 53 48 89 FB 48 83 EC ?? E8 ?? ?? ?? ?? F3
	SetAbsOriginFnAddr = PatternFinder::FindPatternInModule( XORSTR( "client_panorama_client.so" ),
															 ( unsigned char* ) XORSTR("\x55\x48\x89\xE5\x41\x55\x41\x54\x49\x89\xF4\x53\x48\x89\xFB\x48\x83\xEC"
																							   "\x00" //??
																							   "\xE8"
																							   "\x00\x00\x00\x00" //??
																							   "\xF3"),
															 XORSTR( "xxxxxxxxxxxxxxxxxx?x????x" ) );
}

typedef CItemSystem* (* GetItemSystemFn)( );

void Hooker::FindItemSystem()
{
    //xref almost any weapon name "weapon_glock" or "weapon_ak47"
    //above the string find a very commonly used function that has about 100xrefs
    // ItemSystem() proc near
    // 55                      push    rbp
    // 48 89 E5                mov     rbp, rsp
    // 53                      push    rbx
    // 48 89 FB                mov     rbx, rdi
    // 48 83 EC 08             sub     rsp, 8
    // 48 89 37                mov     [rdi], rsi
    // E8 9C 69 E3 FF          call    GetItemSystemWrapper
    // 48 8B 33                mov     rsi, [rbx]
    // 48 8B 10                mov     rdx, [rax]
    // 48 89 C7                mov     rdi, rax
    // FF 92 48 01 00 00       call    qword ptr [rdx+148h]
    // 48 89 43 08             mov     [rbx+8], rax
    // E8 84 69 E3 FF          call    GetItemSystemWrapper
    // 8B 40 3C                mov     eax, [rax+3Ch]
    // 89 43 10                mov     [rbx+10h], eax
    // 48 83 C4 08             add     rsp, 8
    // 5B                      pop     rbx
    // 5D                      pop     rbp
    // C3                      retn
    // -- GetItemSystemWrapper() --
    // 55                      push    rbp
    // 48 89 E5                mov     rbp, rsp
    // E8 87 FB FD FF          call    GetItemSystem
    // 5D                      pop     rbp
    // 48 83 C0 08             add     rax, 8
    // C3                      retn


	uintptr_t funcAddr = PatternFinder::FindPatternInModule( XORSTR( "client_panorama_client.so" ), (unsigned char*) XORSTR("\x55\x48\x89\xE5\x53\x48\x89\xFB\x48\x83\xEC\x08\x48\x89\x37\xE8"
																									"\x00\x00\x00\x00" // ??
																									"\x48"), XORSTR( "xxxxxxxxxxxxxxxx????x" ) );
    funcAddr += 15; // add 15 to get to (E8 9C 69 E3 FF          call    GetItemSystemWrapper)
    funcAddr = GetAbsoluteAddress( funcAddr, 1, 5 ); // Deref to GetItemSystemWrapper()
    funcAddr += 4; // add 4 to Get to GetItemSystem()
    funcAddr = GetAbsoluteAddress( funcAddr, 1, 5 ); // Deref again for the final address.


    GetItemSystemFn GetItemSystem = reinterpret_cast<GetItemSystemFn>( funcAddr );
	uintptr_t itemSys = (uintptr_t)GetItemSystem();
	cvar->ConsoleDPrintf("ItemSystem(%p)\n", itemSys);
	itemSys += sizeof(void*); // 2nd vtable
    itemSystem = (CItemSystem*)itemSys;
}