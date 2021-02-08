#pragma once

class vertex_t {
public:
	vec2_t m_pos;
	vec2_t m_coord;

public:
	vertex_t( const float x, const float y ) : m_pos{ x, y }, m_coord{ 0.f, 0.f } {}
	explicit vertex_t( const vec2_t& pos ) : m_pos{ pos }, m_coord{ 0.f, 0.f } {}
	vertex_t( const vec2_t& pos, const vec2_t& coord ) : m_pos{ pos }, m_coord{ coord } {}

	void init( const vec2_t& pos, const vec2_t& coord = { 0, 0 } ) {
		m_pos = pos;
		m_coord = coord;
	}
};
