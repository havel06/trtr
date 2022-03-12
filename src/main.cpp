#include "window.h"
#include "board.h"
#include "game_loop.h"
#include "piece.h"

#include <SFML/Graphics.hpp>

int main()
{
	// TODO - better game over check
	// TODO - new block rendering (render full board at once)
	// TODO - text centering
	// TODO - adjustable window size
	// TODO - complete gui redesign
	// TODO - line clear delay (400-700ms)
	// TODO - stack above line 19
	// TODO - refactor main.cpp
	// TODO - unit tests for rotation

	trtr::window main_window;

	std::random_device rd;

	trtr::game_loop main_game_loop(main_window, rd());

    while (main_window.isOpen())
    {
        sf::Event event{};
        while (main_window.pollEvent(event))
        {
			switch (event.type)
			{
				case sf::Event::Closed:
					main_window.close();
					break;

				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						case sf::Keyboard::Q:
							main_window.close();
							break;

						case sf::Keyboard::Up:
							main_game_loop.rotate_clockwise();
							break;

						case sf::Keyboard::LControl:
							main_game_loop.rotate_counterclockwise();
							break;

						case sf::Keyboard::Right:
							main_game_loop.set_move_right();
							break;

						case sf::Keyboard::Left:
							main_game_loop.set_move_left();
							break;

						case sf::Keyboard::Space:
							main_game_loop.hard_drop();
							break;

						case sf::Keyboard::Down:
							main_game_loop.set_soft_drop(true);
							break;

						case sf::Keyboard::C:
							main_game_loop.hold_piece();
							break;

						default:
							break;
					}
					break;

				case sf::Event::KeyReleased:
					if (event.key.code == sf::Keyboard::Down)
					{
						main_game_loop.set_soft_drop(false);
					}
					break;

				default:
					break;
			}
        }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			main_game_loop.try_side_move();
		}

		main_game_loop.tick();

        main_window.clear();
		main_window.draw_piece();
		main_window.draw_board();
		main_window.draw_ghost();
		main_window.draw_outline();
		main_window.draw_score();
		main_window.draw_level_number();
		main_window.draw_preview();
		main_window.draw_hold();
        main_window.display();
    }

    return 0;
}
