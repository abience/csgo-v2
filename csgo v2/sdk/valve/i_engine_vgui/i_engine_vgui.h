#pragma once

//https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/ienginevgui.h

enum vgui_panel_t {
	panel_root = 0,
	panel_gameuidll,
	panel_clientdll,
	panel_tools,
	panel_ingamescreens,
	panel_gamedll,
	panel_clientdll_tools
};

enum paint_mode_t {
	paint_uipanels = ( 1 << 0 ),
	paint_ingamepanels = ( 1 << 1 ),
	paint_cursor = ( 1 << 2 ), // software cursor, if appropriate
};

class i_engine_vgui {
	
};