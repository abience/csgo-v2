#pragma once

#include <Windows.h>
#include <stdexcept>
#include <thread>
#include <vector>
#include <ostream>
#include <tuple>
#include <windowsx.h>
#include <d3d9.h>

#include "../core/core.h"
#include "console/console.h"
#include "memory/memory.h"
#include "vmt/vmt.h"

#include "valve/interface_registration/interface_registration.h"

#include "utilities/utilities.h"

#include "vector/vec3_t/vec3_t.h"
#include "vector/vec2_t/vec2_t.h"
#include "vector/matrix/matrix.h"

#include "valve/color/color.h"
#include "valve/vertex/vertex.h"
#include "valve/i_surface/i_surface.h"
#include "valve/i_engine_vgui/i_engine_vgui.h"
#include "valve/player_info_t/player_info_t.h"
#include "valve/iv_engine_client/iv_engine_client.h"
#include "valve/iv_debug_overlay/iv_debug_overlay.h"
#include "valve/recv/recv.h"
#include "valve/i_base_client/i_base_client.h"
#include "valve/c_global_vars_base/c_global_vars_base.h"
#include "valve/i_app_system/i_app_system.h"
#include "valve/i_console/i_console.h"

#include "../interfaces/interfaces.h"
#include "../offsets/offsets.h"

#include "../render/render.h"

#include "../hooks/hooks.h"

#include "../input_helper/input_helper.h"

#include "../menu/controls/controls.h"
#include "../menu/menu.h"