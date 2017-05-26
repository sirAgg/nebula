
SET(NROOT ${CMAKE_CURRENT_LIST_DIR})

option(N_USE_PRECOMPILED_HEADERS "Use precompiled headers" OFF)

if(FIPS_WINDOWS)
	option(N_STATIC_BUILD "Use static runtime in windows builds" ON)
	if(N_STATIC_BUILD)
		add_definitions(-D__N_STATIC_BUILD)
	endif()
endif()

if(FIPS_WINDOWS)
	option(N_MATH_XNA "Use xna-math (requires ancient platform sdk)" OFF)
endif()
if(N_MATH_XNA)
	add_definitions(-D__USE_XNA)
else()	
	add_definitions(-D__USE_VECMATH)
	OPTION(N_USE_AVX "Use AVX instructionset" OFF)	
endif()

set(N_QT4 OFF)
set(N_QT5 OFF)
set(DEFQT "N_QT4")
set(N_QT ${DEFQT} CACHE STRING "Qt Version")
set_property(CACHE N_QT PROPERTY STRINGS "N_QT4" "N_QT5")
set(${N_QT} ON)

set(DEF_RENDERER "N_RENDERER_VULKAN")
set(N_RENDERER ${DEF_RENDERER} CACHE STRING "Nebula 3D Render Device")
set_property(CACHE N_RENDERER PROPERTY STRINGS "N_RENDERER_VULKAN" "N_RENDERER_D3D11" "N_RENDERER_OGL4")
set(${N_RENDERER} ON)

if(N_QT5)
	add_definitions(-D__USE_QT5)
endif()

if(N_QT4)
	add_definitions(-D__USE_QT4)
endif()

if(N_RENDERER_VULKAN)
	add_definitions(-DNEBULA_DEFAULT_FRAMESHADER_NAME="vkdebug")
	add_definitions(-D__VULKAN__)
endif()

option(N_BUILD_NVTT "use NVTT" ON)
