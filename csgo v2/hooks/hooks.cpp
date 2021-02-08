#include "../sdk/sdk.h"

void __fastcall paint( std::uintptr_t ecx, std::uintptr_t edx, int mode ) {
	static auto original_fn = hooks.m_engine_vgui_hook( )->get_original< decltype( &paint ) >( 14 );
	original_fn( ecx, edx, mode );

	static auto start_drawing = reinterpret_cast< void( __thiscall* )( void* ) >( offsets.signatures.vguimatsurface.start_drawing );
	static auto finish_drawing = reinterpret_cast< void( __thiscall* )( void* ) >( offsets.signatures.vguimatsurface.finish_drawing );

	start_drawing( interfaces.m_surface( ) ); {
		menu.draw( );
	} finish_drawing( interfaces.m_surface( ) );
}

long __stdcall end_scene( const LPDIRECT3DDEVICE9 device ) {
	static auto original_fn = hooks.m_d3d_device_9_hook( )->get_original< decltype( &end_scene ) >( 42 );
	return original_fn( device );
}

LRESULT __stdcall wnd_proc( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
	input_helper.poll( hwnd, msg, wparam, lparam );
	return CallWindowProcA( hooks.m_original_wnd_proc( ), hwnd, msg, wparam, lparam );
}

auto c_hooks::init( ) -> void {
	this->engine_vgui_hook_ = new vmt_hook( interfaces.m_engine_vgui( ) );
	this->engine_vgui_hook_->hook( paint, 14 );
	this->engine_vgui_hook_->apply( );

	this->original_wnd_proc_ = reinterpret_cast< WNDPROC >( SetWindowLongPtr( FindWindowA( nullptr, "Counter-Strike: Global Offensive" ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( wnd_proc ) ) );

	this->d3d_device_9_hook_ = new vmt_hook( interfaces.m_d3d_device_9( ) );
	this->d3d_device_9_hook_->hook( end_scene, 42 );
	this->d3d_device_9_hook_->apply( );
}

auto c_hooks::release( ) const -> void {
	this->engine_vgui_hook_->release( );
	SetWindowLongPtr( FindWindowA( nullptr, "Counter-Strike: Global Offensive" ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( this->original_wnd_proc_ ) );
	this->d3d_device_9_hook_->release( );
}