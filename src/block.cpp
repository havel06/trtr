#include "block.h"

trtr::coords trtr::coords::operator+(const coords& other) const
{
	return { x + other.x, y + other.y };
}

trtr::coords trtr::coords::operator-(const coords& other) const
{
	return { x - other.x, y - other.y };
}

trtr::coords& trtr::coords::operator+=(const coords& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

trtr::coords& trtr::coords::operator-=(const coords& other)
{

	this->x -= other.x;
	this->y -= other.y;
	return *this;
}




trtr::piece_layout trtr::piece_layout::transform(const trtr::coords t_coords)
{
	trtr::piece_layout result = *this;

	for (auto& c : result)
	{
		c += t_coords;
	}

	return result;
}
