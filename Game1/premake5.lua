workspace "GameSolution"
  configurations { "Debug", "Release" }
  platforms		 { "x64" }
  location		 "build"
  characterset   "MBCS"
  
 project "Game1"
   kind "WindowedApp"
 
   files {
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
   }
   includedirs {
		  "Framework/Source"
   }