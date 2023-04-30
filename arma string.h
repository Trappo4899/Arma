#ifndef ARMA_STRING_H
#define ARMA_STRING_H

class ArmaString
{
public:

	struct A3_STRING_DATA_T
	{
		INT64 m_references;		// 0x00000
		INT64 m_size;			// 0x00008
		CHAR* m_string;			// 0x00010
	};

private:

	UINT_PTR m_address;
	A3_STRING_DATA_T m_data;

public:

	ArmaString();

	ArmaString(UINT_PTR address);

	void Update();

	A3_STRING_DATA_T GetData();
};

#endif