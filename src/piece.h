#pragma once

#include "block.h"
#include "board.h"
#include "src/random_generator.h"

namespace trtr
{
	
constexpr static const unsigned int starting_x_coord = 3;
constexpr static const unsigned int starting_y_coord = 18;

enum class move_direction {left, right, none};

class piece
{
public:
	explicit piece(const trtr::board& board);
	piece(const piece&) = default;
	piece(piece&&) = default;
	virtual ~piece() = default;

	[[nodiscard]] virtual trtr::block_type get_block_type() const = 0;
	[[nodiscard]] virtual trtr::piece_type get_piece_type() const = 0;
	[[nodiscard]] piece_layout get_global_layout() const;
	[[nodiscard]] piece_layout get_global_layout(int rotation_state) const;
	[[nodiscard]] int get_rotation_state() const;

	bool move_down();
	bool move_left();
	bool move_right();
	bool move(move_direction);
	bool rotate_clockwise();
	bool rotate_counterclockwise();

	[[nodiscard]] trtr::piece_layout get_ghost_layout() const;

private:
	[[nodiscard]] static int get_next_rotation_state(int rotation_state);
	[[nodiscard]] static int get_previous_rotation_state(int rotation_state);
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset(int rotation_state, int phase) const;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset(int rotation_state, int phase) const;
	
	const trtr::board& m_board;
	trtr::coords m_global_positon = {starting_x_coord, starting_y_coord};
	int m_rotation_state = 0; // 0 - 3
	[[nodiscard]] bool check_if_valid_positions(const trtr::piece_layout&) const;

protected:
	[[nodiscard]] piece_layout get_local_layout(int rotation_state) const;
	[[nodiscard]] virtual piece_layout get_layout_0() const = 0;
	[[nodiscard]] virtual piece_layout get_layout_1() const = 0;
	[[nodiscard]] virtual piece_layout get_layout_2() const = 0;
	[[nodiscard]] virtual piece_layout get_layout_3() const = 0;
	[[nodiscard]] virtual trtr::coords get_clockwise_rotation_offset_0 (int rotation_state) const = 0;
	[[nodiscard]] virtual trtr::coords get_clockwise_rotation_offset_1 (int rotation_state) const = 0;
	[[nodiscard]] virtual trtr::coords get_clockwise_rotation_offset_2 (int rotation_state) const = 0;
	[[nodiscard]] virtual trtr::coords get_clockwise_rotation_offset_3 (int rotation_state) const = 0;
	[[nodiscard]] virtual trtr::coords get_counterclockwise_rotation_offset_0 (int rotation_state) const = 0;
	[[nodiscard]] virtual trtr::coords get_counterclockwise_rotation_offset_1 (int rotation_state) const = 0;
	[[nodiscard]] virtual trtr::coords get_counterclockwise_rotation_offset_2 (int rotation_state) const = 0;
	[[nodiscard]] virtual trtr::coords get_counterclockwise_rotation_offset_3 (int rotation_state) const = 0;
};



class i_piece : public piece
{
public:
	using piece::piece;
	[[nodiscard]] trtr::block_type get_block_type() const override;
	[[nodiscard]] trtr::piece_type get_piece_type() const override;
	~i_piece() = default;
private:
	[[nodiscard]] piece_layout get_layout_0() const override;
	[[nodiscard]] piece_layout get_layout_1() const override;
	[[nodiscard]] piece_layout get_layout_2() const override;
	[[nodiscard]] piece_layout get_layout_3() const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_3 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_3 (int rotation_state) const override;
};

class j_piece : public piece
{
public:
	using piece::piece;
	[[nodiscard]] trtr::block_type get_block_type() const override;
	[[nodiscard]] trtr::piece_type get_piece_type() const override;
private:
	[[nodiscard]] piece_layout get_layout_0() const override;
	[[nodiscard]] piece_layout get_layout_1() const override;
	[[nodiscard]] piece_layout get_layout_2() const override;
	[[nodiscard]] piece_layout get_layout_3() const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_3 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_3 (int rotation_state) const override;
};

class l_piece : public piece
{
public:
	using piece::piece;
	[[nodiscard]] trtr::block_type get_block_type() const override;
	[[nodiscard]] trtr::piece_type get_piece_type() const override;
private:
	[[nodiscard]] piece_layout get_layout_0() const override;
	[[nodiscard]] piece_layout get_layout_1() const override;
	[[nodiscard]] piece_layout get_layout_2() const override;
	[[nodiscard]] piece_layout get_layout_3() const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_3 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_3 (int rotation_state) const override;
};

class o_piece : public piece
{
public:
	using piece::piece;
	[[nodiscard]] trtr::block_type get_block_type() const override;
	[[nodiscard]] trtr::piece_type get_piece_type() const override;
private:
	[[nodiscard]] piece_layout get_layout_0() const override;
	[[nodiscard]] piece_layout get_layout_1() const override;
	[[nodiscard]] piece_layout get_layout_2() const override;
	[[nodiscard]] piece_layout get_layout_3() const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_3 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_3 (int rotation_state) const override;
};

class s_piece : public piece
{
public:
	using piece::piece;
	[[nodiscard]] trtr::block_type get_block_type() const override;
	[[nodiscard]] trtr::piece_type get_piece_type() const override;
private:
	[[nodiscard]] piece_layout get_layout_0() const override;
	[[nodiscard]] piece_layout get_layout_1() const override;
	[[nodiscard]] piece_layout get_layout_2() const override;
	[[nodiscard]] piece_layout get_layout_3() const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_3 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_3 (int rotation_state) const override;
};

class t_piece : public piece
{
public:
	using piece::piece;
	[[nodiscard]] trtr::block_type get_block_type() const override;
	[[nodiscard]] trtr::piece_type get_piece_type() const override;
private:
	[[nodiscard]] piece_layout get_layout_0() const override;
	[[nodiscard]] piece_layout get_layout_1() const override;
	[[nodiscard]] piece_layout get_layout_2() const override;
	[[nodiscard]] piece_layout get_layout_3() const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_3 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_3 (int rotation_state) const override;
};

class z_piece : public piece
{
public:
	using piece::piece;
	[[nodiscard]] trtr::block_type get_block_type() const override;
	[[nodiscard]] trtr::piece_type get_piece_type() const override;
private:
	[[nodiscard]] piece_layout get_layout_0() const override;
	[[nodiscard]] piece_layout get_layout_1() const override;
	[[nodiscard]] piece_layout get_layout_2() const override;
	[[nodiscard]] piece_layout get_layout_3() const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_clockwise_rotation_offset_3 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_0 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_1 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_2 (int rotation_state) const override;
	[[nodiscard]] trtr::coords get_counterclockwise_rotation_offset_3 (int rotation_state) const override;
};

} // namespace trtr
