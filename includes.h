#ifndef INCLUDES_H
#define INCLUDES_H

/* std library includes */
#include <iostream>
#include <Windows.h>
#include <vector>
#include <cmath>
#include <process.h>
#include <sstream>
#include <tlhelp32.h>
#include <array>
#include <thread>
#include <chrono>
#include <numbers>
#include <mutex>
#include <emmintrin.h>
#include <map>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <string>
#include <numeric>
#include <d3d11.h>
#include <dwmapi.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dwmapi.lib")

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"

/* utility headers */
#include "memory.h"
#include "process.h"
#include "communication.h"
#include "xorstring.h"
#include "address.h"
#include "util.h"
#include "math.h"

/* project specific includes */
#include "reversals.h"
#include "client.h"
#include "rendering.h"
#include "visuals.h"
#include "aimbot.h"

/* classes */
#include "base class.h"
#include "world.h"
#include "list.h"
#include "dlc manager.h"
#include "entities.h"
#include "visual state.h"
#include "entity type.h"
#include "arma string.h"
#include "network manager.h"
#include "landscape.h"
#include "realplayer.h"
#include "camera angles.h"
#include "dx11engine.h"
#include "camera.h"
#include "entitylist.h"
#include "movestype.h"
#include "moveinfo.h"
#include "actionmap.h"
#include "weapon.h"
#include "weapon_type.h"
#include "weapon_mode.h"
#include "muzzle_state.h"
#include "muzzle_type.h"
#include "magazine.h"
#include "magazine_type.h"
#include "ammo_type.h"

/* menu includes */
#include "menu.h"
#include "tab.h"
#include "group.h"
#include "element.h"
#include "render.h"
#include "input.h"
#include "checkbox.h"
#include "slider.h"
#include "dropdown.h"
#include "multidropdown.h"
#include "colourpicker.h"
#include "button.h"
#include "keybind.h"
#include "textbox.h"
#include "settings.h"
#include "util.h"
#include "text.h"
#include "selectionbox.h"
#include "configbox.h"
#include "callbacks.h"

#endif