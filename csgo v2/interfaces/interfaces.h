#pragma once

class c_interfaces {
	i_surface* surface_ = nullptr;
	i_engine_vgui* engine_vgui_ = nullptr;
	iv_engine_client* engine_client_ = nullptr;
	iv_debug_overlay* debug_overlay_ = nullptr;
	i_base_client* base_client_ = nullptr;
	c_global_vars_base* global_vars_base_ = nullptr;
	i_console* console_ = nullptr;
	IDirect3DDevice9* d3d_device_9_ = nullptr;
public:
	void init( ) {
		this->surface_ = c_utilities::capture_interface<i_surface>( "vguimatsurface.dll", "VGUI_Surface" );;
		this->engine_vgui_ = c_utilities::capture_interface<i_engine_vgui>( "engine.dll", "VEngineVGui" );
		this->engine_client_ = c_utilities::capture_interface<iv_engine_client>( "engine.dll", "VEngineClient" );
		this->debug_overlay_ = c_utilities::capture_interface<iv_debug_overlay>( "engine.dll", "VDebugOverlay" );
		this->base_client_ = c_utilities::capture_interface<i_base_client>( "client.dll", "VClient" );
		this->global_vars_base_ = **reinterpret_cast< c_global_vars_base*** >( ( *reinterpret_cast< std::uintptr_t** >( this->base_client_ ) )[ 0 ] + 0x1F );
		this->console_ = c_utilities::capture_interface<i_console>( "vstdlib.dll", "VEngineCvar" );
		this->d3d_device_9_ = **reinterpret_cast< IDirect3DDevice9*** >( c_memory::get_signature( "shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 0x1 );
	}

	[[nodiscard]] auto m_surface( ) const -> i_surface* {
		return this->surface_;
	}

	[[nodiscard]] auto m_engine_vgui( ) const -> i_engine_vgui* {
		return this->engine_vgui_;
	}

	[[nodiscard]] auto m_engine_client( ) const -> iv_engine_client* {
		return this->engine_client_;
	}

	[[nodiscard]] auto m_debug_overlay( ) const -> iv_debug_overlay* {
		return this->debug_overlay_;
	}

	[[nodiscard]] auto m_base_client( ) const -> i_base_client* {
		return this->base_client_;
	}

	[[nodiscard]] auto m_global_vars_base( ) const -> c_global_vars_base* {
		return this->global_vars_base_;
	}

	[[nodiscard]] auto m_console( ) const -> i_console* {
		return this->console_;
	}

	[[nodiscard]] auto m_d3d_device_9( ) const -> IDirect3DDevice9* {
		return this->d3d_device_9_;
	}
}; inline c_interfaces interfaces;