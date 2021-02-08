#pragma once

class c_menu {
    std::vector<c_window> windows_;
public:
    auto add_window( const c_window& window ) -> void {
        this->windows_.push_back( window );
    }

    auto init( ) -> void {
        auto main_window = c_window( "geminisoftware", { 50, 50, 500, 300 } );

        main_window.add_tab( "aimbot" );
        {
            auto groupbox = c_groupbox( "epic", { 100, 100, 100, 100 }, 0 );
            main_window.add_groupbox( groupbox );
        }

        main_window.add_tab( "visuals" );
        {

        }

        main_window.add_tab( "misc" );
        {

        }

        this->add_window( main_window );
    }

    static auto adjust_area( area_t& from, const area_t to ) -> void {
        from.x += to.x;
        from.y += to.y;
    }

    auto draw( ) -> void {
        for ( auto& window : this->windows_ ) {
            window.paint( );

            for ( auto& groupbox : window.m_groupboxes( ) ) {
                adjust_area( groupbox.area, window.area );
                groupbox.paint( );
            }
        }
    }

    auto input( ) -> void {
        for ( auto& window : this->windows_ ) {
            window.input( );

            for ( auto& groupbox : window.m_groupboxes( ) ) {
                groupbox.input( );
            }
        }
    }
}; inline c_menu menu;