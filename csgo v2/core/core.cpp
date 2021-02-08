#include "../sdk/sdk.h"

auto c_core::initialize( ) const -> void {
	while ( !c_core::ready( ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 150 ) );
	
	if ( this->version == version_t::version_debug )
		c_console::initialize( );
	
	interfaces.init( );
	offsets.init( );
	render.init( );
	hooks.init( );
}

auto c_core::unload( void* module ) const -> void {
	if ( this->version == version_t::version_debug )
		c_console::release( );

	hooks.release( );

	FreeLibraryAndExitThread( static_cast< HMODULE >( module ), 0 );
}

auto c_core::determine_version( ) -> void {
#ifdef _DEBUG
	this->version = version_t::version_debug;
#elif _BETA
	this->version = version_t::version_beta;
#else
	this->version = version_t::version_release;
#endif
}

auto c_core::ready( ) -> bool {
	return GetModuleHandleA( "client.dll" ) && GetModuleHandleA( "serverbrowser.dll" );
}