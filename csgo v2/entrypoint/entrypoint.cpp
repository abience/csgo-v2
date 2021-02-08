#include "../sdk/sdk.h"

/*
 * don't know how you got this source, but congratulations i guess
 * +5 internet points to you my dude
 * 
 * this is my masterpiece, the best i have to offer with my (current) knowledge
 * if i am leonardo da vinci this is my mona lisa
 *
 * 
 * s/o to lilypad, azile, car, finally, admin abuser $$$, spicy, tommy, icey,
 * $$$palaceplayer$$$, bray, crunchy, dylan, mortal, rise, sorrowvibez, meth/John., and authentic
 * each one of these people were testers for this cheat and helped the development process
 *
 *
 * started: 1/25/2021
 *
 *
 * - luna / psilent / whoever you wanna call me by
 * appreciate all of you
 */

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