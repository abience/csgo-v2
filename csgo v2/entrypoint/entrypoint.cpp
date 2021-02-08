#include "../sdk/sdk.h"

auto __stdcall thread( void* module ) -> unsigned long {
	core.initialize( );

	if ( core.version != version_t::version_debug )
		return 0;

	while ( !( GetAsyncKeyState( VK_END ) & 1 ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

	core.unload( module );
	
	return 0;
}

BOOL WINAPI DllMain( _In_ HINSTANCE instance, _In_ DWORD reason, _In_ LPVOID /*reserved*/ ) {

	if ( reason == DLL_PROCESS_ATTACH ) {
		if ( auto* const thread_handle = CreateThread( nullptr, 0, thread, instance, 0, nullptr ) )
			CloseHandle( thread_handle );
	}

	return TRUE;
}
