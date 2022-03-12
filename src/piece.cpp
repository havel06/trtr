#include "piece.h"
#include <algorithm>
#include <stdexcept>

trtr::piece::piece(const trtr::board& t_board) : m_board(t_board)
{
}


trtr::piece_layout trtr::piece::get_local_layout(int rotation_state) const
{
	switch (rotation_state)
	{
	case 0:
		return this->get_layout_0();
		break;
	case 1:
		return this->get_layout_1();
		break;
	case 2:
		return this->get_layout_2();
		break;
	case 3:
		return this->get_layout_3();
		break;
	default:
		throw std::logic_error("rotation is not valid");
	}
}



trtr::piece_layout trtr::piece::get_global_layout(int t_rotation_state) const
{
	trtr::piece_layout current_layout = this->get_local_layout(t_rotation_state);
	for (auto& block : current_layout)
	{
		block.x += this->m_global_positon.x;	
		block.y += this->m_global_positon.y;	
	}
	return current_layout;
}

trtr::piece_layout trtr::piece::get_global_layout() const
{
	return this->get_global_layout(m_rotation_state);
}






int trtr::piece::get_rotation_state() const
{
	return m_rotation_state;
}




bool trtr::piece::move_down()
{
	if (check_if_valid_positions(this->get_global_layout().transform({0, -1})))
	{
		this->m_global_positon.y -= 1;	
		return true;
	}
	return false;
}




bool trtr::piece::move_left()
{
	if (check_if_valid_positions(get_global_layout().transform({-1, 0})))
	{
		m_global_positon.x -= 1;
		return true;
	}
	return false;
}





bool trtr::piece::move_right()
{
	if (check_if_valid_positions(get_global_layout().transform({1, 0})))
	{
		m_global_positon.x += 1;
		return true;
	}
	return false;
}



bool trtr::piece::move(trtr::move_direction t_direction)
{
	if (t_direction == trtr::move_direction::right)
	{
		return trtr::piece::move_right();
	}

	if (t_direction == trtr::move_direction::left)
	{
		return trtr::piece::move_left();
	}

	return false;
}




int trtr::piece::get_next_rotation_state(int t_rotation_state)
{
	return (t_rotation_state + 1) % 4;
}


int trtr::piece::get_previous_rotation_state(int t_rotation_state)
{
	return (t_rotation_state + 3) % 4;
}




trtr::piece_layout trtr::piece::get_ghost_layout() const
{
	trtr::piece_layout current_layout = get_global_layout();

	while (check_if_valid_positions(current_layout))
	{
		current_layout = current_layout.transform({0, -1});
	}
	
	return current_layout.transform({0, 1});
}




trtr::coords trtr::piece::get_clockwise_rotation_offset(int t_rotation_state, int phase) const
{
	switch (phase)
	{
		case 0:
			return this->get_clockwise_rotation_offset_0(t_rotation_state);
		case 1:
			return this->get_clockwise_rotation_offset_1(t_rotation_state);
		case 2:
			return this->get_clockwise_rotation_offset_2(t_rotation_state);
		case 3:
			return this->get_clockwise_rotation_offset_3(t_rotation_state);
		default:
			throw std::logic_error("invlaid phase");
	}
}

trtr::coords trtr::piece::get_counterclockwise_rotation_offset(int t_rotation_state, int phase) const
{
	switch (phase)
	{
		case 0:
			return this->get_counterclockwise_rotation_offset_0(t_rotation_state);
		case 1:
			return this->get_counterclockwise_rotation_offset_1(t_rotation_state);
		case 2:
			return this->get_counterclockwise_rotation_offset_2(t_rotation_state);
		case 3:
			return this->get_counterclockwise_rotation_offset_3(t_rotation_state);
		default:
			throw std::logic_error("invlaid phase");
	}
}





bool trtr::piece::rotate_clockwise()
{
	auto next_rotation_state = get_next_rotation_state(get_rotation_state());
	auto next_global_layout = get_global_layout(next_rotation_state);

	// without wall kick
	if (check_if_valid_positions(next_global_layout))
	{
		m_rotation_state = next_rotation_state;
		return true;
	}

	// with wall kick
	for (auto i = 0; i <= 3; i++)
	{
		auto offset = this->get_clockwise_rotation_offset(get_rotation_state(), i);

		if (check_if_valid_positions(next_global_layout.transform(offset)))
		{
			m_rotation_state = next_rotation_state;
			m_global_positon += offset;
			return true;
		}
	}

	return false;
}




bool trtr::piece::rotate_counterclockwise()
{
	auto next_rotation_state = get_previous_rotation_state(get_rotation_state());
	auto next_global_layout = get_global_layout(next_rotation_state);

	// without wall kick
	if (check_if_valid_positions(next_global_layout))
	{
		m_rotation_state = next_rotation_state;
		return true;
	}

	// with wall kick
	for (auto i = 0; i <= 3; i++)
	{
		auto offset = this->get_counterclockwise_rotation_offset(get_rotation_state(), i);

		if (check_if_valid_positions(next_global_layout.transform(offset)))
		{
			m_rotation_state = next_rotation_state;
			m_global_positon += offset;
			return true;
		}
	}

	return false;

}





bool trtr::piece::check_if_valid_positions(const trtr::piece_layout& t_layout) const
{
	return std::none_of(t_layout.begin(), t_layout.end(),
		[this](auto coords)
		{
			return this->m_board.check_if_interfere(coords);
		});
}



trtr::block_type trtr::i_piece::get_block_type() const
{
	return trtr::block_type::cyan;
}

trtr::piece_type trtr::i_piece::get_piece_type() const
{
	return trtr::piece_type::i;
}

trtr::piece_layout trtr::i_piece::get_layout_0() const
{
	return {trtr::coords{0, 2}, {1, 2}, {2, 2}, {3, 2}};
}

trtr::piece_layout trtr::i_piece::get_layout_1() const
{
	return {trtr::coords{2, 0}, {2, 1}, {2, 2}, {2, 3}};
}

trtr::piece_layout trtr::i_piece::get_layout_2() const
{
	return {trtr::coords{0, 1}, {1, 1}, {2, 1}, {3, 1}};
}

trtr::piece_layout trtr::i_piece::get_layout_3() const
{
	return {trtr::coords{1, 0}, {1, 1}, {1, 2}, {1, 3}};
}


trtr::coords trtr::i_piece::get_clockwise_rotation_offset_0 (int rotation_state) const
{
	switch (rotation_state)
	{
		case 0:
			return {-2, 0};
		case 1:
			return {-1, 0};
		case 2:
			return {2, 0};
		case 3:
			return {1, 0};
		default:
			throw std::logic_error("invalid rotation");
	}
}

trtr::coords trtr::i_piece::get_clockwise_rotation_offset_1 (int rotation_state) const
{
	return this->get_clockwise_rotation_offset_0(3 - rotation_state);
}

trtr::coords trtr::i_piece::get_clockwise_rotation_offset_2 (int rotation_state) const
{
	switch (rotation_state)
	{
		case 0:
			return {-2, 1};
		case 1:
			return {-1, 2};
		case 2:
			return {2, 1};
		case 3:
			return {1, -2};
		default:
			throw std::logic_error("invalid rotation");
	}
}

trtr::coords trtr::i_piece::get_clockwise_rotation_offset_3 (int rotation_state) const
{
	switch (rotation_state)
	{
		case 0:
			return {1, 2};
		case 1:
			return {2, -1};
		case 2:
			return {-1, -2};
		case 3:
			return {-2, 1};
		default:
			throw std::logic_error("invalid rotation");
	}
}

trtr::coords trtr::i_piece::get_counterclockwise_rotation_offset_0 (int rotation_state) const
{
	switch (rotation_state)
	{
		case 0:
			return {-1, 0};
		case 1:
			return {2, 0};
		case 2:
			return {1, 0};
		case 3:
			return {-2, 0};
		default:
			throw std::logic_error("invalid rotation");
	}
}

trtr::coords trtr::i_piece::get_counterclockwise_rotation_offset_1 (int rotation_state) const
{
	switch (rotation_state)
	{
		case 0:
			return {2, 0};
		case 1:
			return {-1, 0};
		case 2:
			return {-2, 0};
		case 3:
			return {1, 0};
		default:
			throw std::logic_error("invalid rotation");
	}
}


trtr::coords trtr::i_piece::get_counterclockwise_rotation_offset_2 (int rotation_state) const
{
	switch (rotation_state)
	{
		case 0:
			return {-1, 2};
		case 1:
			return {2, 1};
		case 2:
			return {1, -2};
		case 3:
			return {-2, -1};
		default:
			throw std::logic_error("invalid rotation");
	}
}

trtr::coords trtr::i_piece::get_counterclockwise_rotation_offset_3 (int rotation_state) const
{
	switch (rotation_state)
	{
		case 0:
			return {2, -1};
		case 1:
			return {-1, -2};
		case 2:
			return {-2, 1};
		case 3:
			return {1, 2};
		default:
			throw std::logic_error("invalid rotation");
	}
}





// helper functions for j l t s z piece, to avoid code repetition

static trtr::coords helper_get_clockwise_rotation_offset_0 (int rotation_state)
{
	switch (rotation_state)
	{
		case 0:
		case 3:
			return {-1, 0};
		case 1:
		case 2:
			return {1, 0};
		default:
			throw std::logic_error("invalid rotation state");
	}
}

static trtr::coords helper_get_clockwise_rotation_offset_1 (int rotation_state)
{
	switch (rotation_state)
	{
		case 0:
			return {-1, 1};
		case 1:
			return {1, -1};
		case 2:
			return {1, 1};
		case 3:
			return {-1, -1};
		default:
			throw std::logic_error("invalid rotation state");
	}
}

static trtr::coords helper_get_clockwise_rotation_offset_2 (int rotation_state)
{
	switch (rotation_state)
	{
		case 0:
		case 2:
			return {0, -2};
		case 1:
		case 3:
			return {0, 2};
		default:
			throw std::logic_error("invalid rotation state");
	}
}

static trtr::coords helper_get_clockwise_rotation_offset_3 (int rotation_state)
{
	switch (rotation_state)
	{
		case 0:
			return {-1, -2};
		case 1:
			return {1, 2};
		case 2:
			return {1, -2};
		case 3:
			return {-1, 2};
		default:
			throw std::logic_error("invalid rotation state");
	}
}

static trtr::coords helper_get_counterclockwise_rotation_offset_0 (int rotation_state)
{
	switch (rotation_state)
	{
		case 0:
		case 1:
			return {1, 0};
		case 2:
		case 3:
			return {-1, 0};
		default:
			throw std::logic_error("invalid rotation state");
	}
}

static trtr::coords helper_get_counterclockwise_rotation_offset_1 (int rotation_state)
{
	switch (rotation_state)
	{
		case 0:
			return {1, 1};
		case 1:
			return {1, -1};
		case 2:
			return {-1, 1};
		case 3:
			return {-1, -1};
		default:
			throw std::logic_error("invalid rotation state");
	}
}

static trtr::coords helper_get_counterclockwise_rotation_offset_2 (int rotation_state)
{
	switch (rotation_state)
	{
		case 0:
		case 2:
			return {0, -2};
		case 1:
		case 3:
			return {0, 2};
		default:
			throw std::logic_error("invalid rotation state");
	}
}

static trtr::coords helper_get_counterclockwise_rotation_offset_3 (int rotation_state)
{
	switch (rotation_state)
	{
		case 0:
			return {1, -2};
		case 1:
			return {1, 2};
		case 2:
			return {-1, -2};
		case 3:
			return {-1, 2};
		default:
			throw std::logic_error("invalid rotation state");
	}
}



trtr::block_type trtr::j_piece::get_block_type() const
{
	return trtr::block_type::blue;
}

trtr::piece_type trtr::j_piece::get_piece_type() const
{
	return trtr::piece_type::j;
}

trtr::piece_layout trtr::j_piece::get_layout_0() const
{
	return {trtr::coords{0, 3}, {0, 2}, {1, 2}, {2, 2}};
}

trtr::piece_layout trtr::j_piece::get_layout_1() const
{
	return {trtr::coords{1, 1}, {1, 2}, {1, 3}, {2, 3}};
}

trtr::piece_layout trtr::j_piece::get_layout_2() const
{
	return {trtr::coords{2, 1}, {0, 2}, {1, 2}, {2, 2}};
}

trtr::piece_layout trtr::j_piece::get_layout_3() const
{
	return {trtr::coords{1, 1}, {1, 2}, {1, 3}, {0, 1}};
}

trtr::coords trtr::j_piece::get_clockwise_rotation_offset_0 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_0(rotation_state);
}

trtr::coords trtr::j_piece::get_clockwise_rotation_offset_1 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_1(rotation_state);
}

trtr::coords trtr::j_piece::get_clockwise_rotation_offset_2 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_2(rotation_state);
}

trtr::coords trtr::j_piece::get_clockwise_rotation_offset_3 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_3(rotation_state);
}

trtr::coords trtr::j_piece::get_counterclockwise_rotation_offset_0 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_0(rotation_state);
}

trtr::coords trtr::j_piece::get_counterclockwise_rotation_offset_1 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_1(rotation_state);
}

trtr::coords trtr::j_piece::get_counterclockwise_rotation_offset_2 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_2(rotation_state);
}

trtr::coords trtr::j_piece::get_counterclockwise_rotation_offset_3 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_3(rotation_state);
}





trtr::block_type trtr::l_piece::get_block_type() const
{
	return trtr::block_type::orange;
}

trtr::piece_type trtr::l_piece::get_piece_type() const
{
	return trtr::piece_type::l;
}

trtr::piece_layout trtr::l_piece::get_layout_0() const
{
	return {trtr::coords{0, 2}, {1, 2}, {2, 2}, {2, 3}};
}

trtr::piece_layout trtr::l_piece::get_layout_1() const
{
	return {trtr::coords{1, 3}, {1, 2}, {1, 1}, {2, 1}};
}

trtr::piece_layout trtr::l_piece::get_layout_2() const
{
	return {trtr::coords{0, 2}, {1, 2}, {2, 2}, {0, 1}};
}

trtr::piece_layout trtr::l_piece::get_layout_3() const
{
	return {trtr::coords{1, 3}, {1, 2}, {1, 1}, {0, 3}};
}

trtr::coords trtr::l_piece::get_clockwise_rotation_offset_0 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_0(rotation_state);
}

trtr::coords trtr::l_piece::get_clockwise_rotation_offset_1 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_1(rotation_state);
}

trtr::coords trtr::l_piece::get_clockwise_rotation_offset_2 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_2(rotation_state);
}

trtr::coords trtr::l_piece::get_clockwise_rotation_offset_3 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_3(rotation_state);
}

trtr::coords trtr::l_piece::get_counterclockwise_rotation_offset_0 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_0(rotation_state);
}

trtr::coords trtr::l_piece::get_counterclockwise_rotation_offset_1 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_1(rotation_state);
}

trtr::coords trtr::l_piece::get_counterclockwise_rotation_offset_2 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_2(rotation_state);
}

trtr::coords trtr::l_piece::get_counterclockwise_rotation_offset_3 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_3(rotation_state);
}




trtr::block_type trtr::o_piece::get_block_type() const
{
	return trtr::block_type::yellow;
}

trtr::piece_type trtr::o_piece::get_piece_type() const
{
	return trtr::piece_type::o;
}

trtr::piece_layout trtr::o_piece::get_layout_0() const
{
	return {trtr::coords{1, 3}, {1, 2}, {2, 3}, {2, 2}};
}

trtr::piece_layout trtr::o_piece::get_layout_1() const
{
	return this->get_layout_0();
}

trtr::piece_layout trtr::o_piece::get_layout_2() const
{
	return this->get_layout_0();
}

trtr::piece_layout trtr::o_piece::get_layout_3() const
{
	return this->get_layout_0();
}

trtr::coords trtr::o_piece::get_clockwise_rotation_offset_0 (int /*rotation_state*/) const
{
	return {0, 0};
}

trtr::coords trtr::o_piece::get_clockwise_rotation_offset_1 (int /*rotation_state*/) const
{
	return {0, 0};
}

trtr::coords trtr::o_piece::get_clockwise_rotation_offset_2 (int /*rotation_state*/) const
{
	return {0, 0};
}

trtr::coords trtr::o_piece::get_clockwise_rotation_offset_3 (int /*rotation_state*/) const
{
	return {0, 0};
}

trtr::coords trtr::o_piece::get_counterclockwise_rotation_offset_0 (int /*rotation_state*/) const
{
	return {0, 0};
}

trtr::coords trtr::o_piece::get_counterclockwise_rotation_offset_1 (int /*rotation_state*/) const
{
	return {0, 0};
}

trtr::coords trtr::o_piece::get_counterclockwise_rotation_offset_2 (int /*rotation_state*/) const
{
	return {0, 0};
}

trtr::coords trtr::o_piece::get_counterclockwise_rotation_offset_3 (int /*rotation_state*/) const
{
	return {0, 0};
}





trtr::block_type trtr::s_piece::get_block_type() const
{
	return trtr::block_type::green;
}

trtr::piece_type trtr::s_piece::get_piece_type() const
{
	return trtr::piece_type::s;
}

trtr::piece_layout trtr::s_piece::get_layout_0() const
{
	return {trtr::coords{0, 2}, {1, 2}, {1, 3}, {2, 3}};
}

trtr::piece_layout trtr::s_piece::get_layout_1() const
{
	return {trtr::coords{2, 1}, {1, 2}, {1, 3}, {2, 2}};
}

trtr::piece_layout trtr::s_piece::get_layout_2() const
{
	return {trtr::coords{0, 1}, {1, 1}, {1, 2}, {2, 2}};
}

trtr::piece_layout trtr::s_piece::get_layout_3() const
{
	return {trtr::coords{1, 1}, {0, 2}, {0, 3}, {1, 2}};
}

trtr::coords trtr::s_piece::get_clockwise_rotation_offset_0 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_0(rotation_state);
}

trtr::coords trtr::s_piece::get_clockwise_rotation_offset_1 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_1(rotation_state);
}

trtr::coords trtr::s_piece::get_clockwise_rotation_offset_2 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_2(rotation_state);
}

trtr::coords trtr::s_piece::get_clockwise_rotation_offset_3 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_3(rotation_state);
}

trtr::coords trtr::s_piece::get_counterclockwise_rotation_offset_0 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_0(rotation_state);
}

trtr::coords trtr::s_piece::get_counterclockwise_rotation_offset_1 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_1(rotation_state);
}

trtr::coords trtr::s_piece::get_counterclockwise_rotation_offset_2 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_2(rotation_state);
}

trtr::coords trtr::s_piece::get_counterclockwise_rotation_offset_3 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_3(rotation_state);
}




trtr::block_type trtr::t_piece::get_block_type() const
{
	return trtr::block_type::purple;
}

trtr::piece_type trtr::t_piece::get_piece_type() const
{
	return trtr::piece_type::t;
}

trtr::piece_layout trtr::t_piece::get_layout_0() const
{
	return {trtr::coords{0, 2}, {1, 2}, {2, 2}, {1, 3}};
}

trtr::piece_layout trtr::t_piece::get_layout_1() const
{
	return {trtr::coords{1, 2}, {2, 2}, {1, 3}, {1, 1}};
}

trtr::piece_layout trtr::t_piece::get_layout_2() const
{
	return {trtr::coords{1, 2}, {2, 2}, {0, 2}, {1, 1}};
}

trtr::piece_layout trtr::t_piece::get_layout_3() const
{
	return {trtr::coords{0, 2}, {1, 2}, {1, 1}, {1, 3}};
}

trtr::coords trtr::t_piece::get_clockwise_rotation_offset_0 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_0(rotation_state);
}

trtr::coords trtr::t_piece::get_clockwise_rotation_offset_1 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_1(rotation_state);
}

trtr::coords trtr::t_piece::get_clockwise_rotation_offset_2 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_2(rotation_state);
}

trtr::coords trtr::t_piece::get_clockwise_rotation_offset_3 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_3(rotation_state);
}

trtr::coords trtr::t_piece::get_counterclockwise_rotation_offset_0 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_0(rotation_state);
}

trtr::coords trtr::t_piece::get_counterclockwise_rotation_offset_1 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_1(rotation_state);
}

trtr::coords trtr::t_piece::get_counterclockwise_rotation_offset_2 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_2(rotation_state);
}

trtr::coords trtr::t_piece::get_counterclockwise_rotation_offset_3 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_3(rotation_state);
}





trtr::block_type trtr::z_piece::get_block_type() const
{
	return trtr::block_type::red;
}

trtr::piece_type trtr::z_piece::get_piece_type() const
{
	return trtr::piece_type::z;
}

trtr::piece_layout trtr::z_piece::get_layout_0() const
{
	return {trtr::coords{0, 3}, {1, 3}, {1, 2}, {2, 2}};
}

trtr::piece_layout trtr::z_piece::get_layout_1() const
{
	return {trtr::coords{1, 1}, {2, 3}, {1, 2}, {2, 2}};
}

trtr::piece_layout trtr::z_piece::get_layout_2() const
{
	return {trtr::coords{0, 2}, {1, 2}, {1, 1}, {2, 1}};
}

trtr::piece_layout trtr::z_piece::get_layout_3() const
{
	return {trtr::coords{0, 1}, {1, 3}, {0, 2}, {1, 2}};
}

trtr::coords trtr::z_piece::get_clockwise_rotation_offset_0 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_0(rotation_state);
}

trtr::coords trtr::z_piece::get_clockwise_rotation_offset_1 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_1(rotation_state);
}

trtr::coords trtr::z_piece::get_clockwise_rotation_offset_2 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_2(rotation_state);
}

trtr::coords trtr::z_piece::get_clockwise_rotation_offset_3 (int rotation_state) const
{
	return helper_get_clockwise_rotation_offset_3(rotation_state);
}

trtr::coords trtr::z_piece::get_counterclockwise_rotation_offset_0 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_0(rotation_state);
}

trtr::coords trtr::z_piece::get_counterclockwise_rotation_offset_1 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_1(rotation_state);
}

trtr::coords trtr::z_piece::get_counterclockwise_rotation_offset_2 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_2(rotation_state);
}

trtr::coords trtr::z_piece::get_counterclockwise_rotation_offset_3 (int rotation_state) const
{
	return helper_get_counterclockwise_rotation_offset_3(rotation_state);
}
