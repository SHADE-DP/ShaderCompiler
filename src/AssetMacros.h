/******************************************************************************
 * \file    SHAssetMacros.h
 * \author  Loh Xiao Qi
 * \brief   Macros and typedefs for assets
 * 
 * \copyright	Copyright (c) 2022 Digipen Institute of Technology. Reproduction
 *						or disclosure of this file or its contents without the prior
 *						written consent of Digipen Institute of Technology is prohibited
 ******************************************************************************/
#pragma once

#include <cstdint>
#include <filesystem>
#include <vulkan/vulkan.hpp>

// Typedefs
typedef std::filesystem::path AssetPath;

// Asset Meta Version
constexpr std::string_view ASSET_META_VER { "1.0" };

//Directory
#ifdef _PUBLISH
constexpr std::string_view ASSET_ROOT{ "Assets" };
constexpr std::string_view BUILT_IN_ASSET_ROOT {"Built_In"};
#else
constexpr std::string_view ASSET_ROOT {"../../Assets"};
constexpr std::string_view BUILT_IN_ASSET_ROOT{ "../../Built_In" };
#endif

// ASSET EXTENSIONS
constexpr std::string_view SHADER_EXTENSION{ ".shshader" };
constexpr std::string_view SHADER_BUILT_IN_EXTENSION{ ".shshaderb" };

// EXTERNAL EXTENSIONS
constexpr std::string_view GLSL_EXTENSION{ ".glsl" };

// SHADER IDENTIFIERS
constexpr std::string_view VERTEX_SHADER{ "_VS" };
constexpr std::string_view FRAGMENT_SHADER{ "_FS" };
constexpr std::string_view COMPUTER_SHADER{ "_CS" };

enum class SH_SHADER_TYPE : uint8_t
{
  VERTEX       = static_cast<uint8_t>(vk::ShaderStageFlagBits::eVertex),
  FRAGMENT     = static_cast<uint8_t>(vk::ShaderStageFlagBits::eFragment),
  COMPUTE      = static_cast<uint8_t>(vk::ShaderStageFlagBits::eCompute),
  INAVLID_TYPE = std::numeric_limits<uint8_t>::max()
};

constexpr std::pair<std::string_view, SH_SHADER_TYPE> SHADER_IDENTIFIERS[] = {
  std::make_pair(VERTEX_SHADER, SH_SHADER_TYPE::VERTEX),
  std::make_pair(FRAGMENT_SHADER, SH_SHADER_TYPE::FRAGMENT),
  std::make_pair(COMPUTER_SHADER, SH_SHADER_TYPE::COMPUTE)
};

constexpr size_t SHADER_TYPE_MAX_COUNT{ 3 };
