#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

int main()
{
  float width = sf::VideoMode::getDesktopMode().width;
	float height = sf::VideoMode::getDesktopMode().height;
	View mainView(FloatRect(0.0f,0.0f,width, height));
	//width = 800; height = 600;
	// Create a video mode object
	VideoMode vm(width, height);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	Font f;
	if (!f.loadFromFile("./fonts/KOMIKAP_.ttf")) cout << "failed to load font..." << endl;
	Text instructions;
	instructions.setFont(f);
	instructions.setCharacterSize(24);
	instructions.setFillColor(Color::Green);

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the right button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
					if(vertices.size() <= 3)
					{
						vertices.push_back(Vector2f{(float)event.mouseButton.x, (float)event.mouseButton.y}));
					}
					else
					{
						points.push_back(Vector2f{(float)event.mouseButton.x, float(event.mouseButton.y}));
					}

					// get the current mouse position in the window
					sf::Vector2i pixelPos = sf::Mouse::getPosition(window);

					// convert it to world coordinates
					sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos, mainView);
					vertices.push_back(worldPos);
				}
			}

		}
		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*****************************************
			Update the scene
		*****************************************/
		//generate interior points

		ostringstream oss;
		oss << "Click three times to draw a triangle " << endl << "Click again to start the program.";
		instructions.setString(oss.str());

		FloatRect textRect = instructions.getLocalBounds();
		instructions.setOrigin(textRect.left +
			textRect.width / 2.0f,
			textRect.top +
			textRect.height / 2.0f);

		instructions.setPosition(width / 2, 50);

		/*
		****************************************
		Draw the scene
		****************************************
		*/
		// Clear everything from the last run frame
		window.clear();
		// Draw our game scene here
		//RectangleShape r{ Vector2f{4,4} }; ///width, height.  Center uninitialized
		window.setView(mainView);
		CircleShape r(2);
		r.setFillColor(Color::Magenta);
		for (size_t i = 0; i < vertices.size(); i++)
		{
			r.setPosition(Vector2f{ vertices.at(i).x, vertices.at(i).y });
			window.draw(r);
		}
		window.draw(instructions);
		// Show everything we just drew
		window.display();
	}

}
