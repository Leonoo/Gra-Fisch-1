
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <list>
#include <random>
#include <memory>

#include "Character.h"
#include "Piranha.h"
#include "BlasenAttacke.h"

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(700, 500), "SFML Views");
	App.setVerticalSyncEnabled(true);

	 sf::Font font;
	 if (!font.loadFromFile("Ressourcen/DK_Crayon_Crumble.ttf"))
	 {
	 }

	sf::RectangleShape BackgroundShape;
	BackgroundShape.setFillColor(sf::Color::Green);
	BackgroundShape.setSize(sf::Vector2f(6000, 500));

	Character grafish;
	grafish.load();

    sf::Text Text("0", font);
    Text.move(10, 100);
    Text.setColor(sf::Color::White);

    sf::Vector2f ViewSize(700, 500);
    sf::View View(grafish.getPosition(), ViewSize);

	std::uniform_int_distribution<int> randomint(50,100);
	std::uniform_int_distribution<int> randomíntPira(100,400);
	std::uniform_int_distribution<int> randomIntOneTofour(1,4);
	std::default_random_engine randomEngine;
	std::default_random_engine randomEnginePira;
	std::default_random_engine randomEngineOneTofour;

	std::list<std::shared_ptr<sf::RectangleShape>> RectShapeList;
	std::list<std::shared_ptr<sf::RectangleShape>> RectShapeUntenList;

	for (int i = 0; i < 6000 / 50; i++)
	{
		std::shared_ptr<sf::RectangleShape> tempRectShape = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape());
		RectShapeList.push_back(tempRectShape);
		tempRectShape->setFillColor(sf::Color::Green);
		tempRectShape->setPosition(i*50, 0);
		tempRectShape->setSize(sf::Vector2f(50, randomint(randomEngine)));
	}

	for (int i = 0; i <= 6000 / 50; i++)
	{
		std::shared_ptr<sf::RectangleShape> tempRectShape = std::shared_ptr<sf::RectangleShape>(new sf::RectangleShape());
		RectShapeUntenList.push_back(tempRectShape);
		tempRectShape->setFillColor(sf::Color::Green);

		int random = randomint(randomEngine);

		tempRectShape->setPosition(i*50, 500 - random);
		tempRectShape->setSize(sf::Vector2f(50, random));
	}

	std::list<std::shared_ptr<Piranha>> PiranhaList;
	std::list<std::shared_ptr<Piranha>> dropPiranhaList;

	std::list<std::shared_ptr<BlasenAttacke>> blasenAttackeList;
	std::list<std::shared_ptr<BlasenAttacke>> dropBlasenAttackeList;

	sf::Clock clock;
	sf::Clock clock2;
	sf::Clock clock3;
	// Start game loop
	sf::Event Event;
    while (App.isOpen())
    {
		sf::Time elapsed = clock.restart();
		float Offset = 200.f * elapsed.asSeconds();
        
        while (App.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                App.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                App.close();
        }

		if (clock2.getElapsedTime().asSeconds() > 5.0)
		{
			sf::Time piraTime = clock3.getElapsedTime();

			for (auto item: blasenAttackeList)
			{
				item->update(elapsed);
			}

			grafish.update(elapsed);
			std::shared_ptr<BlasenAttacke> tempAttack = grafish.getAttack();
			if (tempAttack != nullptr)
			{
				blasenAttackeList.push_back(tempAttack);
			}

			for (auto item: PiranhaList)
			{
				item->update(elapsed);
			}

			if (piraTime.asSeconds() > 3.f)
			{
				for (int i = 0; i < randomIntOneTofour(randomEngineOneTofour); i++)
				{
					float xposi = View.getCenter().x - 350 <= 0 ? 0 : View.getCenter().x - 350;

					sf::Vector2f startPosition(xposi, randomíntPira(randomEngineOneTofour));
					std::shared_ptr<Piranha> tempPira(new Piranha());
					tempPira->load(startPosition);
					PiranhaList.push_back(tempPira);
				}
				clock3.restart();
			}

			for (auto item: PiranhaList)
			{
				if (item->collisionBlasenAttacke(blasenAttackeList))
				{
					dropPiranhaList.push_back(item);
				}
			}
			for (auto item: dropPiranhaList)
			{
				PiranhaList.remove(item);
			}
			dropPiranhaList.clear();

			View.setCenter(grafish.getPosition().x, 250.f);

			if (View.getCenter().x > 6000 - 250)
			{
				View.setCenter(6000 - 250, 250.f);
			}
		}

		
		App.clear();

		if (clock2.getElapsedTime().asSeconds() > 5.0)
		{
			App.setView(View);

			sf::IntRect viewRect = sf::IntRect(View.getCenter().x - (View.getSize().x / 2), View.getCenter().y - (View.getSize().y / 2), View.getSize().x, View.getSize().y); 

			for (auto item: RectShapeList)
			{
				auto itemRect = sf::IntRect(static_cast<sf::Vector2i>(item->getPosition()), static_cast<sf::Vector2i>(item->getSize()));

				if (viewRect.intersects(itemRect))
				{
					App.draw(*item);
				}
			}

			for (auto item: RectShapeUntenList)
			{
				auto itemRect = sf::IntRect(static_cast<sf::Vector2i>(item->getPosition()), static_cast<sf::Vector2i>(item->getSize()));

				if (viewRect.intersects(itemRect))
				{
					App.draw(*item);
				}
			}
		
			for (auto item: PiranhaList)
			{
				if (item->getPosition().x >= View.getCenter().x + 350)
				{
					dropPiranhaList.push_back(item);
				}
				else
				{
					App.draw(*item);
				}
			}
			for (auto item: dropPiranhaList)
			{
				PiranhaList.remove(item);
			}
			dropPiranhaList.clear();

			for (auto item: blasenAttackeList)
			{
				if (item->getPosition().x <= View.getCenter().x - 350)
				{
					dropBlasenAttackeList.push_back(item);
				}
				else
				{
					App.draw(*item);
				}
			}
			for (auto item: dropBlasenAttackeList)
			{
				blasenAttackeList.remove(item);
			}
			dropBlasenAttackeList.clear();

			App.draw(grafish);
			App.setView(App.getDefaultView());
		}
		else
		{
			std::stringstream str;

			str << clock2.getElapsedTime().asSeconds();
			Text.setString(str.str());
			App.setView(App.getDefaultView());
			App.draw(Text);
		}

        // Finally, display rendered frame on screen
        App.display();
    }

    return EXIT_SUCCESS;
}
