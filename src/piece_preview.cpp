#include "piece_preview.h"
#include <stdexcept>

trtr::piece_preview::piece_preview(trtr::random_generator& t_generator) : m_generator(t_generator)
{
	for (auto& piece : m_contents)
	{
		piece = m_generator.get();
	}
}

trtr::piece_type trtr::piece_preview::cycle()
{
	trtr::piece_type front = m_contents.front();

	for (auto* i = m_contents.begin(); i != m_contents.end() - 1; ++i)
	{
		*i = *std::next(i);
	}

	m_contents.back() = m_generator.get();

	return front;
}




trtr::piece_type trtr::piece_preview::get(unsigned int t_index) const
{
	return m_contents.at(t_index);
}
