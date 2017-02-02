#pragma once

#include "../SDK/SDK.h"

// credits: emskye96
class RecvPropHook
{
	private:
		RecvProp* target_property;
		RecvVarProxyFn original_proxy_fn;
	public:
		RecvPropHook(RecvProp* target_property)
		{
			this->target_property = target_property;
			this->original_proxy_fn = target_property->m_ProxyFn;
		}

		~RecvPropHook()
		{
			target_property->m_ProxyFn = this->original_proxy_fn;
		}

		RecvVarProxyFn GetOriginalFunction()
		{
			return this->original_proxy_fn;
		}

		void SetProxyFunction(RecvVarProxyFn user_proxy_fn)
		{
			target_property->m_ProxyFn = user_proxy_fn;
		}
};