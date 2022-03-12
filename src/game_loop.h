#include "board.h"
#include "piece.h"
#include "piece_preview.h"
#include "random_generator.h"
#include "window.h"

#include <SFML/System/Clock.hpp>

#include <memory>

namespace trtr
{
	class game_loop
	{
		public:
			game_loop(trtr::window&, unsigned int seed);
			~game_loop();

			void tick();
			void rotate_clockwise();
			void rotate_counterclockwise();
			void set_move_right();
			void set_move_left();
			void set_move_none();
			void hard_drop();
			void set_soft_drop(bool);
			void try_side_move();
			void hold_piece();
			[[nodiscard]] const trtr::piece& get_piece() const;
		private:
			void new_piece(trtr::piece_type);
			void land_piece();
			void calculate_score(unsigned int rows_cleared);
			void update_level();
			sf::Time get_piece_fall_time() const;

			trtr::random_generator m_random_generator;
			trtr::piece_preview m_piece_preview;
			trtr::board m_board{};
			trtr::window& m_window;
			std::unique_ptr<trtr::piece> m_piece;
			sf::Clock m_piece_fall_clock{};
			sf::Clock m_lock_delay_clock{};
			sf::Clock m_fast_side_move_clock{}; // how long to hold until fast movement starts
			sf::Clock m_minmal_side_move_clock{}; // minimal time to move one block to the side

			unsigned int m_level = 1;
			unsigned int m_rows_cleared = 0;
			unsigned int m_score = 0;
			bool m_soft_drop = false;
			move_direction m_desired_direction = move_direction::none;
			trtr::piece_type m_held_piece = trtr::piece_type::none;
			bool m_hold_available = true;
	};

} // namespace trtr
