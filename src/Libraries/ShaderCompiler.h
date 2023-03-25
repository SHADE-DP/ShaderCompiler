/*************************************************************************//**
 * \file    ShaderCompiler.h
 * \author  Loh Xiao Qi
 * \date    22 March 2023
 * \brief    
 *
 * Copyright (C) 2022 DigiPen Institute of Technology. Reproduction or
 * disclosure of this file or its contents without the prior written consent
 * of DigiPen Institute of Technology is prohibited.
 *****************************************************************************/
#pragma once

#include "AssetMacros.h"
#include "Types/ShaderAsset.h"

namespace SH_COMP
{
	class ShaderCompiler
	{
		static std::string WriteToFile(AssetPath path, ShaderAsset const& data) noexcept;
		static ShaderAsset const* CompileShaderSourceToMemory(std::string const& data, std::string const& name, SH_SHADER_TYPE type) noexcept;

		static SH_SHADER_TYPE GetShaderTypeFromFilename(std::string name) noexcept;

	public:
		static void LoadAndCompile(AssetPath path) noexcept;
	};
}
