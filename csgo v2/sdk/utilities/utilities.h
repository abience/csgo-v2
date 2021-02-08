#pragma once

class c_utilities {
public:
	template < typename T >
	static auto capture_interface( const char* module, const char* iface, const bool exact = false ) -> T* {
		T* return_interface = nullptr;
		const auto part_match_length = strlen( iface );

		const auto interface_fn = reinterpret_cast< DWORD >( GetProcAddress( GetModuleHandleA( module ), "CreateInterface" ) );
		if ( !interface_fn ) { return nullptr; }

		const auto jump_start = static_cast< unsigned >( interface_fn ) + 4;
		const auto jump_target = jump_start + *reinterpret_cast< unsigned* >( jump_start + 1 ) + 5;

		auto* const register_list = **reinterpret_cast< c_interface_registration*** >( jump_target + 6 );

		for (auto* cur = register_list; cur; cur = cur->next ) {
			if ( exact ) {
				if ( strcmp( cur->name, iface ) == 0 )
					return_interface = static_cast< T* >( cur->create_fn( ) );
			} else {
				if ( !strncmp( cur->name, iface, part_match_length ) && std::atoi( cur->name + part_match_length ) > 0 )
					return_interface = static_cast< T* >( cur->create_fn( ) );
			}
		}

		return return_interface;
	}

	template < typename T >
	static auto get_virtual_function( void* base, const std::uint16_t index ) -> T {
		return ( *static_cast< T** >( base ) )[ index ];
	}
};

#define VIRTUAL_FN( function_name, index, type, ... ) \
	auto function_name { \
		return c_utilities::get_virtual_function< type >( this, index )( this, __VA_ARGS__ ); \
	};