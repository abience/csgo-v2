#pragma once

class i_base_client {
public:
	VIRTUAL_FN( get_all_classes( ), 8, client_class* ( __thiscall* )( void* ) );
	VIRTUAL_FN( dispatch_user_message( int msg_type, unsigned int arg1, unsigned int length, const void* data = nullptr ), 38, client_class* ( __thiscall* )( void*, int, unsigned int, unsigned int, const void* ), msg_type, arg1, length, data );
};

enum client_frame_stage_t {
	FRAME_UNDEFINED = -1,
	FRAME_START,
	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,
	FRAME_RENDER_START,
	FRAME_RENDER_END
};