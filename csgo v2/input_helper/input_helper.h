#pragma once

class c_input_helper {
	vec2_t mouse_position_{0, 0};
	float mouse_wheel_delta_{0.f};
	bool pressed_keys_[ 256 ]{};
public:
	auto poll( HWND hwnd, const UINT msg, const WPARAM wparam, const LPARAM lparam ) -> void {
		switch ( msg ) {
		case WM_MOUSEMOVE: {
			this->mouse_position_ = { static_cast< float >( GET_X_LPARAM( lparam ) ), static_cast< float >( GET_Y_LPARAM( lparam ) ) };
			break;
		}
		case WM_MOUSEWHEEL: {
			this->mouse_wheel_delta_ = GET_WHEEL_DELTA_WPARAM( wparam );
			break;
		}
		case WM_LBUTTONDOWN:
		case WM_LBUTTONDBLCLK:
			pressed_keys_[ VK_LBUTTON ] = true;
			break;
		case WM_LBUTTONUP:
			pressed_keys_[ VK_LBUTTON ] = false;
			break;
		case WM_RBUTTONDOWN:
		case WM_RBUTTONDBLCLK:
			pressed_keys_[ VK_RBUTTON ] = true;
			break;
		case WM_RBUTTONUP:
			pressed_keys_[ VK_RBUTTON ] = false;
			break;
		case WM_MBUTTONDOWN:
		case WM_MBUTTONDBLCLK:
			pressed_keys_[ VK_MBUTTON ] = true;
			break;
		case WM_MBUTTONUP:
			pressed_keys_[ VK_MBUTTON ] = false;
			break;
		case WM_XBUTTONDOWN:
		case WM_XBUTTONDBLCLK: {
			UINT button = GET_XBUTTON_WPARAM( wparam );
			if ( button == XBUTTON1 ) {
				pressed_keys_[ VK_XBUTTON1 ] = true;
			} else if ( button == XBUTTON2 ) {
				pressed_keys_[ VK_XBUTTON2 ] = true;
			}
			break;
		}
		case WM_XBUTTONUP: {
			UINT button = GET_XBUTTON_WPARAM( wparam );
			if ( button == XBUTTON1 ) {
				pressed_keys_[ VK_XBUTTON1 ] = false;
			} else if ( button == XBUTTON2 ) {
				pressed_keys_[ VK_XBUTTON2 ] = false;
			}
			break;
		}
		case WM_KEYDOWN: {
			pressed_keys_[ wparam ] = true;
			break;
		}
		case WM_KEYUP:
			pressed_keys_[ wparam ] = false;
			break;
		case WM_SYSKEYDOWN:
			if ( wparam == VK_MENU )
				pressed_keys_[ VK_MENU ] = true;
			break;
		case WM_SYSKEYUP:
			if ( wparam == VK_MENU )
				pressed_keys_[ VK_MENU ] = false;
			break;
		}
	}
	
	[[nodiscard]] auto m_mouse_position( ) const -> vec2_t {
		return this->mouse_position_;
	}

	[[nodiscard]] auto m_mouse_wheel_delta( ) const -> float {
		return this->mouse_wheel_delta_;
	}

	[[nodiscard]] auto is_hovering( const area_t area ) const -> bool {
		return this->mouse_position_.x > area.x && this->mouse_position_.y > area.y && this->mouse_position_.x <
			area.w + area.x && this->mouse_position_.y < area.h + area.y;
	}

	[[nodiscard]] auto key_pressed( const int key ) const -> bool {
		return this->pressed_keys_[ key ];
	}

	[[nodiscard]] static auto key_down( const int key ) -> bool {
		return GetAsyncKeyState( key );
	}
}; inline c_input_helper input_helper;