#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "Board.h"
#include "MineSweeper.h"

namespace MineSweeper
{
	std::vector<Point*> availablePointsStore;
	Board* board;

	std::unordered_map<GameDifficulty, MineSweeperConfig> mineSweeperConfigMap =
	{
		{ GameDifficulty::Easy, {8, 8, 10, 256, 256} },
		{ GameDifficulty::Medium, {16, 16, 40, 512, 512} },
		{ GameDifficulty::Hard, {30, 16, 99, 512, 960} }
	};

	MineSweeperConfig GetConfig(GameDifficulty difficulty)
	{
		return mineSweeperConfigMap[difficulty];
	}

	// Store all the points on container, this container is used later to generate random mines positions.
	void InitializeAvailablePointsContainer()
	{
		for (uint32 row = 0; row < board->GetRows(); ++row)
		{
			for (uint32 col = 0; col < board->GetColums(); ++col)
			{
				Point* point = new Point(row, col);
				board->AddPoint(point);
				availablePointsStore.push_back(point);
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
	void InitializeMinesPositions()
	{
		for (uint8 i = 0; i < board->GetTotalMines(); ++i)
		{
			auto itr = availablePointsStore.begin();
			std::advance(itr, std::rand() % availablePointsStore.size());

			Point* mine = *itr;
			mine->IsMine = true;
			board->CalcNearPointsFromMine(mine);

			availablePointsStore.erase(itr);
		}
	}

	// Random seed
	inline void InitializeRandom()
	{
		unsigned int uTimeNow = unsigned int(std::time(0));
		std::srand(uTimeNow);
	}

	// Initialize the board based on difficulty.
	void SetBoardSizeByDifficulty(GameDifficulty difficulty)
	{
		board = new Board(difficulty);
	}

	bool IsValidDifficulty(int difficulty)
	{
		return difficulty >= uint8(GameDifficulty::Easy) && difficulty <= uint8(GameDifficulty::Hard);
	}

	int ConvertCharToInt(char ch)
	{
		return ch - '0';
	}

	void AskUserForDifficulty()
	{
		std::cout << "Select difficulty" << std::endl
			<< "0 - Easy: 8 rows, 8 columns, 10 mines." << std::endl
			<< "1 - Medium: 16 rows, 16 columns, 40 mines." << std::endl
			<< "2 - Hard: 30 rows, 16 columns, 99 mines." << std::endl;

		std::string difficultyInput; std::cin >> difficultyInput; // We assume a string is given.

		int difficulty = ConvertCharToInt(difficultyInput[0]);

		if (difficultyInput.size() != 1 || !IsValidDifficulty(difficulty))
		{
			system("cls");
			AskUserForDifficulty();
			return;
		}

		SetBoardSizeByDifficulty(GameDifficulty(difficulty));
	}

	void InitializeRandomMines()
	{
		InitializeAvailablePointsContainer();
		InitializeMinesPositions();
	}

	void InitializeGame()
	{
		system("cls");

		delete board;

		board = nullptr;
		availablePointsStore.clear();

		InitializeRandom();
		AskUserForDifficulty();
		InitializeRandomMines();
	}

	void PlayGame()
	{
		InitializeGame();

		MineSweeperConfig config = mineSweeperConfigMap[board->GetDifficulty()];

		sf::RenderWindow window(sf::VideoMode(config.Width, config.Height), "Mine Sweeper");
		sf::Texture texture;
		texture.loadFromFile("tiles.jpg");
		sf::Sprite sprite(texture);
		board->Update(window, sprite);

		while (window.isOpen())
		{
			sf::Event e;
			while (window.waitEvent(e))
			{
				if (board->GetGameState() != GameState::Playing)
				{
					window.close();
					break;
				}

				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				int x = mousePos.x / 32;
				int y = mousePos.y / 32;

				switch (e.type)
				{
					case sf::Event::Closed:
						window.close();
						break;

					case sf::Event::MouseButtonPressed:
					{
						Point* point = board->GetPoint(y, x);
						switch (e.key.code)
						{
							case sf::Mouse::Left:
								board->DiscoverPoint(point);
								board->Update(window, sprite);
								break;

							case sf::Mouse::Right:
								if (point->IsDiscovered)
									break;

								point->SetOrUndoFlag();
								board->Update(window, sprite);

								break;
						}
					}
				}
			}
		}
		PlayGame();
	}
}
