workspace "GameSolution"
  configurations { "Debug", "Release" }
  platforms		 { "x64" }
  location		 "build"
  characterset   "MBCS"
  startproject "Game"
  
 project "Game"
   kind "WindowedApp"
   debugdir "Game"

   files {
		"Game/Data/Shaders/**.vert",
		"Game/Data/Shaders/**.frag",
		"Game/Source/**.cpp",
		"Game/Source/**.h",
		"BuildProjectFiles.bat",
		"premake5.lua",

   }
      includedirs {
		  "Framework/Source"
		 
   }

   links{
		  "Framework",
		  "opengl32",
   }

 project "Framework"
   kind "StaticLib"

   
   files{
		"Framework/Source/**.cpp",
		"Framework/Source/**.h",
		"Framework/Libraries/imgui/*.cpp",
		"Framework/Libraries/imgui/*.h",
   }
   includedirs {
		  "Framework/Source"
   }