#include "antiaim.h"

bool Settings::AntiAim::Yaw::enabled = false;
bool Settings::AntiAim::Pitch::enabled = false;
AntiAimType_Y Settings::AntiAim::Yaw::type = AntiAimType_Y::SPIN_FAST;
AntiAimType_Y Settings::AntiAim::Yaw::typeFake = AntiAimType_Y::SPIN_FAST;
bool Settings::AntiAim::Yaw::antiResolver = false;
AntiAimType_X Settings::AntiAim::Pitch::type = AntiAimType_X::STATIC_DOWN;
bool Settings::AntiAim::HeadEdge::enabled = false;
float Settings::AntiAim::HeadEdge::distance = 25.0f;
bool Settings::AntiAim::AutoDisable::noEnemy = false;
bool Settings::AntiAim::AutoDisable::knifeHeld = false;

bool Settings::AntiAim::Lua::debugMode = true;
char Settings::AntiAim::Lua::scriptX[512];
char Settings::AntiAim::Lua::scriptY[512];
char Settings::AntiAim::Lua::scriptY2[512];
// if the script is the same, we can skip some initialization.
char luaLastX[sizeof(Settings::AntiAim::Lua::scriptX)];
char luaLastY[sizeof(Settings::AntiAim::Lua::scriptY)];
char luaLastY2[sizeof(Settings::AntiAim::Lua::scriptY2)];
float luaRetX, luaRetY, luaRetY2; // Pop the Lua stack off into these and then return them.

lua_State *LuaX, *LuaY, *LuaY2; // 1 instance of Lua for each Script.

static float Distance(Vector a, Vector b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

static bool GetBestHeadAngle(QAngle& angle)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

	Vector position = localplayer->GetVecOrigin() + localplayer->GetVecViewOffset();

	float closest_distance = 100.0f;

	float radius = Settings::AntiAim::HeadEdge::distance + 0.1f;
	float step = M_PI * 2.0 / 8;

	for (float a = 0; a < (M_PI * 2.0); a += step)
	{
		Vector location(radius * cos(a) + position.x, radius * sin(a) + position.y, position.z);

		Ray_t ray;
		trace_t tr;
		ray.Init(position, location);
		CTraceFilter traceFilter;
		traceFilter.pSkip = localplayer;
		trace->TraceRay(ray, 0x4600400B, &traceFilter, &tr);

		float distance = Distance(position, tr.endpos);

		if (distance < closest_distance)
		{
			closest_distance = distance;
			angle.y = RAD2DEG(a);
		}
	}

	return closest_distance < Settings::AntiAim::HeadEdge::distance;
}
void AntiAim::LuaInit() // commence nigg riggin'
{
	// Fill out the structure of the Lua scripts
	Settings::AntiAim::Lua::scriptX[0] =  'f';
	Settings::AntiAim::Lua::scriptX[1] =  'u';
	Settings::AntiAim::Lua::scriptX[2] =  'n';
	Settings::AntiAim::Lua::scriptX[3] =  'c';
	Settings::AntiAim::Lua::scriptX[4] =  't';
	Settings::AntiAim::Lua::scriptX[5] =  'i';
	Settings::AntiAim::Lua::scriptX[6] =  'o';
	Settings::AntiAim::Lua::scriptX[7] =  'n';
	Settings::AntiAim::Lua::scriptX[8] =  ' ';
	Settings::AntiAim::Lua::scriptX[9] =  'a';
	Settings::AntiAim::Lua::scriptX[10] = 'n';
	Settings::AntiAim::Lua::scriptX[11] = 'g';
	Settings::AntiAim::Lua::scriptX[12] = 'l';
	Settings::AntiAim::Lua::scriptX[13] = 'e';
	Settings::AntiAim::Lua::scriptX[14] = 'X';
	Settings::AntiAim::Lua::scriptX[15] = '(';
	Settings::AntiAim::Lua::scriptX[16] = 'l';
	Settings::AntiAim::Lua::scriptX[17] = 'a';
	Settings::AntiAim::Lua::scriptX[18] = 's';
	Settings::AntiAim::Lua::scriptX[19] = 't';
	Settings::AntiAim::Lua::scriptX[20] = 'A';
	Settings::AntiAim::Lua::scriptX[21] = 'n';
	Settings::AntiAim::Lua::scriptX[22] = 'g';
	Settings::AntiAim::Lua::scriptX[23] = 'l';
	Settings::AntiAim::Lua::scriptX[24] = 'e';
	Settings::AntiAim::Lua::scriptX[25] = ',';
	Settings::AntiAim::Lua::scriptX[26] = ' ';
	Settings::AntiAim::Lua::scriptX[27] = 'a';
	Settings::AntiAim::Lua::scriptX[28] = 'n';
	Settings::AntiAim::Lua::scriptX[29] = 'g';
	Settings::AntiAim::Lua::scriptX[30] = 'l';
	Settings::AntiAim::Lua::scriptX[31] = 'e';
	Settings::AntiAim::Lua::scriptX[32] = ')';
	Settings::AntiAim::Lua::scriptX[33] = '\n';
	Settings::AntiAim::Lua::scriptX[34] = '\n';
	Settings::AntiAim::Lua::scriptX[35] = 'r';
	Settings::AntiAim::Lua::scriptX[36] = 'e';
	Settings::AntiAim::Lua::scriptX[37] = 't';
	Settings::AntiAim::Lua::scriptX[38] = 'u';
	Settings::AntiAim::Lua::scriptX[39] = 'r';
	Settings::AntiAim::Lua::scriptX[40] = 'n';
	Settings::AntiAim::Lua::scriptX[41] = ' ';
	Settings::AntiAim::Lua::scriptX[42] = 'a';
	Settings::AntiAim::Lua::scriptX[43] = 'n';
	Settings::AntiAim::Lua::scriptX[44] = 'g';
	Settings::AntiAim::Lua::scriptX[45] = 'l';
	Settings::AntiAim::Lua::scriptX[46] = 'e';
	Settings::AntiAim::Lua::scriptX[47] = ';';
	Settings::AntiAim::Lua::scriptX[48] = '\n';
	Settings::AntiAim::Lua::scriptX[49] = 'e';
	Settings::AntiAim::Lua::scriptX[50] = 'n';
	Settings::AntiAim::Lua::scriptX[51] = 'd';
	Settings::AntiAim::Lua::scriptX[sizeof(Settings::AntiAim::Lua::scriptX)-1] = '\0';

	Settings::AntiAim::Lua::scriptY[0] =  'f';
	Settings::AntiAim::Lua::scriptY[1] =  'u';
	Settings::AntiAim::Lua::scriptY[2] =  'n';
	Settings::AntiAim::Lua::scriptY[3] =  'c';
	Settings::AntiAim::Lua::scriptY[4] =  't';
	Settings::AntiAim::Lua::scriptY[5] =  'i';
	Settings::AntiAim::Lua::scriptY[6] =  'o';
	Settings::AntiAim::Lua::scriptY[7] =  'n';
	Settings::AntiAim::Lua::scriptY[8] =  ' ';
	Settings::AntiAim::Lua::scriptY[9] =  'a';
	Settings::AntiAim::Lua::scriptY[10] = 'n';
	Settings::AntiAim::Lua::scriptY[11] = 'g';
	Settings::AntiAim::Lua::scriptY[12] = 'l';
	Settings::AntiAim::Lua::scriptY[13] = 'e';
	Settings::AntiAim::Lua::scriptY[14] = 'Y';
	Settings::AntiAim::Lua::scriptY[15] = '(';
	Settings::AntiAim::Lua::scriptY[16] = 'l';
	Settings::AntiAim::Lua::scriptY[17] = 'a';
	Settings::AntiAim::Lua::scriptY[18] = 's';
	Settings::AntiAim::Lua::scriptY[19] = 't';
	Settings::AntiAim::Lua::scriptY[20] = 'A';
	Settings::AntiAim::Lua::scriptY[21] = 'n';
	Settings::AntiAim::Lua::scriptY[22] = 'g';
	Settings::AntiAim::Lua::scriptY[23] = 'l';
	Settings::AntiAim::Lua::scriptY[24] = 'e';
	Settings::AntiAim::Lua::scriptY[25] = ',';
	Settings::AntiAim::Lua::scriptY[26] = ' ';
	Settings::AntiAim::Lua::scriptY[27] = 'a';
	Settings::AntiAim::Lua::scriptY[28] = 'n';
	Settings::AntiAim::Lua::scriptY[29] = 'g';
	Settings::AntiAim::Lua::scriptY[30] = 'l';
	Settings::AntiAim::Lua::scriptY[31] = 'e';
	Settings::AntiAim::Lua::scriptY[32] = ')';
	Settings::AntiAim::Lua::scriptY[33] = '\n';
	Settings::AntiAim::Lua::scriptY[34] = '\n';
	Settings::AntiAim::Lua::scriptY[35] = 'r';
	Settings::AntiAim::Lua::scriptY[36] = 'e';
	Settings::AntiAim::Lua::scriptY[37] = 't';
	Settings::AntiAim::Lua::scriptY[38] = 'u';
	Settings::AntiAim::Lua::scriptY[39] = 'r';
	Settings::AntiAim::Lua::scriptY[40] = 'n';
	Settings::AntiAim::Lua::scriptY[41] = ' ';
	Settings::AntiAim::Lua::scriptY[42] = 'a';
	Settings::AntiAim::Lua::scriptY[43] = 'n';
	Settings::AntiAim::Lua::scriptY[44] = 'g';
	Settings::AntiAim::Lua::scriptY[45] = 'l';
	Settings::AntiAim::Lua::scriptY[46] = 'e';
	Settings::AntiAim::Lua::scriptY[47] = ';';
	Settings::AntiAim::Lua::scriptY[48] = '\n';
	Settings::AntiAim::Lua::scriptY[49] = 'e';
	Settings::AntiAim::Lua::scriptY[50] = 'n';
	Settings::AntiAim::Lua::scriptY[51] = 'd';
	Settings::AntiAim::Lua::scriptY[sizeof(Settings::AntiAim::Lua::scriptY)-1] = '\0';

	Settings::AntiAim::Lua::scriptY2[0] =  'f';
	Settings::AntiAim::Lua::scriptY2[1] =  'u';
	Settings::AntiAim::Lua::scriptY2[2] =  'n';
	Settings::AntiAim::Lua::scriptY2[3] =  'c';
	Settings::AntiAim::Lua::scriptY2[4] =  't';
	Settings::AntiAim::Lua::scriptY2[5] =  'i';
	Settings::AntiAim::Lua::scriptY2[6] =  'o';
	Settings::AntiAim::Lua::scriptY2[7] =  'n';
	Settings::AntiAim::Lua::scriptY2[8] =  ' ';
	Settings::AntiAim::Lua::scriptY2[9] =  'a';
	Settings::AntiAim::Lua::scriptY2[10] = 'n';
	Settings::AntiAim::Lua::scriptY2[11] = 'g';
	Settings::AntiAim::Lua::scriptY2[12] = 'l';
	Settings::AntiAim::Lua::scriptY2[13] = 'e';
	Settings::AntiAim::Lua::scriptY2[14] = 'Y';
	Settings::AntiAim::Lua::scriptY2[15] = '2';
	Settings::AntiAim::Lua::scriptY2[16] = '(';
	Settings::AntiAim::Lua::scriptY2[17] = 'l';
	Settings::AntiAim::Lua::scriptY2[18] = 'a';
	Settings::AntiAim::Lua::scriptY2[19] = 's';
	Settings::AntiAim::Lua::scriptY2[20] = 't';
	Settings::AntiAim::Lua::scriptY2[21] = 'A';
	Settings::AntiAim::Lua::scriptY2[22] = 'n';
	Settings::AntiAim::Lua::scriptY2[23] = 'g';
	Settings::AntiAim::Lua::scriptY2[24] = 'l';
	Settings::AntiAim::Lua::scriptY2[25] = 'e';
	Settings::AntiAim::Lua::scriptY2[26] = ',';
	Settings::AntiAim::Lua::scriptY2[27] = ' ';
	Settings::AntiAim::Lua::scriptY2[28] = 'a';
	Settings::AntiAim::Lua::scriptY2[29] = 'n';
	Settings::AntiAim::Lua::scriptY2[30] = 'g';
	Settings::AntiAim::Lua::scriptY2[31] = 'l';
	Settings::AntiAim::Lua::scriptY2[32] = 'e';
	Settings::AntiAim::Lua::scriptY2[33] = ')';
	Settings::AntiAim::Lua::scriptY2[34] = '\n';
	Settings::AntiAim::Lua::scriptY2[35] = '\n';
	Settings::AntiAim::Lua::scriptY2[36] = 'r';
	Settings::AntiAim::Lua::scriptY2[37] = 'e';
	Settings::AntiAim::Lua::scriptY2[38] = 't';
	Settings::AntiAim::Lua::scriptY2[39] = 'u';
	Settings::AntiAim::Lua::scriptY2[40] = 'r';
	Settings::AntiAim::Lua::scriptY2[41] = 'n';
	Settings::AntiAim::Lua::scriptY2[42] = ' ';
	Settings::AntiAim::Lua::scriptY2[43] = 'a';
	Settings::AntiAim::Lua::scriptY2[44] = 'n';
	Settings::AntiAim::Lua::scriptY2[45] = 'g';
	Settings::AntiAim::Lua::scriptY2[46] = 'l';
	Settings::AntiAim::Lua::scriptY2[47] = 'e';
	Settings::AntiAim::Lua::scriptY2[48] = ';';
	Settings::AntiAim::Lua::scriptY2[49] = '\n';
	Settings::AntiAim::Lua::scriptY2[50] = 'e';
	Settings::AntiAim::Lua::scriptY2[51] = 'n';
	Settings::AntiAim::Lua::scriptY2[52] = 'd';
	Settings::AntiAim::Lua::scriptY2[sizeof(Settings::AntiAim::Lua::scriptY2)-1] = '\0';

	luaLastX[sizeof(luaLastX) -1] = '\0';
	luaLastY[sizeof(luaLastY) -1] = '\0';
	luaLastY2[sizeof(luaLastY2) -1] = '\0';

	LuaX = luaL_newstate();
	luaL_openlibs(LuaX);

	LuaY = luaL_newstate();
	luaL_openlibs(LuaY);

	LuaY2 = luaL_newstate();
	luaL_openlibs(LuaY2);

}
void AntiAim::LuaCleanup()
{
	lua_close(LuaX);
	lua_close(LuaY);
	lua_close(LuaY2);
}
static void LuaError( int errorCode, lua_State *luaInstance )
{
	switch( errorCode ){ // defined in lua.h
		case 2: // Runtime Error.
			cvar->ConsoleDPrintf(XORSTR("LUA: Runtime Error: %s\n"), lua_tostring(luaInstance, -1));
			break;
		case 3: // Syntax error.
			cvar->ConsoleDPrintf(XORSTR("LUA: Syntax Error: %s\n"), lua_tostring(luaInstance, -1));
			break;
		case 4: // Memory Allocation error.
			cvar->ConsoleDPrintf(XORSTR("LUA: Memory Alloc Error: %s\n"), lua_tostring(luaInstance, -1));
			break;
		case 6: // Error while returning Error Code
			cvar->ConsoleDPrintf(XORSTR("LUA: Error returning Error: %s\n"), lua_tostring(luaInstance, -1));
			break;
		default: // Unknown.
			cvar->ConsoleDPrintf(XORSTR("LUA: Unknown Error: %s\n"), lua_tostring(luaInstance, -1));
			break;
	}
}
static inline float LuaScriptX(const float lastAngle, const float angle)
{
	if( Settings::AntiAim::Lua::debugMode ){
		if( strcmp(Settings::AntiAim::Lua::scriptX, luaLastX) != 0 ){
			int load_status = luaL_loadbuffer(LuaX, Settings::AntiAim::Lua::scriptX, strlen(Settings::AntiAim::Lua::scriptX), Settings::AntiAim::Lua::scriptX);
			if( load_status != 0 ){
				cvar->ConsoleDPrintf(XORSTR("LUA: Error Loading Buffer\n"));
				LuaError(load_status, LuaX);
				return angle;
			}
			lua_pcall(LuaX, 0, 0, 0); // load the script with no args for function setup.
			cvar->ConsoleDPrintf(XORSTR("Updating ScriptX\n"));
			strncpy( luaLastX, Settings::AntiAim::Lua::scriptX, sizeof(luaLastX) );
		}
		lua_getglobal(LuaX, XORSTR("angleX"));
		lua_pushnumber(LuaX, lastAngle); // give Angle from last tick to Lua.
		lua_pushnumber(LuaX, angle); // give current Angle to Lua.
		int run_status = lua_pcall(LuaX, 2, 1, 0); // pcall :^)
		if( run_status != 0 ){
			LuaError(run_status, LuaX);
			return angle;
		}
		if( !lua_isnumber(LuaX, -1) ) {
			cvar->ConsoleDPrintf(XORSTR("LUA: Your LUA script must return a Number!\n"));
			return angle;
		}
		luaRetX = (float)lua_tonumber(LuaX, -1); // By default lua_number is a double, can be changed in luaconf.h
		lua_pop(LuaX, 1); // pop the returned value off of the stack.
		return luaRetX;
	} else {
		if( strcmp(Settings::AntiAim::Lua::scriptX, luaLastX) != 0 ){
			luaL_loadbuffer(LuaX, Settings::AntiAim::Lua::scriptX, strlen(Settings::AntiAim::Lua::scriptX), Settings::AntiAim::Lua::scriptX);
			lua_pcall(LuaX, 0, 0, 0);
			strncpy( luaLastX, Settings::AntiAim::Lua::scriptX, sizeof(luaLastX) );
		}
		lua_getglobal(LuaX, XORSTR("angleX"));
		lua_pushnumber(LuaX, lastAngle); // give Angle from last tick to Lua.
		lua_pushnumber(LuaX, angle); // give current Angle to Lua.
		lua_pcall(LuaX, 2, 1, 0);
		luaRetX = (float)lua_tonumber(LuaX, -1); // By default lua_number is a double, can be changed in luaconf.h
		lua_pop(LuaX, 1); // pop the returned value off of the stack.
		return luaRetX;
	}

}

static inline float LuaScriptY(const float lastAngle, const float angle)
{
	if( Settings::AntiAim::Lua::debugMode ){
		if( strcmp(Settings::AntiAim::Lua::scriptY, luaLastY) != 0 ){
			int load_status = luaL_loadbuffer(LuaY, Settings::AntiAim::Lua::scriptY, strlen(Settings::AntiAim::Lua::scriptY), Settings::AntiAim::Lua::scriptY);
			if( load_status != 0 ){
				cvar->ConsoleDPrintf(XORSTR("LUA: Error Loading Buffer\n"));
				LuaError(load_status, LuaY);
				return angle;
			}
			lua_pcall(LuaY, 0, 0, 0); // load the script with no args for function setup.
			cvar->ConsoleDPrintf(XORSTR("Updating ScriptY\n"));
			strncpy( luaLastY, Settings::AntiAim::Lua::scriptY, sizeof(luaLastY) );
		}
		lua_getglobal(LuaY, XORSTR("angleY"));
		lua_pushnumber(LuaY, lastAngle); // give Angle from last tick to Lua.
		lua_pushnumber(LuaY, angle); // give current Angle to Lua.
		int run_status = lua_pcall(LuaY, 2, 1, 0); // pcall :^)
		if( run_status != 0 ){
			LuaError(run_status, LuaY);
			return angle;
		}
		if( !lua_isnumber(LuaY, -1) ) {
			cvar->ConsoleDPrintf(XORSTR("LUA: Your LUA script must return a Number!\n"));
			return angle;
		}
		luaRetY = (float)lua_tonumber(LuaY, -1); // By default lua_number is a double, can be changed in luaconf.h
		lua_pop(LuaY, 1); // pop the returned value off of the stack.
		return luaRetY;
	} else {
		if( strcmp(Settings::AntiAim::Lua::scriptY, luaLastY) != 0 ){
			luaL_loadbuffer(LuaY, Settings::AntiAim::Lua::scriptY, strlen(Settings::AntiAim::Lua::scriptY), Settings::AntiAim::Lua::scriptY);
			lua_pcall(LuaY, 0, 0, 0);
			strncpy( luaLastY, Settings::AntiAim::Lua::scriptY, sizeof(luaLastY) );
		}
		lua_getglobal(LuaY, XORSTR("angleY"));
		lua_pushnumber(LuaY, lastAngle); // give Angle from last tick to Lua.
		lua_pushnumber(LuaY, angle); // give current Angle to Lua.
		lua_pcall(LuaY, 2, 1, 0);
		luaRetY = (float)lua_tonumber(LuaY, -1); // By default lua_number is a double, can be changed in luaconf.h
		lua_pop(LuaY, 1); // pop the returned value off of the stack.
		return luaRetY;
	}
}

static inline float LuaScriptY2(const float lastAngle, const float angle)
{
	if( Settings::AntiAim::Lua::debugMode ){
		if( strcmp(Settings::AntiAim::Lua::scriptY2, luaLastY2) != 0 ){
			int load_status = luaL_loadbuffer(LuaY2, Settings::AntiAim::Lua::scriptY2, strlen(Settings::AntiAim::Lua::scriptY2), Settings::AntiAim::Lua::scriptY2);
			if( load_status != 0 ){
				cvar->ConsoleDPrintf(XORSTR("LUA: Error Loading Buffer\n"));
				LuaError(load_status, LuaY2);
				return angle;
			}
			lua_pcall(LuaY2, 0, 0, 0); // load the script with no args for function setup.
			cvar->ConsoleDPrintf(XORSTR("Updating ScriptY2\n"));
			strncpy( luaLastY2, Settings::AntiAim::Lua::scriptY2, sizeof(luaLastY2) );
		}
		lua_getglobal(LuaY2, XORSTR("angleY2"));
		lua_pushnumber(LuaY2, lastAngle); // give Angle from last tick to Lua.
		lua_pushnumber(LuaY2, angle); // give current Angle to Lua.
		int run_status = lua_pcall(LuaY2, 2, 1, 0); // pcall :^)
		if( run_status != 0 ){
			LuaError(run_status, LuaY2);
			return angle;
		}
		if( !lua_isnumber(LuaY2, -1) ) {
			cvar->ConsoleDPrintf(XORSTR("LUA: Your LUA script must return a Number!\n"));
			return angle;
		}
		luaRetY2 = (float)lua_tonumber(LuaY2, -1); // By default lua_number is a double, can be changed in luaconf.h
		lua_pop(LuaY2, 1); // pop the returned value off of the stack.
		return luaRetY2;
	} else {
		if( strcmp(Settings::AntiAim::Lua::scriptY2, luaLastY2) != 0 ){
			luaL_loadbuffer(LuaY2, Settings::AntiAim::Lua::scriptY2, strlen(Settings::AntiAim::Lua::scriptY2), Settings::AntiAim::Lua::scriptY2);
			lua_pcall(LuaY2, 0, 0, 0);
			strncpy( luaLastY2, Settings::AntiAim::Lua::scriptY2, sizeof(luaLastY2) );
		}
		lua_getglobal(LuaY2, XORSTR("angleY2"));
		lua_pushnumber(LuaY2, lastAngle); // give Angle from last tick to Lua.
		lua_pushnumber(LuaY2, angle); // give current Angle to Lua.
		lua_pcall(LuaY2, 2, 1, 0);
		float temp = (float)lua_tonumber(LuaY2, -1); // By default lua_number is a double, can be changed in luaconf.h
		lua_pop(LuaY2, 1); // pop the returned value off of the stack.
		return temp;
	}
}
static bool HasViableEnemy()
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BasePlayer* entity = (C_BasePlayer*) entityList->GetClientEntity(i);

		if (!entity
			|| entity == localplayer
			|| entity->GetDormant()
			|| !entity->GetAlive()
			|| entity->GetImmune())
			continue;

		if( !Aimbot::friends.empty() ) // check for friends, if any
		{
			IEngineClient::player_info_t entityInformation;
			engine->GetPlayerInfo(i, &entityInformation);

			if (std::find(Aimbot::friends.begin(), Aimbot::friends.end(), entityInformation.xuid) != Aimbot::friends.end())
				continue;
		}

		if (Settings::Aimbot::friendly || entity->GetTeam() != localplayer->GetTeam())
			return true;
	}

	return false;
}
static void DoAntiAimY(QAngle& angle, int command_number, bool bFlip, bool& clamp)
{
	AntiAimType_Y aa_type = bFlip ? Settings::AntiAim::Yaw::typeFake : Settings::AntiAim::Yaw::type;

	static bool yFlip;
	float temp;
	double factor;
	static float trigger;
	QAngle temp_qangle;
	int random;
	int maxJitter;
	static float lastAngleY, lastAngleY2; // angle we had last frame

	yFlip = bFlip != yFlip;

	switch (aa_type)
	{
		case AntiAimType_Y::SPIN_FAST:
			factor =  360.0 / M_PHI;
			factor *= 25;
			angle.y = fmodf(globalVars->curtime * factor, 360.0);
			break;
		case AntiAimType_Y::SPIN_SLOW:
			factor =  360.0 / M_PHI;
			angle.y = fmodf(globalVars->curtime * factor, 360.0);
			break;
		case AntiAimType_Y::JITTER:
			yFlip ? angle.y -= 90.0f : angle.y -= 270.0f;
			break;
		case AntiAimType_Y::BACKJITTER:
			angle.y -= 180;
			random = rand() % 100;
			maxJitter = rand() % (85 - 70 + 1) + 70;
			temp = maxJitter - (rand() % maxJitter);
			if (random < 35 + (rand() % 15))
				angle.y -= temp;
			else if (random < 85 + (rand() % 15 ))
				angle.y += temp;
			break;
		case AntiAimType_Y::SIDE:
			yFlip ? angle.y += 90.f : angle.y -= 90.0f;
			break;
		case AntiAimType_Y::BACKWARDS:
			angle.y -= 180.0f;
			break;
		case AntiAimType_Y::FORWARDS:
			angle.y -= 0.0f;
			break;
		case AntiAimType_Y::LEFT:
			angle.y += 90.0f;
			break;
		case AntiAimType_Y::RIGHT:
			angle.y -= 90.0f;
			break;
		case AntiAimType_Y::STATICAA:
			angle.y = 0.0f;
			break;
		case AntiAimType_Y::STATICJITTER:
			trigger += 15.0f;
			angle.y = trigger > 50.0f ? 150.0f : -150.0f;

			if (trigger > 100.0f)
				trigger = 0.0f;
			break;
		case AntiAimType_Y::STATICSMALLJITTER:
			trigger += 15.0f;
			angle.y = trigger > 50.0f ? -30.0f : 30.0f;

			if (trigger > 100.0f)
				trigger = 0.0f;
			break;
		case AntiAimType_Y::LUA1:
			angle.y = LuaScriptY( lastAngleY, angle.y );
			break;
		case AntiAimType_Y::LUA2:
			angle.y = LuaScriptY2( lastAngleY2, angle.y );
			break;
		case AntiAimType_Y::LISP:
			clamp = false;
			yFlip ? angle.y += 323210000.0f : angle.y -= 323210000.0f;
			break;
		case AntiAimType_Y::LISP_SIDE:
			clamp = false;
			temp = angle.y + 90.0f;
			temp_qangle = QAngle(0.0f, temp, 0.0f);
			Math::NormalizeAngles(temp_qangle);
			temp = temp_qangle.y;

			if (temp > -45.0f)
				temp < 0.0f ? temp = -90.0f : temp < 45.0f ? temp = 90.0f : temp = temp;

			temp += 1800000.0f;
			angle.y = temp;
			break;
		case AntiAimType_Y::LISP_JITTER:
			clamp = false;
			static int jittertimer = -1;
			temp = angle.y - 155.0f;

			if (jittertimer == 1)
			{
				temp = angle.y + 58.0f;
				temp += 1800000.0f;
			}

			if (bSendPacket)
			{
				if (jittertimer >= 1)
					jittertimer = -1;
				jittertimer++;
			}
			angle.y = temp;
			break;
		case AntiAimType_Y::ANGEL_BACKWARD:
			clamp = false;
			angle.y += 36000180.0f;
			break;
		case AntiAimType_Y::ANGEL_INVERSE:
			clamp = false;
			angle.y = 36000180.0f;
			break;
		case AntiAimType_Y::LOWERBODY:
			angle.y = *((C_BasePlayer*)entityList->GetClientEntity(engine->GetLocalPlayer()))->GetLowerBodyYawTarget() + rand()%35 + 165;
			break;
		case AntiAimType_Y::ANGEL_SPIN:
			clamp = false;
			factor = (globalVars->curtime * 5000.0f);
			angle.y = factor + 36000000.0f;
			break;
		case AntiAimType_Y::CASUAL:
			yFlip ? angle.y -= 35.0f : angle.y += 35.0f;
			break;
		case AntiAimType_Y::LUA_UNCLAMPED:
			clamp = false;
			angle.y = LuaScriptY( lastAngleY, angle.y );
			break;
		case AntiAimType_Y::LUA_UNCLAMPED2:
			clamp = false;
			angle.y = LuaScriptY2( lastAngleY2, angle.y );
			break;
		case AntiAimType_Y::LBYONGROUND:
			static C_BasePlayer* player = ((C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer()));
			if (player->GetFlags() & FL_ONGROUND)
				angle.y = *((C_BasePlayer*)entityList->GetClientEntity(engine->GetLocalPlayer()))->GetLowerBodyYawTarget() + rand()%35 + 165;
			else
			{
				static int aimType = rand() % 4;
				switch (aimType)
				{
					case 1:
						yFlip ? angle.y += 90.f : angle.y -= 90.0f;
						break;
					case 2:
						yFlip ? angle.y -= 120.0f : angle.y -= 210.0f;
						break;
					case 3:
						factor =  360.0 / M_PHI;
						factor *= 25;
						angle.y = fmodf(globalVars->curtime * factor, 360.0);
						break;
					default:
						angle.y -= 180.0f;
				}
			}
			break;
		default:
			angle.y -= 0.0f;
			break;
	}
	lastAngleY = angle.y;
	lastAngleY2 = angle.y;
}

static void DoAntiAimX(QAngle& angle, bool bFlip, bool& clamp)
{
	static float pDance = 0.0f;
	static float lastAngleX;
	AntiAimType_X aa_type = Settings::AntiAim::Pitch::type;

	switch (aa_type)
	{
		case AntiAimType_X::STATIC_UP:
			angle.x = -89.0f;
			break;
		case AntiAimType_X::STATIC_DOWN:
			angle.x = 89.0f;
			break;
		case AntiAimType_X::DANCE:
			pDance += 45.0f;
			if (pDance > 100)
				pDance = 0.0f;
			else if (pDance > 75.f)
				angle.x = -89.f;
			else if (pDance < 75.f)
				angle.x = 89.f;
			break;
		case AntiAimType_X::FRONT:
			angle.x = 0.0f;
			break;
		case AntiAimType_X::STATIC_UP_FAKE:
			angle.x = bFlip ? 89.0f : -89.0f;
			break;
		case AntiAimType_X::STATIC_DOWN_FAKE:
			angle.x = bFlip ? -89.0f : 89.0f;
			break;
		case AntiAimType_X::LUA1:
			angle.x = LuaScriptX( lastAngleX, angle.x );
			break;
		case AntiAimType_X::LISP_DOWN:
			clamp = false;
			angle.x = 1800089.0f;
			break;
		case AntiAimType_X::ANGEL_DOWN:
			clamp = false;
			angle.x = 36000088.0f;
			break;
		case AntiAimType_X::ANGEL_UP:
			clamp = false;
			angle.x = 35999912.0f;
			break;
		case AntiAimType_X::LUA_UNCLAMPED:
			clamp = false;
			angle.x = LuaScriptX( lastAngleX, angle.x );
			break;
		default:
			angle.x -= 0.0f;
			break;
	}
	lastAngleX = angle.x;
}

void AntiAim::CreateMove(CUserCmd* cmd)
{
	if (!Settings::AntiAim::Yaw::enabled && !Settings::AntiAim::Pitch::enabled)
		return;

	if (Settings::Aimbot::AimStep::enabled && Aimbot::aimStepInProgress)
		return;

	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!activeWeapon)
		return;

	if (activeWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_GRENADE)
	{
		C_BaseCSGrenade* csGrenade = (C_BaseCSGrenade*) activeWeapon;

		if (csGrenade->GetThrowTime() > 0.f)
			return;
	}

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || (cmd->buttons & IN_ATTACK2 && *activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER))
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	// AutoDisable checks

	// Knife
	if (Settings::AntiAim::AutoDisable::knifeHeld && localplayer->GetAlive() && activeWeapon->GetCSWpnData()->GetWeaponType() == CSWeaponType::WEAPONTYPE_KNIFE)
		return;

	if (Settings::AntiAim::AutoDisable::noEnemy && localplayer->GetAlive() && !HasViableEnemy())
		return;

	QAngle edge_angle = angle;
	bool edging_head = Settings::AntiAim::HeadEdge::enabled && GetBestHeadAngle(edge_angle);

	static bool bFlip;

	bFlip = !bFlip;

	bool should_clamp = true;

	if (!ValveDSCheck::forceUT && (*csGameRules) && (*csGameRules)->IsValveDS())
	{
		if (Settings::AntiAim::Yaw::type >= AntiAimType_Y::LISP)
			Settings::AntiAim::Yaw::type = AntiAimType_Y::SPIN_SLOW;

		if (Settings::AntiAim::Yaw::typeFake >= AntiAimType_Y::LISP)
			Settings::AntiAim::Yaw::typeFake = AntiAimType_Y::SPIN_SLOW;

		if (Settings::AntiAim::Pitch::type >= AntiAimType_X::STATIC_UP_FAKE)
			Settings::AntiAim::Pitch::type = AntiAimType_X::STATIC_UP;
	}

	if (Settings::AntiAim::Yaw::enabled)
	{
		DoAntiAimY(angle, cmd->command_number, bFlip, should_clamp);
		Math::NormalizeAngles(angle);
		if (!Settings::FakeLag::enabled)
			CreateMove::sendPacket = bFlip;
		if (Settings::AntiAim::HeadEdge::enabled && edging_head && !bFlip)
			angle.y = edge_angle.y;
	}

	if (Settings::AntiAim::Pitch::enabled)
		DoAntiAimX(angle, bFlip, should_clamp);

	if (should_clamp)
	{
		Math::NormalizeAngles(angle);
		Math::ClampAngles(angle);
	}

	cmd->viewangles = angle;

	if (Settings::AntiAim::Yaw::antiResolver)
	{
		static bool antiResolverFlip = false;
		if (cmd->viewangles.y == *localplayer->GetLowerBodyYawTarget())
		{
			if (antiResolverFlip)
				cmd->viewangles.y += 60.f;
			else
				cmd->viewangles.y -= 60.f;

			antiResolverFlip = !antiResolverFlip;

			if (should_clamp)
			{
				Math::NormalizeAngles(cmd->viewangles);
				Math::ClampAngles(cmd->viewangles);
			}
		}
	}

	Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
}
