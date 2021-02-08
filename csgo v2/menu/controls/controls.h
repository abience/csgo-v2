#pragma once

// forward declarations.

enum control_type_t {
	control_window = 0,
	control_groupbox
};

class c_base_control {
public:
	virtual auto paint( ) -> void = 0;
	virtual auto input( ) -> void = 0;

	auto set_disabled( const bool disabled ) -> void {
		this->disabled = disabled;
	}
	
	const char* name;
	area_t area;
	bool disabled;
	control_type_t type;
};

class c_groupbox : public c_base_control {
public:
	explicit c_groupbox( const char* name = "", const area_t area = { }, int tab = 0 ) {
		this->name = name;
		this->area = area;
		this->type = control_groupbox;
	}

	auto paint( ) -> void override {
		// main form.
		c_render::filled_rectangle( area, { 25, 25, 25 } );

		// outline.
		c_render::outlined_rectangle( area, { 35, 35, 35 } );
	}

	auto input( ) -> void override {

	}
};

class c_window : public c_base_control {
	// dragging vars.
	bool hovering_{ false };
	vec2_t drag_offset_{ 0, 0 };
	bool clicked_{ false };
	bool should_drag_{ false };

	// tab vars.
	std::vector<const char*> tabs_{ };
	int selected_tab_{ 0 };

	// groupbox vars.
	std::vector<c_groupbox> groupboxes_{ };
public:
	explicit c_window( const char* name = "", const area_t area = { } ) {
		this->name = name;
		this->area = area;
		this->type = control_window;
	}
	
	auto paint( ) -> void override {
		// main form.
		c_render::filled_rectangle( area, { 10, 10, 10 } );

		// title bar.
		c_render::filled_rectangle( { area.x, area.y, area.w, 16 }, { 30, 30, 30 } );
		c_render::text( render.m_tahoma_13( ), this->name, area.x + ( area.w / 2 ), area.y + 1, true, { 255, 255, 255 } );

		const auto version_text_size = c_render::get_text_size( render.m_tahoma_13( ), "v2" );
		
		c_render::text( render.m_tahoma_13( ), "v2", area.x + ( area.w - version_text_size.x - 2 ), area.y + 1, false, { 200, 200, 200 } );

		// tab bar.
		c_render::filled_rectangle( { area.x + 8, area.y + 23, area.w - 16, 20 }, { 23, 23, 23 } );

		// tabs.
		const auto tab_size = ( area.w - 16 ) / this->tabs_.size( );
		for ( auto i{ 0 }; i < this->tabs_.size( ); ++i ) {
			const auto* tab = this->tabs_[ i ];

			const area_t tab_area = { area.x + 8 + ( i * tab_size ), area.y + 23, tab_size, 20 };
			
			if ( i == this->selected_tab_ )
				c_render::filled_rectangle( { tab_area.x, tab_area.y, tab_area.w, tab_area.h }, { 30, 30, 30 } );

			c_render::text( render.m_tahoma_13( ), tab, tab_area.x + ( tab_area.w / 2 ), tab_area.y + 3, true, i == this->selected_tab_ ? color( 205, 166, 122 )  : color( 255, 255, 255 ) );
			
			c_render::outlined_rectangle( { tab_area.x, tab_area.y, tab_area.w + 1, tab_area.h }, { 35, 35, 35 } );
		}
		
		// inner content.
		c_render::filled_rectangle( { area.x + 8, area.y + 51, area.w - 16, area.h - 59 }, { 10, 10, 10 } );

		// outlines.
		c_render::outlined_rectangle( { area.x, area.y, area.w, 16 }, { 35, 35, 35 } );
		c_render::outlined_rectangle( { area.x + 8, area.y + 23, area.w - 16, 20 }, { 35, 35, 35 } );
		c_render::outlined_rectangle( { area.x + 8, area.y + 51, area.w - 16, area.h - 59 }, { 35, 35, 35 } );
		c_render::outlined_rectangle( area, { 35, 35, 35 } );
	}

	auto input( ) -> void override {
		const auto mouse_position = input_helper.m_mouse_position( );

		// window dragging.
		this->hovering_ = input_helper.is_hovering( { this->area.x, this->area.y, this->area.w, 15 } );
		clicked_ = false;

		if ( c_input_helper::key_down( VK_LBUTTON ) )
			clicked_ = true;

		if ( should_drag_ && !clicked_ )
			should_drag_ = false;

		if ( should_drag_ && clicked_ ) {
			this->area.x = mouse_position.x - drag_offset_.x;
			this->area.y = mouse_position.y - drag_offset_.y;
		}

		if ( this->hovering_ ) {
			should_drag_ = true;
			drag_offset_ = { mouse_position.x - this->area.x, mouse_position.y - this->area.y };
		}

		// tab selection..
		const auto tab_size = ( area.w - 16 ) / this->tabs_.size( );
		for ( auto i{ 0 }; i < this->tabs_.size( ); ++i ) {
			const auto* tab = this->tabs_[ i ];

			const area_t tab_area = { area.x + 8 + ( i * tab_size ), area.y + 23, tab_size, 20 };

			if ( input_helper.is_hovering( tab_area ) && input_helper.key_pressed( VK_LBUTTON ) )
				this->selected_tab_ = i;
		}
	}

	auto add_tab( const char* name ) -> void {
		this->tabs_.push_back( name );
	}

	auto add_groupbox( c_groupbox& groupbox ) -> void {
		groupbox.area.x += this->area.x;
		groupbox.area.y += this->area.y;
		groupboxes_.push_back( groupbox );
	}

	[[nodiscard]] auto m_groupboxes( ) const -> std::vector<c_groupbox> {
		return this->groupboxes_;
	}
};