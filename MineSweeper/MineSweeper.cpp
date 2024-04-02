#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Board.h"
#include "MineSweeper.h"

namespace MineSweeper
{
	MineSweeperConfig const& GetConfig(GameDifficulty const& difficulty)
	{
		// Change with config file instead of hardcoding here.
		std::unordered_map<GameDifficulty, MineSweeperConfig> mineSweeperConfigMap =
		{
			{ GameDifficulty::Easy,		{8,   8, 10, 256, 256} },
			{ GameDifficulty::Medium,	{16, 16, 40, 512, 512} },
			{ GameDifficulty::Hard,		{30, 16, 99, 512, 960} }
		};

		return mineSweeperConfigMap[difficulty];
	}

	// Store all the points on container, this container is used later to generate random mines positions.
	void InitializeAvailablePointsContainer(std::vector<Point*>& availablePoints)
	{
		for (uint32 row = 0; row < sBoard->GetRows(); ++row)
		{
			for (uint32 col = 0; col < sBoard->GetColums(); ++col)
			{
				Point* point = new Point(row, col);
				sBoard->AddPoint(point);
				availablePoints.push_back(point);
			}
		}	
	}

#if _DEBUG
	void ShowAvailablePoints()
	{
		for (auto itr = sAvailablePointsStore.begin(); itr != sAvailablePointsStore.end(); ++itr)
			(*itr)->ToString();
	}
#endif

	// Random mine positions generator
	void InitializeMinesPositions(std::vector<Point*>& availablePoints)
	{
		// Total mines to be generated on the map.
		for (uint8 i = 0; i < sBoard->GetTotalMines(); ++i)
		{
			auto itr = availablePoints.begin();
			// Gets a random iterator from the available points.
			std::advance(itr, std::rand() % availablePoints.size());

			// Now convert this iterator pointer to a mine.
			Point* mine = *itr;
			mine->IsMine = true;
			sBoard->CalcNearPointsFromMine(mine);

			// We will never use this iterator again so lets drop it from the available points.
			availablePoints.erase(itr);
		}
	}

	// Random seed
	inline void InitializeRandom()
	{
		unsigned int uTimeNow = unsigned int(std::time(0));
		std::srand(uTimeNow);
	}

	bool const IsValidDifficulty(int const& difficulty)
	{
		return difficulty >= uint8(GameDifficulty::Easy) && difficulty <= uint8(GameDifficulty::Hard);
	}

	void AskUserForDifficulty()
	{
		std::cout << "Select difficulty" << std::endl
			<< "0 - Easy: 8 rows, 8 columns, 10 mines." << std::endl
			<< "1 - Medium: 16 rows, 16 columns, 40 mines." << std::endl
			<< "2 - Hard: 30 rows, 16 columns, 99 mines." << std::endl;

		// We assume a string is given.
		std::string difficultyInput; std::cin >> difficultyInput; 

		// Convert the first char of the input to a number.
		int const difficulty = int(difficultyInput[0] - '0');

		if (difficultyInput.size() != 1 || !IsValidDifficulty(difficulty))
		{
			system("cls");
			AskUserForDifficulty();
			return;
		}

		sBoard->InitializeBoard(GameDifficulty(difficulty));
	}

	void InitializeRandomMines()
	{
		std::vector<Point*> availablePoints;
		InitializeAvailablePointsContainer(availablePoints);
		InitializeMinesPositions(availablePoints);
	}

	void InitializeGame()
	{
		system("cls");

		sBoard->Clean();
		InitializeRandom();
		AskUserForDifficulty();
		InitializeRandomMines();
	}

	void PlayGame()
	{
		InitializeGame();

		MineSweeperConfig const& config = GetConfig(sBoard->GetDifficulty());

		sf::RenderWindow window(sf::VideoMode(config.BoardWidth, config.BoardHeight), "Mine Sweeper");
		sf::Texture texture;
		texture.loadFromFile("tiles.jpg");
		sf::Sprite sprite(texture);
		sBoard->Update(window, sprite);

		while (window.isOpen())
		{
			if (sBoard->GetGameState() != GameState::Playing)
			{
				window.close();
				break;
			}

			sf::Event event;
			while (window.waitEvent(event))
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				int x = mousePos.x / 32;
				int y = mousePos.y / 32;

				switch (event.type)
				{
					case sf::Event::Closed:
						window.close();
						break;

					case sf::Event::MouseButtonPressed:
					{
						Point* point = sBoard->GetPoint(y, x);
						switch (event.key.code)
						{
							case sf::Mouse::Left:
								sBoard->DiscoverPoint(point);
								sBoard->Update(window, sprite);
								break;

							case sf::Mouse::Right:
								if (point->IsDiscovered)
									break;

								point->SetOrUndoFlag();
								sBoard->Update(window, sprite);

								break;
						}
					}
				}
			}
		}
		PlayGame();
	}
}
