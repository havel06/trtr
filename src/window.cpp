#include "window.h"

constexpr static const size_t board_outline_thickness = 1;
constexpr static const size_t margin_width = 240;
constexpr static const size_t margin_height = 50;
constexpr static const size_t block_width = 32;
constexpr static const size_t window_width = 10 * block_width + 2 * margin_width;
constexpr static const size_t window_height = 20 * block_width + 2 * margin_height;


trtr::window::window() : sf::RenderWindow(sf::VideoMode(window_width, window_height), "trtr", sf::Style::Titlebar | sf::Style::Close)
{
	this->setVerticalSyncEnabled(true);

	m_block_texture.loadFromFile("../texture_single.png");

	m_board_border.setSize({10 * block_width, 20 * block_width});
	m_board_border.setPosition({margin_width, margin_height});
	m_board_border.setOutlineThickness(board_outline_thickness);
	m_board_border.setOutlineColor(sf::Color::White);
	m_board_border.setFillColor(sf::Color::Transparent);

	m_text_font.loadFromFile("../game-of-squids.ttf");
	m_score_number.setFont(m_text_font);
	m_score_number.setPosition({15, window_height / 2.0});
	m_score_number.setString("0");
	m_score_number.setCharacterSize(22);
	m_score_number.setFillColor(sf::Color::White);

	m_level_number.setFont(m_text_font);
	m_level_number.setPosition({15, window_height / 2.0 - 50});
	m_level_number.setString("LEVEL 1");
	m_level_number.setCharacterSize(22);
	m_level_number.setFillColor(sf::Color::White);
}



void trtr::window::draw_board()
{
	for (auto& s : this->m_block_sprites)
	{
		this->draw(s);
	}
}




void trtr::window::draw_score()
{
	this->draw(m_score_number);
}





void trtr::window::draw_level_number()
{
	this->draw(m_level_number);
}




void trtr::window::draw_piece()
{
	for (auto& s : this->m_piece_sprites)
	{
		this->draw(s);
	}
}




void trtr::window::draw_ghost()
{
	for (auto& s : this->m_ghost_sprites)
	{
		this->draw(s);
	}
}





// helper
static sf::Vector2f get_block_screen_coords(unsigned int x, unsigned int y)
{
	return sf::Vector2f(block_width * x + margin_width, window_height - (block_width * (y + 1) + margin_height));
}



// helper
sf::Color trtr::window::get_block_color(trtr::block_type t_type)
{
	switch (t_type)
	{
		case trtr::block_type::cyan: return sf::Color(18, 201, 192);
		case trtr::block_type::blue: return sf::Color(15, 77, 184);
		case trtr::block_type::orange: return sf::Color(220, 125, 14);
		case trtr::block_type::yellow: return sf::Color(197, 230, 16);
		case trtr::block_type::green: return sf::Color(9, 217, 54);
		case trtr::block_type::red: return sf::Color(184, 33, 33);
		case trtr::block_type::purple: return sf::Color(147, 25, 191);
		default: return sf::Color(255, 255, 255);
	}
}

sf::Color trtr::window::get_block_color(trtr::piece_type t_type)
{
	switch (t_type)
	{
		case trtr::piece_type::i: return sf::Color(18, 201, 192);
		case trtr::piece_type::j: return sf::Color(15, 77, 184);
		case trtr::piece_type::l: return sf::Color(220, 125, 14);
		case trtr::piece_type::o: return sf::Color(197, 230, 16);
		case trtr::piece_type::s: return sf::Color(9, 217, 54);
		case trtr::piece_type::z: return sf::Color(184, 33, 33);
		case trtr::piece_type::t: return sf::Color(147, 25, 191);
		default: return sf::Color(255, 255, 255);
	}
}





void trtr::window::update_board(const trtr::board& t_board)
{
	this->m_block_sprites.clear();

	for (std::size_t x = 0; x < t_board.get_width(); ++x)
	{
		for (std::size_t y = 0; y < t_board.get_height(); ++y)
		{
			trtr::block_type type = t_board.get_block(x, y);
			if (type == trtr::block_type::none)
			{
				continue;
			}
			sf::Sprite new_block_sprite(trtr::window::m_block_texture);
			new_block_sprite.setColor(get_block_color(type));
			new_block_sprite.setPosition(get_block_screen_coords(x, y));

			this->m_block_sprites.push_back(std::move(new_block_sprite));
		}
	}
}



void trtr::window::update_piece(const trtr::piece& t_piece)
{
	//TODO - dát do vlastní funkce, tím pádem zkrátit i u update_board
	auto layout = t_piece.get_global_layout();
	auto type = t_piece.get_block_type();
	for (auto i = 0; i < 4; ++i)
	{
		auto [x, y]	= layout.at(i);
		sf::Sprite&  new_block_sprite = m_piece_sprites.at(i);
		new_block_sprite.setTexture(trtr::window::m_block_texture);
		new_block_sprite.setPosition(get_block_screen_coords(x, y));
		new_block_sprite.setColor(get_block_color(type));
	}
}





void trtr::window::update_ghost(trtr::piece_layout t_layout, trtr::block_type t_type)
{
	for (auto i = 0; i < 4; ++i)
	{
		auto [x, y]	= t_layout.at(i);
		sf::Sprite& new_sprite = m_ghost_sprites.at(i);

		new_sprite.setTexture(trtr::window::m_block_texture);
		new_sprite.setPosition(get_block_screen_coords(x, y));

		auto color = get_block_color(t_type);
		color.a = 70;
		new_sprite.setColor(color);

		this->m_ghost_sprites.at(i) = new_sprite;
	}
}




void trtr::window::draw_outline()
{
	this->draw(m_board_border);
}





void trtr::window::update_score(unsigned int t_value)
{
	m_score_number.setString(std::to_string(t_value));
}





void trtr::window::update_level_number(unsigned int t_value)
{
	m_level_number.setString("LEVEL " + std::to_string(t_value));
}




constexpr static const unsigned int preview_height = 100;

void trtr::window::update_preview(const trtr::piece_preview& t_preview)
{
	sf::Vector2f position(window_width - (margin_width / 2.0), margin_height + preview_height / 2.0);

	for (auto i = 0; i < trtr::preview_count; ++i)
	{
		auto & preview_sprites = m_preview_sprites.at(i);
		auto preview_offsets = get_piece_preview_offset(t_preview.get(i));

		for (auto j = 0; j < 4; ++j)
		{
			preview_sprites.at(j).setTexture(m_block_texture);
			preview_sprites.at(j).setPosition(position + preview_offsets.at(j));
			preview_sprites.at(j).setColor(get_block_color(t_preview.get(i)));
		}

		position.y += preview_height;
	}
}




void trtr::window::update_hold(const trtr::piece_type t_type)
{
	sf::Vector2f position(margin_width / 2.0, margin_height + preview_height / 2.0);

	auto preview_offsets = get_piece_preview_offset(t_type);

	for (auto j = 0; j < 4; ++j)
	{
		m_hold_sprites.at(j).setTexture(m_block_texture);
		m_hold_sprites.at(j).setPosition(position + preview_offsets.at(j));
		m_hold_sprites.at(j).setColor(get_block_color(t_type));
	}
}





std::array<sf::Vector2f, 4> trtr::window::get_piece_preview_offset(trtr::piece_type t_type)
{
	switch(t_type)
	{
		case trtr::piece_type::i:
			return {
				sf::Vector2f{block_width * -2.0, block_width * -0.5},
				{block_width * -1.0, block_width * -0.5},
				{0, block_width * -0.5},
				{block_width, block_width * -0.5}
			};
		case trtr::piece_type::j:
			return {
				sf::Vector2f{block_width * -1.5, block_width * -1.0},
				{block_width * -1.5, 0},
				{block_width * -0.5, 0},
				{block_width * 0.5, 0}
			};
		case trtr::piece_type::l:
			return {
				sf::Vector2f{block_width * 0.5, block_width * -1.0},
				{block_width * -1.5, 0},
				{block_width * -0.5, 0},
				{block_width * 0.5, 0}
			};
		case trtr::piece_type::o:
			return {
				sf::Vector2f{block_width * -1.0, block_width * -1.0},
				{0, block_width * -1.0},
				{block_width * -1.0, 0},
				{0, 0}
			};
		case trtr::piece_type::s:
			return {
				sf::Vector2f{block_width * -0.5, block_width * -1.0},
				{block_width * 0.5, block_width * -1.0},
				{block_width * -1.5, 0},
				{block_width * -0.5, 0}
			};
		case trtr::piece_type::t:
			return {
				sf::Vector2f{block_width * -0.5, block_width * -1.0},
				{block_width * -1.5, 0},
				{block_width * -0.5, 0},
				{block_width * 0.5, 0}
			};
		case trtr::piece_type::z:
			return {
				sf::Vector2f{block_width * -0.5, block_width * -1.0},
				{block_width * -1.5, block_width * -1.0},
				{block_width * 0.5, 0},
				{block_width * -0.5, 0}
			};
	}
}





void trtr::window::draw_preview()
{
	for (auto& piece : m_preview_sprites)
	{
		for (auto& block : piece)
		{
			this->draw(block);
		}
	}
}




void trtr::window::draw_hold()
{
	for (auto& block : m_hold_sprites)
	{
		this->draw(block);
	}
}
