#pragma once

class c_interface_registration {
	using interface_fn = void* ( * )( );
public:
	c_interface_registration( ) = delete;
	interface_fn create_fn;
	const char* name;
	c_interface_registration* next;
};