#ifndef LANDSCAPE_H
#define LANDSCAPE_H

class Landscape : public BaseClass
{
private:

	struct landscape_t
	{
		union
		{

		};
	};

private:

	Address m_address;
	landscape_t m_data;

public:

	Landscape();
	Landscape(Address address);

public:

	void Update();

	Address GetAddress();
};

#endif