#pragma once

class vmt_hook {
private:
	uintptr_t* vmt_;
public:
	uintptr_t** p_interface = nullptr;
	uintptr_t* original_vmt = nullptr;
	uint32_t method_count = 0;

	vmt_hook( ) {
	}

	vmt_hook( void* p_interface ) {
		this->p_interface = static_cast< uintptr_t** >( p_interface );

		size_t method_count = 0;

		while ( reinterpret_cast< uintptr_t* >( *this->p_interface )[ method_count ] )
			method_count++;

		original_vmt = *this->p_interface;

		vmt_ = new uintptr_t[ method_count + 1 ];

		memcpy( vmt_, &original_vmt[ -1 ], ( sizeof( uintptr_t ) * method_count ) + sizeof( uintptr_t ) );
	}

	auto hook( void* method, const size_t method_index ) const -> void {
		vmt_[ method_index + 1 ] = reinterpret_cast< uintptr_t >( method );
	}

	auto apply( ) const -> void {
		*this->p_interface = &vmt_[ 1 ];
	}

	auto release( ) const -> void {
		*this->p_interface = original_vmt;
		delete[ ] vmt_;
	}

	template<typename Fn>
	auto get_original( const size_t index ) -> Fn {
		return reinterpret_cast< Fn >( original_vmt[ index ] );
	}
};