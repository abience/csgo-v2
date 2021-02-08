#pragma once

class c_console {
public:
	static auto initialize( ) -> void {
		AllocConsole( );
		freopen_s( reinterpret_cast< FILE** >( stdin ), "CONIN$", "r", stdin );
		freopen_s( reinterpret_cast< FILE** >( stdout ), "CONOUT$", "w", stdout );
	};

	static auto release( ) -> void {
		fclose( reinterpret_cast< FILE* >( stdin ) );
		fclose( reinterpret_cast< FILE* >( stdout ) );
		FreeConsole( );
	};
};