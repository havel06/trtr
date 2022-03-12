#include "board.h"
#include <algorithm>


std::size_t trtr::board::get_width() const
{
	return m_blocks.at(0).size();
}



std::size_t trtr::board::get_height() const
{
	return m_blocks.size();
}



trtr::board::board()
{
	this->clear();
}



void trtr::board::clear()
{
	for (auto& row : this->m_blocks)
	{
		row.fill(trtr::block_type::none);
	}
}



void trtr::board::set_block(unsigned int x, unsigned int y, trtr::block_type t_type)
{
	this->m_blocks.at(y).at(x) = t_type;
}




void trtr::board::set_blocks(trtr::piece_layout t_layout, trtr::block_type t_type)
{
	for (auto block : t_layout)
	{
		this->set_block(block.x, block.y, t_type);
	}
}





bool trtr::board::check_if_interfere(trtr::coords t_coords) const
{
	// outside the board
	if (   t_coords.x < 0
		|| t_coords.x >= board_width
		|| t_coords.y < 0
		)
	{
		return true;
	}

	// above the board
	if (t_coords.y >= board_height)
	{
		return false;
	}

	// interfere with other blocks
	return (this->get_block(t_coords.x, t_coords.y) != trtr::block_type::none);
}




trtr::block_type trtr::board::get_block(const unsigned int x, const unsigned int y) const
{
	return this->m_blocks.at(y).at(x);
}





unsigned int trtr::board::check_for_full_rows()
{
	auto affected_rows = 0;

	auto contains_block = [](auto block_type){
		return block_type != trtr::block_type::none;
	};

	for (auto i = 0; i < board_height; ++i)
	{
		auto& row = m_blocks.at(i);
		if (std::all_of(row.begin(), row.end(), contains_block))
		{
			m_rows_to_be_deleted.insert(i);
			affected_rows += 1;
		}
	}

	return affected_rows;
}




void trtr::board::delete_full_rows()
{
	for (auto row_index : m_rows_to_be_deleted)
	{
		for (auto i = row_index; i <= board_height - 2; ++i)
		{
			m_blocks.at(i) = m_blocks.at(i + 1);
		}

		m_blocks.at(board_height - 1).fill(trtr::block_type::none);
	}
	m_rows_to_be_deleted.clear();
}
