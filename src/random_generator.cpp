#include "random_generator.h"
#include <algorithm>

trtr::random_generator::random_generator(unsigned int t_seed) : m_random_engine{t_seed}
{
	new_bag();
}


trtr::piece_type trtr::random_generator::get()
{
	if (m_current_piece == m_current_bag.end())
	{
		new_bag();
	}

	return *(m_current_piece++);
}


void trtr::random_generator::new_bag()
{
	std::shuffle(m_current_bag.begin(), m_current_bag.end(), m_random_engine);
	m_current_piece = m_current_bag.begin();
}
