#pragma once

class i_convar;
class con_command;
class con_command_base;
using change_callback_t = void( * )( i_convar* var, const char* old_value, float float_old_value );

enum cvar_flags_t {
	fcvar_none = 0,
	fcvar_unregistered = ( 1 << 0 ),
	fcvar_developmentonly = ( 1 << 1 ),
	fcvar_gamedll = ( 1 << 2 ),
	fcvar_clientdll = ( 1 << 3 ),
	fcvar_hidden = ( 1 << 4 ),
	fcvar_protected = ( 1 << 5 ),
	fcvar_sponly = ( 1 << 6 ),
	fcvar_archive = ( 1 << 7 ),
	fcvar_notify = ( 1 << 8 ),
	fcvar_userinfo = ( 1 << 9 ),
	fcvar_printableonly = ( 1 << 10 ),
	fcvar_unlogged = ( 1 << 11 ),
	fcvar_never_as_string = ( 1 << 12 ),
	fcvar_replicated = ( 1 << 13 ),
	fcvar_cheat = ( 1 << 14 ),
	fcvar_ss = ( 1 << 15 ),
	fcvar_demo = ( 1 << 16 ),
	fcvar_dontrecord = ( 1 << 17 ),
	fcvar_ss_added = ( 1 << 18 ),
	fcvar_release = ( 1 << 19 ),
	fcvar_reload_materials = ( 1 << 20 ),
	fcvar_reload_textures = ( 1 << 21 ),
	fcvar_not_connected = ( 1 << 22 ),
	fcvar_material_system_thread = ( 1 << 23 ),
	fcvar_archive_xbox = ( 1 << 24 ),
	fcvar_accessible_from_threads = ( 1 << 25 ),
	fcvar_server_can_execute = ( 1 << 28 ),
	fcvar_server_cannot_query = ( 1 << 29 ),
	fcvar_clientcmd_can_execute = ( 1 << 30 ),
	fcvar_meme_dll = ( 1 << 31 ),
	fcvar_material_thread_mask = ( fcvar_reload_materials | fcvar_reload_textures | fcvar_material_system_thread )
};

class i_convar {
public:
	char pad_0x0000[ 0x4 ];
	i_convar* next;
	__int32 is_registered;
	char* name;
	char* help_string;
	__int32 flags;
	char pad_0x0018[ 0x4 ];
	i_convar* parent;
	char* default_value;
	char* string;
	__int32 string_length;
	float float_value;
	__int32 numerical_value;
	__int32 has_min;
	float min;
	__int32 has_max;
	float max;

	VIRTUAL_FN( get_float( ), 12, float( __thiscall* )( void* ) );
	VIRTUAL_FN( get_int( ), 13, int( __thiscall* )( void* ) );
	VIRTUAL_FN( set_value( const char* value ), 14, void( __thiscall* )( void*, const char* ), value );
	VIRTUAL_FN( set_value( float value ), 15, void( __thiscall* )( void*, float ), value );
	VIRTUAL_FN( set_value( int value ), 16, void( __thiscall* )( void*, int ), value );
	VIRTUAL_FN( set_value( bool value ), 16, void( __thiscall* )( void*, bool ), value );
	VIRTUAL_FN( set_value_char( const char* value ), 14, void( __thiscall* )( void*, const char* ), value );
	VIRTUAL_FN( set_value_float( float value ), 15, void( __thiscall* )( void*, float ), value );
	VIRTUAL_FN( set_value_int( int value ), 16, void( __thiscall* )( void*, int ), value );
	VIRTUAL_FN( set_value_bool( bool value ), 16, void( __thiscall* )( void*, bool ), value );
};

struct ColorRGBA {
	ColorRGBA( unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha = 255 ) {
		RGBA[ 0 ] = Red;
		RGBA[ 1 ] = Green;
		RGBA[ 2 ] = Blue;
		RGBA[ 3 ] = Alpha;
	}

	unsigned char RGBA[ 4 ];
};


class i_console : public i_app_system {
public:
	virtual int allocate_dll_indentifier( ) = 0;
	virtual void register_con_command( con_command_base* pCommandBase ) = 0;
	virtual void unregister_con_command( con_command_base* pCommandBase ) = 0;
	virtual void unregister_con_commands( int id ) = 0;
	virtual const char* get_command_line_value( const char* pVariableName ) = 0;
	virtual con_command_base* find_command_base( const char* name ) = 0;
	virtual const con_command_base* find_command_base( const char* name ) const = 0;
	virtual i_convar* get_convar( const char* var_name ) = 0;
	virtual const i_convar* get_convar( const char* var_name ) const = 0;
	virtual con_command* find_command( const char* name ) = 0;
	virtual const con_command* find_command( const char* name ) const = 0;
	virtual void install_global_change_callback( change_callback_t callback ) = 0;
	virtual void remove_global_change_callback( change_callback_t callback ) = 0;
	virtual void call_global_change_callbacks( i_convar* var, const char* pOldString, float flOldValue ) = 0;
	virtual void install_console_display_func( void* pDisplayFunc ) = 0;
	virtual void remove_console_display_func( void* pDisplayFunc ) = 0;
	virtual void console_color_printf( const ColorRGBA& clr, const char* pFormat, ... ) const = 0;
	virtual void console_printf( const char* pFormat, ... ) const = 0;
	virtual void donsole_dprintf( const char* pFormat, ... ) const = 0;
	virtual void rever_flagged_convars( int nFlag ) = 0;
};