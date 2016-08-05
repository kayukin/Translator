#include "stdafx.h"
#pragma once
#include "ITranslatorController.h"

namespace Dictionary
{
	class IView
	{
	public:
		virtual void onSwitchState() = 0;
	};
}