#pragma once

enum version_t {
	version_release = 0,
	version_debug,
	version_beta
};

class c_core {
	auto determine_version( ) -> void;

public:
	c_core( ) {
		this->determine_version( );
	}

	auto unload( void* module ) const -> void;
	auto initialize( ) const -> void;
	static auto ready( ) -> bool;
	
	int version{};
	bool unloading{};
}; inline c_core core;