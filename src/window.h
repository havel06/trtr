#pragma once

#include "board.h"
#include "piece_preview.h"
#include "piece.h"

#include <SFML/Graphics.hpp>

namespace trtr
{
	class window : public sf::RenderWindow
	{
	public:
		window();
		window(const window& other) = delete;
		window(const window&& other) = delete;
		window& operator=(const window& other) = delete;
		window& operator=(const window&& other) = delete;
		~window() override = default;

		void draw_board();
		void draw_piece();
		void draw_ghost();
		void draw_outline();
		void draw_score();
		void draw_level_number();
		void draw_preview();
		void draw_hold();
		void update_board(const trtr::board& t_board);
		void update_piece(const trtr::piece& t_piece);
		void update_ghost(trtr::piece_layout t_layout, trtr::block_type);
		void update_score(unsigned int);
		void update_level_number(unsigned int);
		void update_preview(const trtr::piece_preview&);
		void update_hold(trtr::piece_type);

	private:
		static sf::Color get_block_color(trtr::block_type t_type);
		static sf::Color get_block_color(trtr::piece_type t_type);
		static std::array<sf::Vector2f, 4> get_piece_preview_offset(trtr::piece_type);

		sf::Texture m_block_texture;
		std::vector<sf::Sprite> m_block_sprites{};
		std::array<sf::Sprite, 4> m_piece_sprites{};
		std::array<sf::Sprite, 4> m_ghost_sprites{};
		std::array<sf::Sprite, 4> m_hold_sprites{};
		std::array<std::array<sf::Sprite, 4>, trtr::preview_count> m_preview_sprites{};
		sf::RectangleShape m_board_border{};
		sf::Font m_text_font{};
		sf::Text m_score_number{};
		sf::Text m_level_number{};

	};
} // namespace trtr
