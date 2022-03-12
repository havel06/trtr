#pragma once

#include "block.h"

#include <array>
#include <set>

constexpr inline const std::size_t board_width = 10;
constexpr inline const std::size_t board_height = 20;

namespace trtr
{
	class board
	{
	public:
		board();

		[[nodiscard]] std::size_t get_width() const;
		[[nodiscard]] std::size_t get_height() const;

		void clear();
		void set_block(unsigned int x, unsigned int y, trtr::block_type t_type);
		void set_blocks(trtr::piece_layout t_layout, trtr::block_type t_type);
		unsigned int check_for_full_rows();
		void delete_full_rows();
		[[nodiscard]] trtr::block_type get_block(unsigned int x, unsigned int y) const;
		[[nodiscard]] bool check_if_interfere(trtr::coords) const;
		
	private:
		std::array<std::array<trtr::block_type, board_width>, board_height> m_blocks{};
		std::set<unsigned int, std::greater<>> m_rows_to_be_deleted{};
	};
} // namespace trtr
