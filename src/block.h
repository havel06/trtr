#pragma once

#include <array>


namespace trtr
{
	enum class block_type {none, cyan, blue, orange, yellow, green, red, purple};

	struct coords
	{
		int x;
		int y;

		coords operator+(const coords& other) const;
		coords operator-(const coords& other) const;
		coords& operator+=(const coords& other);
		coords& operator-=(const coords& other);
	};

	struct piece_layout : public std::array<trtr::coords, 4>
	{
		piece_layout transform(coords);
	};
} // namespace tetris
