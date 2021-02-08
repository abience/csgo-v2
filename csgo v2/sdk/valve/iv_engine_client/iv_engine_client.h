#pragma once

class network_channel {
public:
	uint8_t pad_0x0000[ 0x17 ];
	bool m_b_should_delete;
	int m_n_out_sequence_nr;
	int m_n_in_sequence_nr;
	int m_n_out_sequence_nr_ack;
	int m_n_out_reliable_state;
	int m_n_in_reliable_state;
	int choked_packets;
};

class network_channel_alt {
public:
	enum {
		GENERIC = 0,    // must be first and is default group
		LOCALPLAYER,    // bytes for local player entity update
		OTHERPLAYERS,   // bytes for other players update
		ENTITIES,       // all other entity bytes
		SOUNDS,         // game sounds
		EVENTS,         // event messages
		USERMESSAGES,   // user messages
		ENTMESSAGES,    // entity messages
		VOICE,          // voice data
		STRINGTABLE,    // a stringtable update
		MOVE,           // client move cmds
		STRINGCMD,      // string command
		SIGNON,         // various signondata
		TOTAL,          // must be last and is not a real group
	};

	virtual const char* GetName( void ) const = 0;	            // get channel name
	virtual const char* GetAddress( void ) const = 0;            // get channel IP address as string
	virtual float       GetTime( void ) const = 0;	            // current net time
	virtual float       GetTimeConnected( void ) const = 0;	    // get connection time in seconds
	virtual int         GetBufferSize( void ) const = 0;	        // netchannel packet history size
	virtual int         GetDataRate( void ) const = 0;            // send data rate in byte/sec

	virtual bool        IsLoopback( void ) const = 0;             // true if loopback channel
	virtual bool        IsTimingOut( void ) const = 0;            // true if timing out
	virtual bool        IsPlayback( void ) const = 0;             // true if demo playback

	virtual float       GetLatency( int flow ) const = 0;         // current latency (RTT), more accurate but jittering
	virtual float		GetAvgLatency( int flow ) const = 0;      // average packet latency in seconds
	virtual float       GetAvgLoss( int flow ) const = 0;         // avg packet loss[0..1]
	virtual float       GetAvgChoke( int flow ) const = 0;        // avg packet choke[0..1]
	virtual float       GetAvgData( int flow ) const = 0;         // data flow in bytes/sec
	virtual float       GetAvgPackets( int flow ) const = 0;      // avg packets/sec
	virtual int         GetTotalData( int flow ) const = 0;       // total flow in/out in bytes
	virtual int         GetSequenceNr( int flow ) const = 0;      // last send seq number
	virtual bool        IsValidPacket( int flow, int frame_number ) const = 0;                // true if packet was not lost/dropped/chocked/flushed
	virtual float       GetPacketTime( int flow, int frame_number ) const = 0;                // time when packet was send
	virtual int         GetPacketBytes( int flow, int frame_number, int group ) const = 0;    // group size of this packet
	virtual bool        GetStreamProgress( int flow, int* received, int* total ) const = 0;   // TCP progress if transmitting
	virtual float       GetTimeSinceLastReceived( void ) const = 0;// get time since last recieved packet in seconds
	virtual	float       GetCommandInterpolationAmount( int flow, int frame_number ) const = 0;
	virtual void		GetPacketResponseLatency( int flow, int frame_number, int* pn_latency_msecs, int* pn_choke ) const = 0;
	virtual void		GetRemoteFramerate( float* pflframe_time, float* pflframe_time_std_deviation ) const = 0;

	virtual float		GetTimeoutSeconds( ) const = 0;

};

class iv_engine_client {
public:
	VIRTUAL_FN( get_intersecting_surfaces( const void* model, const vec3_t& center, const float radius, const bool only_visible_surfaces, void* infos, const int max_infos ), 0, int( __thiscall* )( void*, const void*, const vec3_t&, const float, const bool, void*, const int ), model, center, radius, only_visible_surfaces, infos, max_infos ); // 0
	VIRTUAL_FN( get_screen_size( int& width, int& height ), 5, void( __thiscall* )( void*, int&, int& ), width, height ); // 5
	VIRTUAL_FN( get_player_info( const int ent_num, player_info_t* info ), 8, bool( __thiscall* )( void*, int, void* ), ent_num, info ); // 8
	VIRTUAL_FN( get_player_for_user_id( const int user_id ), 9, int( __thiscall* )( void*, int ), user_id ); // 9
	VIRTUAL_FN( get_local_player( void ), 12, int( __thiscall* )( void* ) ); // 12
	VIRTUAL_FN( get_view_angles( vec3_t& va ), 18, void( __thiscall* )( void*, vec3_t& ), va ); // 18
	VIRTUAL_FN( set_view_angles( vec3_t& va ), 19, void( __thiscall* )( void*, vec3_t& ), va ); // 19
	VIRTUAL_FN( get_max_clients( void ), 20, int( __thiscall* )( void* ) ); // 20
	VIRTUAL_FN( is_in_game( void ), 26, bool( __thiscall* )( void* ) ); // 26
	VIRTUAL_FN( is_connected( void ), 27, bool( __thiscall* )( void* ) ); // 27
	VIRTUAL_FN( get_bsp_tree_query( void ), 43, void* ( __thiscall* )( void* ) ); // 43
	VIRTUAL_FN( get_level_name( void ), 52, char const* ( __thiscall* )( void* ) ); // 52
	VIRTUAL_FN( get_network_channel( void ), 78, network_channel* ( __thiscall* )( void* ) ); // 78
	VIRTUAL_FN( get_network_channel_alt( void ), 78, network_channel_alt* ( __thiscall* )( void* ) ); // 78
	VIRTUAL_FN( is_paused( void ), 90, bool( __thiscall* )( void* ) ); // 90
	VIRTUAL_FN( is_hltv( void ), 93, bool( __thiscall* )( void* ) ); // 93
	VIRTUAL_FN( get_screen_aspect_ratio( void ), 100, float( __thiscall* )( void* ) ); // 100
	VIRTUAL_FN( client_cmd_urestricted( const char* cmd_string ), 108, void( __thiscall* )( void*, const char* ), cmd_string ); // 108
};