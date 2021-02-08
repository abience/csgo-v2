#pragma once

class c_hooks {
	vmt_hook* engine_vgui_hook_ = nullptr;
	WNDPROC original_wnd_proc_ = nullptr;
	vmt_hook* d3d_device_9_hook_ = nullptr;
public:
	auto init( ) -> void;
	auto release( ) const ->void;
	
	[[nodiscard]] auto m_engine_vgui_hook( ) const -> vmt_hook* {
		return this->engine_vgui_hook_;
	}

	[[nodiscard]] auto m_d3d_device_9_hook( ) const -> vmt_hook* {
		return this->d3d_device_9_hook_;
	}
	
	[[nodiscard]] auto m_original_wnd_proc( ) const -> WNDPROC {
		return this->original_wnd_proc_;
	}
}; inline c_hooks hooks;