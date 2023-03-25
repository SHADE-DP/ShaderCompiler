/*************************************************************************//**
 * \file    ShaderCompiler.cpp
 * \author  Loh Xiao Qi
 * \date    25 March 2023
 * \brief    
 *
 * Copyright (C) 2022 DigiPen Institute of Technology. Reproduction or
 * disclosure of this file or its contents without the prior written consent
 * of DigiPen Institute of Technology is prohibited.
 *****************************************************************************/
#include "ShaderCompiler.h"
#include <fstream>
#include <string>
#include <iostream>
#include "shaderc/shaderc.hpp"

namespace SH_COMP
{
	std::string ShaderCompiler::WriteToFile(AssetPath path, ShaderAsset const& data) noexcept
	{
    std::string newPath{ path.string() };
    newPath = newPath.substr(0, newPath.find_last_of('.'));
    newPath += SHADER_BUILT_IN_EXTENSION.data();

    std::ofstream file{ newPath, std::ios::binary | std::ios::out | std::ios::trunc };

    file.write(
      reinterpret_cast<char const*>(& data.type), sizeof(uint8_t)
    );

    size_t const byteCount = sizeof(uint32_t) * data.spirvBinary.size();

    file.write(
      reinterpret_cast<char const*>(&byteCount), sizeof(size_t)
    );

    file.write(
      reinterpret_cast<char const*>(data.spirvBinary.data()), byteCount
    );

    file.close();

    return newPath;
	}

	ShaderAsset const* ShaderCompiler::CompileShaderSourceToMemory(std::string const& data, std::string const& name,
		SH_SHADER_TYPE type) noexcept
	{
    // shaderc compiler
    shaderc::Compiler compiler;
    shaderc::CompileOptions options;

    options.AddMacroDefinition("MY_DEFINE", "1");

    //TODO: Check if we need optimisation levels when compiling into spirv
    // Set optimization levels
    //if (opLevel != shaderc_optimization_level_zero)
    //	options.SetOptimizationLevel(opLevel);

    // Attempt to get the shaderc equivalent shader stage
    shaderc_shader_kind shaderKind;
    switch (type)
    {
    case SH_SHADER_TYPE::VERTEX:
      shaderKind = shaderc_shader_kind::shaderc_glsl_vertex_shader;
      break;
    case SH_SHADER_TYPE::FRAGMENT:
      shaderKind = shaderc_shader_kind::shaderc_glsl_fragment_shader;
      break;
    case SH_SHADER_TYPE::COMPUTE:
      shaderKind = shaderc_shader_kind::shaderc_glsl_compute_shader;
      break;
    default:
      shaderKind = shaderc_shader_kind::shaderc_glsl_vertex_shader;
      break;
    }

    // Compile the shader and get the result
    shaderc::SpvCompilationResult compileResult = compiler.CompileGlslToSpv(data, shaderKind, name.c_str(), options);

    if (compileResult.GetCompilationStatus() != shaderc_compilation_status_success)
    {
      std::cout << "[Shader Compiler] Shaderc failed to compile GLSL shader to binary | " << compileResult.GetErrorMessage();
      return nullptr;
    }

    auto result = new ShaderAsset();
    result->spirvBinary.resize(compileResult.end() - compileResult.begin());

    std::ranges::copy(compileResult.begin(), compileResult.end(), result->spirvBinary.data());

    result->name = name;
    result->type = type;

    return result;
	}

	SH_SHADER_TYPE ShaderCompiler::GetShaderTypeFromFilename(std::string name) noexcept
	{
    for (auto i { 0 }; i < SHADER_TYPE_MAX_COUNT; ++i)
    {
      const auto& [SHADER_SUFFIX, SHADER_TYPE] = SHADER_IDENTIFIERS[i];
      if (name.find(SHADER_SUFFIX.data()) != std::string::npos)
      {
        return SHADER_TYPE;
      }
    }

	  return SH_SHADER_TYPE::INAVLID_TYPE;
	}

	void ShaderCompiler::LoadAndCompile(AssetPath path) noexcept
	{
    auto type = GetShaderTypeFromFilename(path.filename().string());

    if (type == SH_SHADER_TYPE::INAVLID_TYPE)
    {
      std::cout << "[Shader Compiler] Invalid filename for shaders, follow suffix standard\n";
      return;
    }

    path.make_preferred();

    std::ifstream file{ path.string(), std::ios::in };

    if (file.is_open())
    {
      std::stringstream stream;

      stream << file.rdbuf();

      std::string const content = stream.str();

      auto data = CompileShaderSourceToMemory(content, path.filename().string(), type);

      if (data == nullptr)
      {
        return;
      }

    	WriteToFile(path, *data);
      std::cout << "[Shader Compiler] Compiled file: " << path << "\n\n";
      return;
    }
    
	  std::cout << "[Shader Compiler] Failed to compile file: " << path << "\n\n";
	}
}
