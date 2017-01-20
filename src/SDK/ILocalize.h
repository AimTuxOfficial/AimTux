#pragma once

typedef uint32_t LocalizeStringIndex_t;

class ILocalizeTextQuery
{
public:
	virtual int ComputeTextWidth(const wchar_t* pString) = 0;
};

class ILocalizationChangeCallback
{
public:
	virtual void OnLocalizationChanged() = 0;
};

class ILocalize : public IAppSystem
{
public:
	// adds the contents of a file to the localization table
	virtual bool AddFile(const char* fileName, const char* pPathID = NULL, bool bIncludeFallbackSearchPaths = false) = 0;

	// Remove all strings from the table
	virtual void RemoveAll() = 0;

	// Finds the localized text for tokenName. Returns NULL if none is found.
	virtual wchar_t* Find(const char* tokenName) = 0;

	// Like Find(), but as a failsafe, returns an error message instead of NULL if the string isn't found.
	virtual const wchar_t* FindSafe(const char* tokenName) = 0;

	// converts an english string to unicode
	// returns the number of wchar_t in resulting string, including null terminator
	virtual int ConvertANSIToUnicode(const char* ansi, wchar_t* unicode, int unicodeBufferSizeInBytes) = 0;

	// converts an unicode string to an english string
	// unrepresentable characters are converted to system default
	// returns the number of characters in resulting string, including null terminator
	virtual int ConvertUnicodeToANSI(const wchar_t* unicode, char* ansi, int ansiBufferSize) = 0;

	// finds the index of a token by token name, INVALID_STRING_INDEX if not found
	virtual LocalizeStringIndex_t FindIndex(const char* tokenName) = 0;

	// builds a localized formatted string
	// uses the format strings first: %s1, %s2, ...  unicode strings (wchar_t* )
	virtual void ConstructString(wchar_t* unicodeOuput, int unicodeBufferSizeInBytes, const wchar_t* formatString, int numFormatParameters, ...) = 0;

	// gets the values by the string index
	virtual const char* GetNameByIndex(LocalizeStringIndex_t index) = 0;
	virtual wchar_t* GetValueByIndex(LocalizeStringIndex_t index) = 0;

	///////////////////////////////////////////////////////////////////
	// the following functions should only be used by localization editors

	// iteration functions
	virtual LocalizeStringIndex_t GetFirstStringIndex() = 0;
	// returns the next index, or INVALID_STRING_INDEX if no more strings available
	virtual LocalizeStringIndex_t GetNextStringIndex(LocalizeStringIndex_t index) = 0;

	// adds a single name/unicode string pair to the table
	virtual void AddString(const char* tokenName, wchar_t* unicodeString, const char* fileName) = 0;

	// changes the value of a string
	virtual void SetValueByIndex(LocalizeStringIndex_t index, wchar_t* newValue) = 0;

	// saves the entire contents of the token tree to the file
	virtual bool SaveToFile(const char* fileName) = 0;

	// iterates the filenames
	virtual int GetLocalizationFileCount() = 0;
	virtual const char* GetLocalizationFileName(int index) = 0;

	// returns the name of the file the specified localized string is stored in
	virtual const char* GetFileNameByIndex(LocalizeStringIndex_t index) = 0;

	// for development only, reloads localization files
	virtual void ReloadLocalizationFiles() = 0;

	// need to replace the existing ConstructString with this
	virtual void ConstructString(wchar_t* unicodeOutput, int unicodeBufferSizeInBytes, const char* tokenName, KeyValues* localizationVariables) = 0;
	virtual void ConstructString(wchar_t* unicodeOutput, int unicodeBufferSizeInBytes, LocalizeStringIndex_t unlocalizedTextSymbol, KeyValues* localizationVariables) = 0;

	// Used to install a callback to query which localized strings are the longest
	virtual void SetTextQuery(ILocalizeTextQuery* pQuery) = 0;

	// Is called when any localization strings change
	virtual void InstallChangeCallback(ILocalizationChangeCallback* pCallback) = 0;
	virtual void RemoveChangeCallback(ILocalizationChangeCallback* pCallback) = 0;
};