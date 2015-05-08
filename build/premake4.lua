solution "MySolution"
	configurations {"Debug", "Release"}
	
	project "Pong"
		kind "ConsoleApp"
		language "C++"
		links { "SDL2", "SDL2_ttf" }
		includedirs{ "../include" }
		files {
			"../include/**.h",
			"../src/**.cpp"
		}

