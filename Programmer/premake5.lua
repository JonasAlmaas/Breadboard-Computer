include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Programmer"
    architecture "x86_64"
    startproject "Programmer"

    configurations
	{
		"Debug",
		"Release",
		"Dist",
	}

    solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Programmer"
