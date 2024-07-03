#pragma once


#include "Entity.h"
#include "EntityManager.h"
#include "Vec2.h"

#include <SFML/Graphics.hpp>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, SL, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };




class Game
{
	sf::RenderWindow   m_window;
	EntityManager      m_entities;
	sf::Font           m_font;
	sf::Text           m_text;              // to draw score 
	sf::Text           m_text_death;
	sf::Text           m_text_specialBullet;
	PlayerConfig       m_playerConfig;
	EnemyConfig        m_enemyConfig;
	BulletConfig       m_bulletConfig;
	int                m_specialBullet = 0;
	int                m_score = 0;
	int				   m_death = 0;
	int                m_currentFrame = 1;
	int                m_lastEnemySpawnTime = 0;
	bool               m_pause = false;     // where we update game login 
	bool               m_running = true;    // is game is running 
											
	std::shared_ptr<Entity> m_player;       // storeing pointer to the player

	void init(const std::string& config);   // initialize game states with config file path
	void setPaused();            // paused the game

	void sMovement();                       // System : Entity position / movement update 
	void sUserInput();                      // System : User Input 
	void sLifespan();                       // System : Lifesapn
	void sRender();                         // System : Render / Drawing 
	void sEnemySpawner();					// System : Spawn Enemies
	void sCollision();                      // System : collision


	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity);
	void bounceEntity(std::shared_ptr<Entity> entity);


public:

	Game(const std::string& config); // Constructor , take in game config

	void run();	

};