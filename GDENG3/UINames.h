#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"


class UINames
{
public:
	const String PROFILER_SCREEN = "PROFILER_SCREEN";
	const String MENU_SCREEN = "MENU_SCREEN";
	const String INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const String HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String COLORPICKER_SCREEN = "COLORPICKER_SCREEN";
	const String PLAYBACK_SCREEN = "PLAYBACK_SCREEN";
	const String ACTIONS_SCREEN = "ACTIONS_SCREEN";
	const String DEBUG_CONSOLE_SCREEN = "DEBUG_CONSOLE_SCREEN";
};

