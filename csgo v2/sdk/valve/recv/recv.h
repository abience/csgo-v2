#pragma once

struct recv_prop;

class d_variant {
public:
	union {
		float	m_Float;
		long	m_Int;
		char* m_pString;
		void* m_pData;
		vec3_t m_vector;
	};
};

enum class send_prop_type {
	DPT_Int = 0,
	DPT_Float,
	DPT_vector,
	DPT_vectorXY, // Only encodes the XY of a vector, ignores Z
	DPT_String,
	DPT_Array,     // An array of the base types (can't be of datatables).
	DPT_DataTable,
	DPT_Int64,
	DPT_NUMSendPropTypes
};

class c_recv_proxy_data {
public:
	const recv_prop* m_pRecvProp;
	char _pad[ 4 ];//csgo ( for l4d keep it commented out :) )
	d_variant		m_Value;
	int				m_iElement;
	int				m_ObjectID;
};

typedef void( *recv_var_proxy_fn )( const c_recv_proxy_data* pData, void* pStruct, void* pOut );

struct recv_table {
	recv_prop* m_pProps;
	int				m_nProps;
	void* m_pDecoder;
	char* m_pNetTableName;
	bool			m_bInitialized;
	bool			m_bInMainList;
};

struct recv_prop {
	char* m_pVarName;
	int						m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;
	bool					m_bInsideArray;
	const void* m_pExtraData;
	recv_prop* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	recv_table* m_pDataTable;
	int						m_Offset;
	int						m_ElementStride;
	int						m_nElements;
	const char* m_pParentArrayPropName;
};

class client_class {
public:
	void* m_pCreateFn;
	void* m_pCreateEventFn;
	char* network_name;
	recv_table* m_pRecvTable;
	client_class* m_pNext;
	int				m_ClassID;
};