#pragma once
#include <string>
#include "SharedContext.hpp"
#include <SFML/Graphics.hpp>
#include "NetworkClient.hpp"
#include <sstream>
struct PlayerData
{
	std::string _name{ "Default" };
	int _id{ 0 };
	int _xPos{ 0 }, _yPos{ 0 };
	PlayerData() {}
};

struct BallData
{
	int _xPos{ 0 }, _yPos{ 0 };
	BallData() {}
};

class Game
{

	PlayerData player1;
	PlayerData player2;
	std::string m_name{ "Defau" };
	int m_xPos;
	int m_yPos;
	int myPlayerID;
	sf::RenderWindow m_rWnd;
	sf::Time m_elapsed;
	sf::Clock m_updateTimer;
	std::string m_otherPlayerData;
	std::string m_currPlayerData;
	sf::RectangleShape m_pl1Rect;
	sf::RectangleShape m_pl2Rect;
	sf::RectangleShape* m_myRectShape{ nullptr };
	sf::RectangleShape* m_otherRectShape{ nullptr };
	int m_numPlayersConnected{ 0 };


public:
	SharedContext m_shrd;

	Game(NetworkClient& l_nc)
		: m_rWnd(sf::VideoMode{ 640U,480U,32U }, "Pon-Gline", sf::Style::Close | sf::Style::Titlebar)
		, m_shrd()
		, m_pl1Rect(), m_pl2Rect()
	{
		m_shrd.SetWindow(m_rWnd);
		m_shrd.SetNetworker(l_nc);
		m_elapsed = sf::Time::Zero;
		m_updateTimer.restart();
		m_otherPlayerData = m_shrd._nc->UpdateNetworkStuff();
		
		int otherID = std::stoi(m_otherPlayerData.substr(0, 1));
		
		if (otherID == 1)
		{
			myPlayerID = 2;
			UnpackData(1);
			PackData();

			m_myRectShape = &m_pl2Rect;
			m_otherRectShape = &m_pl1Rect;

		}
		else if (otherID == 2)
		{
			myPlayerID = 1;
			UnpackData(2);
			PackData();
			m_myRectShape = &m_pl1Rect;
			m_otherRectShape = &m_pl2Rect;


		}
		else
		{
			std::cout << std::endl << "Did not get one or two?";
		}

		m_pl1Rect.setPosition((float)player1._xPos, (float)player1._yPos);
		m_pl2Rect.setPosition((float)player2._xPos, (float)player2._yPos);
		m_pl1Rect.setFillColor(sf::Color::Red);
		m_pl2Rect.setFillColor(sf::Color::Red);
		m_pl1Rect.setSize({ 8.f, 32.f });
		m_pl2Rect.setSize({ 8.f, 32.f });

		Run();
	}

	~Game() {}

	void UnpackData(int l_playerID)
	{
		if (l_playerID == 1)
		{
		
			player1._id = std::stoi(m_otherPlayerData.substr(0,1));
			player1._name = m_otherPlayerData.substr(2, 1);
			player1._xPos = std::stoi(m_otherPlayerData.substr(3, 3));
			player1._yPos = std::stoi(m_otherPlayerData.substr(6, 3));


		}
		else if (l_playerID == 2)
		{
			player2._id = std::stoi(m_otherPlayerData.substr(0, 1));
			player2._name = m_otherPlayerData.substr(2, 1);
			player2._xPos = std::stoi(m_otherPlayerData.substr(3, 3));
			player2._yPos = std::stoi(m_otherPlayerData.substr(6, 3));
		}
	}

	void PackData()
	{
		if (myPlayerID == 1)
		{
			std::string xPosStr;
			std::string yPosStr;

			if (m_xPos < 10)
			{
				xPosStr = "00";
			}
			else if (m_xPos < 100)
			{
				xPosStr = "0";
			}
			else
			{
				xPosStr = "";
			}

			if (m_yPos < 10)
			{
				yPosStr = "00";
			}
			else if (m_yPos < 100)
			{
				yPosStr = "0";
			}
			else
			{
				yPosStr = "";
			}
			std::stringstream ss;
			ss << "11" << m_name << xPosStr << std::to_string(m_xPos) << yPosStr << std::to_string(m_yPos);
			m_currPlayerData = ss.str();
		}
		else if (myPlayerID == 2)
		{
			std::string xPosStr;
			std::string yPosStr;

			if (m_xPos < 10)
			{
				xPosStr = "00";
			}
			else if (m_xPos < 100)
			{
				xPosStr = "0";
			}
			else
			{
				xPosStr = "";
			}

			if (m_yPos < 10)
			{
				yPosStr = "00";
			}
			else if (m_yPos < 100)
			{
				yPosStr = "0";
			}
			else
			{
				yPosStr = "";
			}
			std::stringstream ss;
			ss << "21" << m_name << xPosStr << std::to_string(m_xPos) << yPosStr << std::to_string(m_yPos);
			m_currPlayerData = ss.str();
		}
	}

	void Update(float gameTime)
	{

	}

	void Draw()
	{
		m_rWnd.clear(sf::Color(47, 147, 247, 255));

		// render here
		m_rWnd.draw(m_pl1Rect);
		m_rWnd.draw(m_pl2Rect);

		m_rWnd.display();
	}

	void ProcessInput()
	{

	}

	void UpdateNetworkStuff() 
	{
		// if (m_numPlayersConnected == 2)
		m_otherPlayerData = m_shrd._nc->UpdateNetworkStuff();
	}

	void BackupCurrFrame()
	{

	}


	void Run()
	{

		while (m_rWnd.isOpen())
		{
			ProcessInput();
			this->UpdateNetworkStuff();

			m_elapsed += m_updateTimer.restart();
			if (m_elapsed > sf::seconds(1.0f / 60.0f))
			{
				m_elapsed = sf::Time::Zero;
				Update(1.0f / 60.f);
				Draw();
			}

			sf::Event e;
			while (m_rWnd.pollEvent(e))
			{
				switch (e.type)
				{
				case sf::Event::Closed:
					m_rWnd.close();
					break;
				case sf::Event::KeyReleased:
					if (e.key.code == sf::Keyboard::Escape)
					{
						m_rWnd.close();
					}
					break;
				default:
					break;
				}
			}
			
			
			BackupCurrFrame();

		}
	}


	
};

