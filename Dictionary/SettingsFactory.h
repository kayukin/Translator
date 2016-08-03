#include "stdafx.h"
#pragma once
#include "ISettings.h"
#include <memory>
#include "RegistrySettings.h"

namespace Dictionary
{
	class SettingsFactory
	{
	public:
		static std::shared_ptr<ISettings> create()
		{
			return std::shared_ptr<ISettings>(new RegistrySettings());
		}
	};
}