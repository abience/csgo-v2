#pragma once
#include <ostream>

class color {
	uint8_t r_{};
	uint8_t g_{};
	uint8_t b_{};
	uint8_t a_{};

public:
	color( const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255 )
		: r_( r ),
		g_( g ),
		b_( b ),
		a_( a ) {
	}

	explicit color( const int hex ) {
		r_ = ( ( hex >> 16 ) & 0xFF ) / 255;
		g_ = ( ( hex >> 8 ) & 0xFF ) / 255;
		b_ = ( ( hex ) & 0xFF ) / 255;
		a_ = 255;
	}

	[[nodiscard]] auto m_r( ) const -> uint8_t {
		return this->r_;
	}

	[[nodiscard]] auto m_g( ) const -> uint8_t {
		return this->g_;
	}

	[[nodiscard]] auto m_b( ) const -> uint8_t {
		return this->b_;
	}

	[[nodiscard]] auto m_a( ) const -> uint8_t {
		return this->a_;
	}

	auto set_alpha( const uint8_t alpha ) -> void {
		this->a_ = alpha;
	}
};