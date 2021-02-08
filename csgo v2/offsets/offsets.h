#pragma once


class c_offsets {
	auto get_signatures( ) -> void {
		// todo: connect to my server and retrieve signatures dynamically, +2 internet points
		signatures.vguimatsurface.start_drawing = c_memory::get_signature( "vguimatsurface.dll", "55 8B EC 83 E4 C0 83 EC 38" );
		signatures.vguimatsurface.finish_drawing = c_memory::get_signature( "vguimatsurface.dll", "8B 0D ? ? ? ? 56 C6 05 ? ? ? ? ?" );
	}

	auto get_netvars( ) -> void {
	}
public:
	auto init( ) -> void {
		this->get_signatures( );
		this->get_netvars( );
	}

	// netvars.
	struct {
	} netvars;

	// signatures.
	struct {
		struct {
			uint8_t* start_drawing;
			uint8_t* finish_drawing;
		} vguimatsurface;
	} signatures;
}; inline c_offsets offsets;