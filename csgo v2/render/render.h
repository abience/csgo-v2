#pragma once

struct area_t {
	int x, y, w, h;
};

class c_render {
	struct {
		DWORD tahoma_13;
		DWORD tahoma_13_bold;
	} fonts_;
public:
	auto init( ) -> void {
		auto create_font = [ ]( unsigned long& font, const char* font_name, const int size, const int weight, const int flags ) -> void {
			font = interfaces.m_surface( )->create_font( );
			interfaces.m_surface( )->set_font_glyph_set( font, font_name, size, weight, 0, 0, flags, 0, 0 );
		};
		
		create_font( this->fonts_.tahoma_13, "Tahoma", 13, 300, FONTFLAG_DROPSHADOW );
		create_font( this->fonts_.tahoma_13_bold, "Tahoma", 13, 700, FONTFLAG_DROPSHADOW );
	}

	// render funcs.
	static auto filled_rectangle( const area_t area, const color col ) -> void {
		interfaces.m_surface( )->draw_set_color( col.m_r( ), col.m_g( ), col.m_b( ), col.m_a( ) );
		interfaces.m_surface( )->draw_filled_rect( area.x, area.y, area.x + area.w, area.y + area.h );
	}

	static auto outlined_rectangle( const area_t area, const color col ) -> void {
		interfaces.m_surface( )->draw_set_color( col.m_r( ), col.m_g( ), col.m_b( ), col.m_a( ) );
		interfaces.m_surface( )->draw_outlined_rect( area.x, area.y, area.x + area.w, area.y + area.h );
	}

	static auto line( const area_t area, const color col ) -> void {
		interfaces.m_surface( )->draw_set_color( col.m_r( ), col.m_g( ), col.m_b( ), col.m_a( ) );
		interfaces.m_surface( )->draw_line( area.x, area.y, area.w, area.h );
	}

	static auto text( const unsigned long font, const std::string text, const int x, const int y, const bool centered, const color col ) -> void {
		auto _x = x, _y = y;

		wchar_t buf[ 2056 ];

		if ( MultiByteToWideChar( CP_UTF8, 0, text.c_str( ), -1, buf, 128 ) > 0 ) {
			int width, height;
			interfaces.m_surface( )->get_text_size( font, buf, width, height );

			if ( centered )
				_x -= width / 2;

			interfaces.m_surface( )->draw_set_text_font( font );
			interfaces.m_surface( )->draw_set_text_color( col.m_r( ), col.m_g( ), col.m_b( ), col.m_a( ) );
			interfaces.m_surface( )->draw_set_text_pos( _x, _y );
			interfaces.m_surface( )->draw_print_text( buf, wcslen( buf ) );
		}
	}

	static auto get_text_size( const unsigned long font, const std::string& text ) -> vec2_t {
		RECT output{ };

		wchar_t buf[ 2056 ];

		if ( MultiByteToWideChar( CP_UTF8, 0, text.c_str( ), -1, buf, 128 ) > 0 ) {
			int width, height;
			interfaces.m_surface( )->get_text_size( font, buf, width, height );
			output.right = width;
			output.bottom = height;
		}

		return vec2_t( static_cast< float >( output.right ), static_cast< float >( output.bottom ) );
	}

	
	// fonts.
	[[nodiscard]] auto m_tahoma_13( ) const -> unsigned long {
		return this->fonts_.tahoma_13;
	}

	[[nodiscard]] auto m_tahoma_13_bold( ) const -> unsigned long {
		return this->fonts_.tahoma_13_bold;
	}
}; inline c_render render;