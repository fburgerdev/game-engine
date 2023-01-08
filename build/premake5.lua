-- premake5.lua
workspace "parrot"
   configurations { "debug", "optimized", "dist" }

ROOT = ".."
project "parrot"
   kind "ConsoleApp"
   
   language "C++"
   cppdialect "C++20"
   
   targetdir(ROOT .. "/bin")
   objdir(ROOT .. "/bin/obj")

   files { 
      ROOT .. "/src/**.hpp",
      ROOT .. "/src/**.cpp",
      ROOT .. "/vendor/**"
   }
   includedirs {
      ROOT .. "/src",
      ROOT .. "/src/api",
      ROOT .. "/vendor"
   }
   links {
      "glfw",
      "GLEW",
      "GLU",
      "GL"
   }

   debugger "GDB"
   filter "configurations:debug"
      defines { "DEBUG" }
      symbols "On"
   filter "configurations:optimized"
      defines { "OPTIMIZED" }
      optimize "On"
   filter "configurations:dist"
      defines { "DIST" }
      optimize "On"