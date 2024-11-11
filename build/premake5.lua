-- premake5.lua
ROOT = "%{wks.location}/.."
WORKSPACE = "game_engine"
STARTUP_PROJECT = "demo"

-- workspace
workspace(WORKSPACE)
   -- startproject
   startproject(STARTUP_PROJECT)
   
   -- architecture
   architecture "x64"
   -- cpp
   language "C++"
   cppdialect "C++20"

   -- debug
   debugger "GDB"

   -- dependancies
   -- :: directories
   libdirs {
      ROOT .. "/vendor/**/lib"
      --[[ INSERT ADDITIONAL LINKS HERE ]]
   }
   -- :: libraries
   links { --[[ INSERT ADDITIONAL LINKS HERE ]] }

   -- config
   configurations { "debug", "release", "dist" }
   -- :: debug
   filter "configurations:debug"
      -- symbols / defines
      symbols "On"
      defines { "CONFIG_DEBUG" }
      -- options
      linkoptions{ }
   -- :: release
   filter "configurations:release"
      -- optimize / defines
      optimize "On"
      defines { "CONFIG_RELEASE" }
      -- options
      linkoptions{ "-Ofast" }
   -- :: dist
   filter "configurations:dist"
      -- optimize / defines
      optimize "On"
      defines { "CONFIG_DIST" }
      -- options
      linkoptions { "-Ofast" }
   
   -- system
   -- :: windows
   filter "system:windows"
      defines { "SYSTEM_WINDOWS" }
   -- :: linux
   filter "system:linux"
      defines { "SYSTEM_LINUX" }

   -- toolset
   warnings "Everything"

-- project lib
project(WORKSPACE)
   -- static lib
   kind "StaticLib"

   -- -- precompiled headers
   -- pchheader "common.hpp"
   -- pchsource "common.cpp"
   
   -- include
   includedirs {
      ROOT .. "/",
      ROOT .. "/src",
      ROOT .. "/src/api",
      ROOT .. "/vendor",
      ROOT .. "/vendor/**/include"
   }
   -- files
   files {
      ROOT .. "/src/**",
      ROOT .. "/vendor/**",
   }

   -- binaries
   targetdir(ROOT .. "/bin/%{cfg.buildcfg}")
   objdir(ROOT .. "/bin/obj")

-- project demo
project "demo"
   -- console
   kind "ConsoleApp"

   -- include
   includedirs {
      ROOT .. "/",
      ROOT .. "/test/demo/**",
      ROOT .. "/src",
      ROOT .. "/src/api",
      ROOT .. "/vendor",
      ROOT .. "/vendor/**/include"
      --[[ INSERT ADDITIONAL DIRECTORIES HERE ]]
   }
   -- files
   files {
      ROOT .. "/test/demo/**",
      --[[ INSERT ADDITIONAL FILES HERE ]]
   }

   -- dependancies
   -- :: directories
   libdirs {
      ROOT .. "/bin/%{cfg.system}_%{cfg.buildcfg}",
      ROOT .. "/vendor/**/lib"
      --[[ INSERT ADDITIONAL DIRECTORIES HERE ]]
   }
   -- :: libraries
   links { WORKSPACE, "glfw3.lib", "opengl32.lib", --[[ INSERT ADDITIONAL LINKS HERE ]] }

   -- binaries
   targetdir(ROOT .. "/bin/%{cfg.buildcfg}")
   objdir(ROOT .. "/bin/obj")