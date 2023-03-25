-- outputdir = "%{wks.location}/bin/%{cfg.buildcfg}"
-- interdir = "%{wks.location}/bin_int"
-- workspace "ShaderCompile"
-- architecture "x64"
--   configurations
--   {
--     "Release",
--     "Debug"
--   }

project "ShaderCompiler"
  kind "ConsoleApp"
  language "C++"
  cppdialect "C++20"
  targetdir (outputdir)
  objdir    (interdir)
  systemversion "latest"

  files  
  {
    "%{prj.location}/src/**.h",
    "%{prj.location}/src/**.cpp",
    "%{prj.location}/src/**.hpp"
  }
  
  includedirs
  {
    "%{prj.location}/src"
  }

  externalincludedirs
  {    
    "$(VULKAN_SDK)\\include",
	  "$(VULKAN_SDK)\\Source\\SPIRV-Reflect"  
  }
  
  libdirs
  {
    "$(VULKAN_SDK)/Lib"
  }

  links
  {
    "shaderc_shared.lib"
  }
  
  externalwarnings "Off"

  flags
  {
  	"MultiProcessorCompile"
  }

  warnings 'Extra'
  
  filter "configurations:Debug"
    symbols "On"
    defines {"_DEBUG"}
  
  filter "configurations:Release"
    optimize "On"
    defines{"_RELEASE"}
  
  filter "configurations:Publish"
    flags {"ExcludeFromBuild"}