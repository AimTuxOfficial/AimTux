#pragma once

#include <string>
#include <sys/mman.h>
#include <zconf.h>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <locale>
#include <codecvt>
#include <sstream>
#include "../ImGUI/imgui.h"
#include "../SDK/SDK.h"

namespace Util
{
	std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
	void StdReplaceStr(std::string&, const std::string&, const std::string&);
	const char* PadStringRight(std::string text, size_t value);
	void ProtectAddr(void* address, int prot);
	bool Contains(const std::string &word, const std::string &sentence);
	std::string ToLower(std::string str);
	std::string ToUpper(std::string str);
	std::string WstringToString(std::wstring wstr);
	std::wstring StringToWstring(std::string str);
	ImColor GetRainbowColor(float speed);
	Color GetHealthColor(int hp);
	Color GetHealthColor(C_BasePlayer* player);

	long GetEpochTime();

	const std::map<int,int> * GetModelTypeBoneMap(C_BasePlayer* player);
	ModelType GetModelTypeID(C_BasePlayer* player);
	std::string ModelTypeToString(ModelType model);
	std::string BoneToString(const std::map<int,int> * model, int boneID );
	template <typename T>
	T GetValueByKey(std::vector<std::pair<int, T>> vec, int key)
	{
		for (auto i : vec)
			if (i.first == key)
				return i.second;

		return "";
	}

	template <typename K, typename V>
	K MapReverseSearchOrDefault(std::map<K, V> const* _map, V value, K fallback)
	{
		auto _pair = std::find_if(_map->begin(), _map->end(),
				[value](const std::pair<K, V>& pair) {
					return pair.second == value;
				});

		if (_pair == _map->end())
			return fallback;

		return _pair->first;
	}

	template <typename K, typename V>
	V MapSearchOrDefault(std::map<K, V> const* _map, K key, V fallback)
	{
		auto result = _map->find(key);
		if (result == _map->end())
			return fallback;

		return result->second;
	}

	template<typename T>
	struct IntHash
	{
		size_t operator()(const T& t) const noexcept
		{
			return std::hash<int>()((int) t);
		}
	};
}