workspace "GameSolution"
  configurations { "Debug", "Release" }
  platforms		 { "x64" }
  location		 "build"
  
 project "Game1"
   kind "WindowedApp"
 
   files {
		"Source/**.cpp",
		"Source/**.h",
		"BuildProjectFiles.bat",
		"premake5.lua",
   }