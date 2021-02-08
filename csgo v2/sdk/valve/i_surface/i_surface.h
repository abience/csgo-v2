#pragma once

enum font_flags_t {
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

class i_surface {
public:
	VIRTUAL_FN( draw_set_color( const int r, const int g, const int b, const int a ), 15, void( __thiscall* )( void*, int, int, int, int ), r, g, b, a );
	VIRTUAL_FN( draw_filled_rect( const int x0, const int y0, const int x1, const int y1 ), 16, void( __thiscall* )( void*, int, int, int, int ), x0, y0, x1, y1 );
	VIRTUAL_FN( draw_outlined_rect( const int x0, const int y0, const int x1, const int y1 ), 18, void( __thiscall* )( void*, int, int, int, int ), x0, y0, x1, y1 );
	VIRTUAL_FN( draw_line( const int x0, const int y0, const int x1, const int y1 ), 19, void( __thiscall* )( void*, int, int, int, int ), x0, y0, x1, y1 );
	VIRTUAL_FN( draw_set_text_font( const DWORD font ), 23, void( __thiscall* )( void*, DWORD ), font );
	VIRTUAL_FN( draw_set_text_color( const int r, const int g, const int b, const int a ), 25, void( __thiscall* )( void*, int, int, int, int ), r, g, b, a );
	VIRTUAL_FN( draw_set_text_pos( const int x, const int y ), 26, void( __thiscall* )( void*, int, int ), x, y );
	VIRTUAL_FN( draw_print_text( const wchar_t* text, const int text_length ), 28, void( __thiscall* )( void*, const wchar_t*, int, int ), text, text_length, 0 );
	VIRTUAL_FN( draw_set_texture_rgb( const int id, color* rgba, const int w, const int h ), 37, void( __thiscall* )( void*, int, color*, int, int ), id, rgba, w, h );
	VIRTUAL_FN( draw_set_texture_rgb( const int id, const unsigned char* rgba, const int w, const int h ), 37, void( __thiscall* )( void*, int, const unsigned char*, int, int ), id, rgba, w, h );
	VIRTUAL_FN( draw_set_texture( const int id ), 38, void( __thiscall* )( void*, int ), id );
	VIRTUAL_FN( draw_textured_rectangle( const int x0, const int y0, const int x1, const int y1 ), 41, void( __thiscall* )( void*, int, int, int, int ), x0, y0, x1, y1 );
	VIRTUAL_FN( is_texture_id_valid( const int id ), 42, bool( __thiscall* )( void*, int ), id );
	VIRTUAL_FN( create_new_texture_id( const bool procedural = false ), 43, int( __thiscall* )( void*, bool ), procedural );
	VIRTUAL_FN( get_screen_size( int& wide, int& tall ), 44, void( __thiscall* )( void*, int&, int& ), wide, tall );
	VIRTUAL_FN( unlock_cursor( void ), 66, void( __thiscall* )( void* ) );
	VIRTUAL_FN( lock_cursor( void ), 67, void( __thiscall* )( void* ) );
	VIRTUAL_FN( create_font( void ), 71, DWORD( __thiscall* )( void* ) );
	VIRTUAL_FN( set_font_glyph_set( const DWORD font, const char* font_name, const int tall, const int weight, const int blur, const  int scan_lines, const int flags, const int min_range, const int max_range ), 72, void( __thiscall* )( void*, DWORD, const char*, int, int, int, int, int, int, int ), font, font_name, tall, weight, blur, scan_lines, flags, min_range, max_range );
	VIRTUAL_FN( add_custom_font_file( const char* font_file_name ), 73, bool( __thiscall* )( void*, const char* ), font_file_name );
	VIRTUAL_FN( get_font_tall( const DWORD font ), 74, int( __thiscall* )( void*, DWORD ), font );
	VIRTUAL_FN( get_font_tall( const DWORD font, const  int ch ), 78, int( __thiscall* )( void*, DWORD, int ), font, ch );
	VIRTUAL_FN( get_text_size( const DWORD font, const wchar_t* text, int& wide, int& tall ), 79, void( __thiscall* )( void*, unsigned long, const wchar_t*, int&, int& ), font, text, wide, tall );
	VIRTUAL_FN( play_sound( const char* sound ), 82, int( __thiscall* )( void*, const char* ), sound );
	VIRTUAL_FN( draw_outlined_circle( const int x, const int y, const int radius, const int segments ), 103, void( __thiscall* )( void*, int, int, int, int ), x, y, radius, segments );
	VIRTUAL_FN( draw_textured_poly_line( const int count, vertex_t* verts ), 104, void( __thiscall* )( void*, vertex_t*, int ), verts, count );
	VIRTUAL_FN( draw_textured_polygon( const int count, vertex_t* verts, const bool unk = false ), 106, void( __thiscall* )( void*, int, vertex_t*, bool ), count, verts, unk );
	VIRTUAL_FN( on_screen_size_change( const int old_width, const int old_height ), 116, int( __thiscall* )( void*, int, int ), old_width, old_height );
	VIRTUAL_FN( draw_filled_rect_fade( const int x0, const int y0, const int x1, const int y1, const unsigned int alpha0, const unsigned int alpha1, const bool horizontal ), 123, void( __thiscall* )( void*, int, int, int, int, unsigned int, unsigned int, bool ), x0, y0, x1, y1, alpha0, alpha1, horizontal );
	VIRTUAL_FN( add_bitmap_font_file( const char* font_file_name ), 127, bool( __thiscall* )( void*, const char* ), font_file_name );
	VIRTUAL_FN( get_clip_rect( int& x0, int& y0, int& x1, int& y1 ), 146, void( __thiscall* )( void*, int, int, int, int ), x0, y0, x1, y1 );
	VIRTUAL_FN( set_clip_rect( int& x0, int& y0, int& x1, int& y1 ), 147, void( __thiscall* )( void*, int, int, int, int ), x0, y0, x1, y1 );
	void set_clipping_enabled( const bool enabled ) { *reinterpret_cast< bool* >( reinterpret_cast< std::uintptr_t >( this ) + 0x280 ) = enabled; };
};