workspace "ObjParserC"
	location ".\\build\\"
	startproject "ObjParserC"

	targetdir "%{wks.location}\\bin\\%{cfg.buildcfg}\\"
	objdir "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}\\"
	buildlog "%{wks.location}\\obj\\%{cfg.buildcfg}\\%{prj.name}.log"

	largeaddressaware "on"
	editandcontinue "off"
	staticruntime "on"

	systemversion "latest"
	characterset "mbcs"
	warnings "extra"

	syslibdirs {
		-- Any static libs we link against go here.
	}

	includedirs {
		".\\src\\",
	}

	buildoptions {
		"/Zm200",
		"/utf-8",
		"/std:c++latest",
	}

	flags {
		"no64bitchecks",
		"shadowedvariables",
		"noincrementallink",
		"undefinedidentifiers",
		"multiprocessorcompile",
	}

	platforms {
		"x86",
		"x64",
	}

	configurations {
		"debug",
		"release",
	}

	configuration "debug"
		defines "DEBUG"
		optimize "debug"
		runtime "debug"
		symbols "on"

	configuration "release"
		defines "NDEBUG"
		optimize "full"
		runtime "release"
		symbols "on"

	project "ObjParserC"
		targetname "ObjParserC"

		language "c++"
		kind "consoleapp"

		pchheader "pch.hpp"
		pchsource "src/pch.cpp"

		defines {
			"NOMINMAX",
			"_CRT_SECURE_NO_WARNINGS",
		}

		files {
			".\\src\\**.hpp",
			".\\src\\**.cpp",
		}

		links {

		}

		includedirs {
			".\\src\\",
		}