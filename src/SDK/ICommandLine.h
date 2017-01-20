#pragma once

class ICommandLine
{
public:
	virtual void CreateCmdLine(const char* commandline) = 0;
	virtual void CreateCmdLine(int argc, char** argv) = 0;
	virtual const char* GetCmdLine(void) const = 0;

	// Check whether a particular parameter exists
	virtual	const char* CheckParm(const char* psz, const char** ppszValue = 0) const = 0;
	virtual void RemoveParm(const char* parm) = 0;
	virtual void AppendParm(const char* pszParm, const char* pszValues) = 0;

	// Returns the argument after the one specified, or the default if not found
	virtual const char* ParmValue(const char* psz, const char* pDefaultVal = 0) const = 0;
	virtual int ParmValue(const char* psz, int nDefaultVal) const = 0;
	virtual float ParmValue(const char* psz, float flDefaultVal) const = 0;

	// Gets at particular parameters
	virtual int ParmCount() const = 0;
	virtual int FindParm(const char* psz) const = 0;	// Returns 0 if not found.
	virtual const char* GetParm(int nIndex) const = 0;

	// copies the string passwed
	virtual void SetParm(int nIndex, char const* pNewParm) = 0;

	virtual const char* ParmValueByIndex(int nIndex, const char* pDefaultVal = 0) const = 0;
};