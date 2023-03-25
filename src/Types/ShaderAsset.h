#pragma once

#include "AssetMacros.h"
#include <vector>

namespace SH_COMP
{
	struct ShaderAsset
	{
		std::vector<uint32_t> spirvBinary;

		SH_SHADER_TYPE type;

		std::string name;
	};
}