#pragma once

#include <array>
#include <random>

namespace trtr
{
	enum class piece_type {i = 0, o = 1, t = 2, s = 3, z = 4, j = 5, l = 6, none = 7};
	constexpr static const size_t bag_size = 7;

	class random_generator
	{
		public:
			explicit random_generator(unsigned int seed);
			~random_generator() = default;
			random_generator(const random_generator&) = delete;
			random_generator(random_generator&&) = delete;
			random_generator& operator=(const random_generator&) = delete;
			random_generator& operator=(random_generator&&) = delete;

			piece_type get();
		private:
			void new_bag();

			std::array<piece_type, bag_size> m_current_bag = {
				piece_type::i,
				piece_type::o,
				piece_type::t,
				piece_type::s,
				piece_type::z,
				piece_type::j,
				piece_type::l
			};
			std::array<piece_type, bag_size>::iterator m_current_piece = nullptr;
			std::mt19937 m_random_engine;
	};
} // namespace trtr
