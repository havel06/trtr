#pragma once

#include "random_generator.h"

namespace trtr
{
	constexpr inline const std::size_t preview_count = 5;

	class piece_preview
	{
		public:
			explicit piece_preview(trtr::random_generator& generator);
			[[nodiscard]] trtr::piece_type cycle();
			[[nodiscard]] trtr::piece_type get(unsigned int) const;
		private:
			std::array<trtr::piece_type, preview_count> m_contents{};
			trtr::random_generator& m_generator;
	};

} // namespace trtr
