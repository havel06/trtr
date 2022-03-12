#include "game_loop.h"
#include <cmath>
#include <iostream>

trtr::game_loop::game_loop(trtr::window& t_window, unsigned int t_seed) :
	m_random_generator(t_seed),
	m_piece_preview(m_random_generator),
	m_window(t_window)
{ 
	m_window.update_board(m_board);

	new_piece(m_random_generator.get());
}



trtr::game_loop::~game_loop()
{
	// TODO - replace with proper game over screen
	std::cout << "GAME OVER\nLEVEL " << m_level << "\nSCORE " << m_score << "\n";
}



const trtr::piece& trtr::game_loop::get_piece() const
{
	return *this->m_piece;
}


static const sf::Time lock_delay_time = sf::milliseconds(500);

void trtr::game_loop::tick()
{
	if (this->m_piece_fall_clock.getElapsedTime() >= get_piece_fall_time())
	{
		this->m_piece_fall_clock.restart();

		if (this->m_piece->move_down())
		{
			m_lock_delay_clock.restart();
		}
		else if (m_lock_delay_clock.getElapsedTime() >= lock_delay_time)
		{
			land_piece();
		}

		this->m_window.update_piece(*this->m_piece);
	}
}




sf::Time trtr::game_loop::get_piece_fall_time() const
{
	// FIXME - handle speed after level 20
	if (m_soft_drop)
	{
		return sf::milliseconds(30); // TODO - configurable
	}

	return sf::seconds(pow(0.8 - (static_cast<double>((m_level - 1))*0.007), static_cast<double>(m_level - 1)));
}




void trtr::game_loop::land_piece()
{
	m_board.set_blocks(m_piece->get_global_layout(), m_piece->get_block_type());

	auto rows_cleared = m_board.check_for_full_rows();
	m_board.delete_full_rows();

	m_rows_cleared += rows_cleared;
	calculate_score(rows_cleared);
	update_level();

	new_piece(m_piece_preview.cycle());

	m_window.update_board(m_board);
	m_window.update_score(m_score);

	m_hold_available = true;
}




void trtr::game_loop::calculate_score(unsigned int t_rows_cleared)
{
	switch(t_rows_cleared)
	{
		case 1:
			m_score += 100 * m_level;
			break;
		case 2:
			m_score += 300 * m_level;
			break;
		case 3:
			m_score += 500 * m_level;
			break;
		case 4:
			m_score += 800 * m_level;
			break;
		default:
			break;
	}
}




void trtr::game_loop::update_level()
{
	m_level = (m_rows_cleared / 10) + 1;
	m_window.update_level_number(m_level);
}




void trtr::game_loop::hard_drop()
{
	while (m_piece->move_down())
	{
	}

	land_piece();
}




void trtr::game_loop::rotate_clockwise()
{
	if (this->m_piece->rotate_clockwise())
	{
		this->m_window.update_piece(*this->m_piece);
		m_lock_delay_clock.restart();
		m_window.update_ghost(m_piece->get_ghost_layout(), m_piece->get_block_type());
	}
}


void trtr::game_loop::rotate_counterclockwise()
{
	if (this->m_piece->rotate_counterclockwise())
	{
		m_window.update_piece(*m_piece);
		m_lock_delay_clock.restart();
		m_window.update_ghost(m_piece->get_ghost_layout(), m_piece->get_block_type());
	}
}




void trtr::game_loop::set_move_right()
{
	m_desired_direction = trtr::move_direction::right;

	m_fast_side_move_clock.restart();

	if (this->m_piece->move_right())
	{
		this->m_window.update_piece(*this->m_piece);
		m_lock_delay_clock.restart();
		m_window.update_ghost(m_piece->get_ghost_layout(), m_piece->get_block_type());
	}
}




void trtr::game_loop::set_move_left()
{
	m_desired_direction = trtr::move_direction::left;

	m_fast_side_move_clock.restart();

	if (this->m_piece->move_left())
	{
		this->m_window.update_piece(*this->m_piece);
		m_lock_delay_clock.restart();
		m_window.update_ghost(m_piece->get_ghost_layout(), m_piece->get_block_type());
	}
}




void trtr::game_loop::set_move_none()
{
	m_desired_direction = trtr::move_direction::none;
}




static const sf::Time move_press_duration = sf::milliseconds(160); // TODO - configurable
static const sf::Time move_minimal_duration = sf::milliseconds(60); // TODO - configurable

void trtr::game_loop::try_side_move()
{
	if (m_fast_side_move_clock.getElapsedTime() < move_press_duration
		|| m_minmal_side_move_clock.getElapsedTime() < move_minimal_duration)
	{
		return;
	}

	if (m_piece->move(m_desired_direction))
	{
		m_window.update_piece(*this->m_piece);
		m_lock_delay_clock.restart();
		m_window.update_ghost(m_piece->get_ghost_layout(), m_piece->get_block_type());
	}
}




void trtr::game_loop::hold_piece()
{
	if (!m_hold_available)
	{
		return;
	}

	auto last_held_piece = m_held_piece;
	m_held_piece = m_piece->get_piece_type();

	if (last_held_piece == trtr::piece_type::none)	
	{
		new_piece(m_piece_preview.cycle());
	}
	else
	{
		new_piece(last_held_piece);
	}

	m_window.update_hold(m_held_piece);
	m_hold_available = false;
}




void trtr::game_loop::new_piece(trtr::piece_type t_type)
{
	switch (t_type)	
	{
	case trtr::piece_type::i:
		m_piece = std::make_unique<i_piece>(this->m_board);
		break;
	case trtr::piece_type::t:
		m_piece = std::make_unique<t_piece>(this->m_board);
		break;
	case trtr::piece_type::o:
		m_piece = std::make_unique<o_piece>(this->m_board);
		break;
	case trtr::piece_type::s:
		m_piece = std::make_unique<s_piece>(this->m_board);
		break;
	case trtr::piece_type::z:
		m_piece = std::make_unique<z_piece>(this->m_board);
		break;
	case trtr::piece_type::j:
		m_piece = std::make_unique<j_piece>(this->m_board);
		break;
	case trtr::piece_type::l:
		m_piece = std::make_unique<l_piece>(this->m_board);
		break;
	case trtr::piece_type::none:
		throw std::logic_error("invalid piece type");
	}

	m_window.update_preview(m_piece_preview);
	m_window.update_piece(*m_piece);
	m_window.update_ghost(m_piece->get_ghost_layout(), m_piece->get_block_type());
}




void trtr::game_loop::set_soft_drop(bool state)
{
	this->m_soft_drop = state;
}
