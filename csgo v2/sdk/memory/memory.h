#pragma once

class c_memory {
public:
	static auto get_pattern( const DWORD address, const DWORD length, const char* pattern ) -> DWORD {
		if ( !address || !length || !pattern )
			return 0;

		const auto* patter_pointer = pattern;
		DWORD match_data = 0;
		DWORD return_data = 0;

		for ( auto p_data_patch = address; p_data_patch < length; p_data_patch++ ) {
			if ( !*patter_pointer )
				return_data = match_data;

			if ( *PBYTE( patter_pointer ) == '\?' || *reinterpret_cast< BYTE* >( p_data_patch ) == ( (
				patter_pointer[ 0 ] >= '0' && patter_pointer[ 0 ] <= '9'
				? patter_pointer[ 0 ] - '0'
				: ( patter_pointer[ 0 ] & ~32 ) - 'A' + 10 ) << 4 | ( patter_pointer[ 1 ] >= '0' && patter_pointer[ 1 ] <= '9'
				? patter_pointer[ 1 ] - '0'
				: ( patter_pointer[ 1 ] & ~32 ) - 'A' + 10 ) ) ) {
				if ( !match_data )
					match_data = p_data_patch;

				if ( !patter_pointer[ 2 ] )
					return_data = match_data;

				patter_pointer += *PWORD( patter_pointer ) == 16191 || *PBYTE( patter_pointer ) != '\?' ? 3 : 2;
			} else {
				patter_pointer = pattern;
				match_data = 0;
			}
		}

		return return_data;
	};

	static auto get_signature( const char* module_name, const char* signature ) -> std::uint8_t* {
		auto* const module_handle = GetModuleHandleA( module_name );

		if ( !module_handle )
			return nullptr;

		static auto pattern_to_byte = [ ]( const char* pattern ) {
			auto bytes = std::vector<int>{};
			auto* const start = const_cast< char* >( pattern );
			auto* const end = const_cast< char* >( pattern ) + std::strlen( pattern );

			for ( auto* current = start; current < end; ++current ) {
				if ( *current == '?' ) {
					++current;

					if ( *current == '?' )
						++current;

					bytes.push_back( -1 );
				} else {
					bytes.push_back( std::strtoul( current, &current, 16 ) );
				}
			}
			return bytes;
		};

		auto* const dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( module_handle );
		auto* const nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< std::uint8_t* >( module_handle ) +
																		dos_header->e_lfanew );

		const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
		auto pattern_bytes = pattern_to_byte( signature );
		auto* const scan_bytes = reinterpret_cast< std::uint8_t* >( module_handle );

		const auto s = pattern_bytes.size( );
		auto* const d = pattern_bytes.data( );

		for ( auto i = 0ul; i < size_of_image - s; ++i ) {
			auto found = true;

			for ( auto j = 0ul; j < s; ++j ) {
				if ( scan_bytes[ i + j ] != d[ j ] && d[ j ] != -1 ) {
					found = false;
					break;
				}
			}

			if ( found )
				return &scan_bytes[ i ];
		}

		return nullptr;
	}
};