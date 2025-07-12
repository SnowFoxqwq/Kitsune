#pragma once

//This file should be used by kitsune applications

#include "kitsune/application.h"

#include "kitsune/console.h"

//---entery point------------------------------
#include "kitsune/entery_point.h"
//---------------------------------------------

//---event system------------------------------
#include "kitsune/event/event.h"
#include "kitsune/event/application_event.h"
//---------------------------------------------

//---window related----------------------------
#include "kitsune/window.h"
#include "platform/windows_window.h"
//---------------------------------------------

//---layer related----------------------------
#include "kitsune/core/layer.h"
#include "kitsune/core/layer_stack.h"
#include "kitsune/imgui/imgui_layer.h"
//---------------------------------------------