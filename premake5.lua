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
		".\\deps\\LinearC\\",
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
		dependson "LinearC"

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
			"LinearC",
		}

		includedirs {
			".\\src\\",
		}

	group "Dependencies"

	project "LinearC"
		targetname "LinearC"
		warnings "off"

		language "c++"
		kind "staticlib"

		files {
			".\\deps\\LinearC\\src\\**.hpp",
			".\\deps\\LinearC\\src\\**.cpp",
		}

		includedirs {
			".\\deps\\LinearC\\src\\",
		}