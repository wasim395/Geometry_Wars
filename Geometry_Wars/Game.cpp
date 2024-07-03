#include "Game.h" 
#include "Vec2.h"

#include <fstream>
#include <cstdlib> 
#include <time.h>
#include <iostream> 
#include <string> 
#include <cmath>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& config) 
{
   
    std::ifstream fin(config); // Use the provided config file path
    if (!fin.is_open()) 
    {
        std::cerr << "Failed to load the file: " << config << std::endl;
        return;
    }

    std::cout << config << "   is open \n";

    float window_width = 800.0f, window_height = 600.0f, window_frameRate = 60.0f;
    bool isFullWindow = false;

    std::string temp;
    while (fin >> temp) 
    {
        std::cout << temp << "\n";
        if (temp == "Window") 
        {
            fin >> window_width >> window_height >> window_frameRate >> isFullWindow;
        }
        else if (temp == "Font") 
        {
            std::string tempFontFile;
            float tempFontSize, FR, FG, FB;
            fin >> tempFontFile >> tempFontSize >> FR >> FG >> FB;

            if (!m_font.loadFromFile(tempFontFile)) 
            {
                std::cerr << "Failed to load font file: " << tempFontFile << std::endl;
                continue; // Continue to next iteration or handle failure
            }

            m_text.setFont(m_font);
            m_text.setCharacterSize(static_cast<unsigned int>(tempFontSize));
            m_text.setFillColor(sf::Color(static_cast<sf::Uint8>(FR), static_cast<sf::Uint8>(FG), static_cast<sf::Uint8>(FB)));
            m_text.setPosition(10, 10);
            m_text.setString("SCORE " + std::to_string(0));

            m_text_death.setFont(m_font);
            m_text_death.setCharacterSize(static_cast<unsigned int>(tempFontSize));
            m_text_death.setFillColor(sf::Color(static_cast<sf::Uint8>(FR), static_cast<sf::Uint8>(FG), static_cast<sf::Uint8>(FB)));
            m_text_death.setPosition(10, 39);
            m_text_death.setString("DEATH " + std::to_string(0));

            m_text_specialBullet.setFont(m_font);
            m_text_specialBullet.setCharacterSize(static_cast<unsigned int>(tempFontSize));
            m_text_specialBullet.setFillColor(sf::Color(static_cast<sf::Uint8>(FR), static_cast<sf::Uint8>(FG), static_cast<sf::Uint8>(FB)));
            m_text_specialBullet.setPosition(10, 68);
            m_text_specialBullet.setString("SPECIAL WEAPON " + std::to_string(0));

        }
        else if (temp == "Player") 
        {
            fin >> m_playerConfig.SR >> m_playerConfig.CR >> m_playerConfig.S
                >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB
                >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB
                >> m_playerConfig.OT >> m_playerConfig.V;
        }
        else if (temp == "Enemy") 
        {
            fin >> m_enemyConfig.SR >> m_enemyConfig.CR >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX
                >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB
                >> m_enemyConfig.OT >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX
                >> m_enemyConfig.SL >> m_enemyConfig.SI;
        }
        else if (temp == "Bullet") 
        {
            fin >> m_bulletConfig.SR >> m_bulletConfig.CR >> m_bulletConfig.S
                >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB
                >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB
                >> m_bulletConfig.OT >> m_bulletConfig.V >> m_bulletConfig.L;
        }
    }

    m_window.create(sf::VideoMode(static_cast<int>(window_width), static_cast<int>(window_height)), "Geometry Wars");
    m_window.setFramerateLimit(static_cast<unsigned int>(window_frameRate));

    spawnPlayer();
}



void Game::run()
{

	//m_entities.update();
	//sMovement();
	//sUserInput();
	//sEnemySpawner();
	//sCollision();
	//m_currentFrame++;
	
    while (m_running)
    {
        m_entities.update();
        sMovement();
        sUserInput();
        sEnemySpawner();
        sCollision();
        sLifespan();
        sRender();
        m_currentFrame++;
    }
}


void Game::setPaused(bool paused)
{
	m_pause = paused;
}

void Game::spawnPlayer()
{
	auto entity = m_entities.addEntity("player");

	float mid_window_x = m_window.getSize().x/(float)2;
	float mid_window_y = m_window.getSize().y/(float)2;

	entity->cTransform = std::make_shared<CTransform>( Vec2(mid_window_x, mid_window_y), Vec2(0.f, 0.f), 0.f);
   
    entity->cShape = std::make_shared<CShape>(
        m_playerConfig.SR,
        m_playerConfig.V,
        sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB),
        sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB),
        m_playerConfig.OT
    );

    entity->cScore = std::make_shared<CScore>(0);
    //std::cout << entity->cScore->score << std::endl;

    m_player = entity;
}


//sapwnEnmey
void Game::spawnEnemy()
{
    //m_entities in entityManager is entityVec and m_entities in entities in  Game is enetityManager 
    //here m_entities is entityManger so we can use addEntity 
    auto entity = m_entities.addEntity("enemy");
    
    //srand(time(nullptr));

    int px = (rand() % (m_window.getSize().x - 2 * m_enemyConfig.SR)) + m_enemyConfig.SR;
    int py = (rand() % (m_window.getSize().y - 2 * m_enemyConfig.SR)) + m_enemyConfig.SR;

    float vx = (((float)(rand()) / RAND_MAX) * (m_enemyConfig.VMAX - m_enemyConfig.VMIN)) + m_enemyConfig.VMIN;
    float vy = (((float)(rand()) / RAND_MAX) * (m_enemyConfig.VMAX - m_enemyConfig.VMIN)) + m_enemyConfig.VMIN;

    //std::cout << " velociy -> " << vx << " " << vy << "\n";
    //std::cout << "position of enemey " << px << "  " << py << "\n";

    entity->cTransform = std::make_shared<CTransform>(Vec2(px , py), Vec2(vx , vy), 0.f);

    int V = (rand() % (m_enemyConfig.VMAX - m_enemyConfig.VMIN)) + m_enemyConfig.VMIN;

    int FR = rand() % 255;
    int FG = rand() % 255;
    int FB = rand() % 255;

    entity->cShape = std::make_shared<CShape>(
        m_enemyConfig.SR,
        V ,
        sf::Color(FR , FG , FB ),
        sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
        m_enemyConfig.OT
    );

    //std::cout << "enemey spawned \n";

}

//spawnSmalEnemy 
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    int vertices = e->cShape->circle.getPointCount();
    int radius   = e->cShape->circle.getRadius();

    int px       = e->cTransform->pos.x;
    int py       = e->cTransform->pos.y;

    float angle = 2 * (3.14f)/vertices ;
    float speed = sqrt((e->cTransform->velocity.x * e->cTransform->velocity.x) + (e->cTransform->velocity.y * e->cTransform->velocity.y));

    for (int i = 0; i < vertices; i++)
    {
        auto se = m_entities.addEntity("smallEnemy");
        
        float vx = cos(i * angle) * speed;
        float vy = sin(i * angle) * speed;

        se->cTransform = std::make_shared<CTransform>(Vec2(px, py), Vec2(vx/2 , vy/2), 0.0f);

        int FR = e->cShape->circle.getFillColor().r;
        int FG = e->cShape->circle.getFillColor().g;
        int FB = e->cShape->circle.getFillColor().b;

        se->cShape = std::make_shared<CShape>(
            m_enemyConfig.SR / 2,
            vertices,
            sf::Color(FR, FG, FB ),
            sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
            m_enemyConfig.OT
        );

        se->cLifespan->total = m_enemyConfig.SL;
        se->cLifespan->remaining = m_enemyConfig.SL;

    }

}

//spawn bullets 
void Game::spawnBullet(std::shared_ptr<Entity> e, const Vec2& mousePos)
{

    auto entity = m_entities.addEntity("bullet");

    //postion
    
    //player postion 
    int px = m_player->cTransform->pos.x;
    int py = m_player->cTransform->pos.y;

    //direct of bullet 
    int mx = mousePos.x;
    int my = mousePos.y;
     
    //velocity
    float vx = ((mx - px) / m_player->cTransform->pos.dist(Vec2(mx, my))) * m_bulletConfig.S;
    float vy = ((my - py) / m_player->cTransform->pos.dist(Vec2(mx, my))) * m_bulletConfig.S;

    //bullet postion 
    int bpx = px + ((mx - px) / m_player->cTransform->pos.dist(Vec2(mx, my))) * m_bulletConfig.SR;
    int bpy = py + ((my - py) / m_player->cTransform->pos.dist(Vec2(mx, my))) * m_bulletConfig.SR;

    //shape 
    entity->cTransform = std::make_shared<CTransform>(Vec2(bpx, bpy), Vec2(vx, vy), 0.0f);

    entity->cShape = std::make_shared<CShape>(
        m_bulletConfig.SR,
        m_bulletConfig.V,
        sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
        sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
        m_bulletConfig.OT
    );

    entity->cLifespan->total     = m_bulletConfig.L;
    entity->cLifespan->remaining = m_bulletConfig.L;

}

void Game::bounceEntity(std::shared_ptr<Entity> e)
{
    int x = e->cTransform->pos.x;
    int y = e->cTransform->pos.y;
    int r = e->cShape->circle.getRadius();

    //up bound
    if (y - r <= 0 || y + r >= m_window.getSize().y)
        e->cTransform->velocity.y *= -1;
    if (x - r <= 0 || x + r >= m_window.getSize().x)
        e->cTransform->velocity.x *= -1;
}

//spawn specialbullet
void Game::spawnSpecialWeapon(std::shared_ptr<Entity> e)
{

    if (m_specialBullet <= 0) return;
    m_specialBullet--;

    int vertices = e->cShape->circle.getPointCount();
    int radius = e->cShape->circle.getRadius();

    int px = e->cTransform->pos.x;
    int py = e->cTransform->pos.y;

    float angle = 2 * (3.14f) / vertices;
    float speed = m_bulletConfig.S;

    for (int i = 0; i < vertices; i++)
    {
        auto se = m_entities.addEntity("bullet");

        float vx = cos(i * angle) * speed;
        float vy = sin(i * angle) * speed;

        se->cTransform = std::make_shared<CTransform>(Vec2(px, py), Vec2(vx / 2, vy / 2), 0.0f);

        int FR = e->cShape->circle.getFillColor().r;
        int FG = e->cShape->circle.getFillColor().g;
        int FB = e->cShape->circle.getFillColor().b;

        se->cShape = std::make_shared<CShape>(
            m_enemyConfig.SR / 2,
            vertices,
            sf::Color(FR, FG, FB),
            sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB),
            m_playerConfig.OT/2
        );

        se->cLifespan->total = m_bulletConfig.L;
        se->cLifespan->remaining = m_bulletConfig.L;

    }


}

//system moments
void Game::sMovement()
{
    //updating player postion
    int xl = m_player->cTransform->pos.x - m_player->cShape->circle.getRadius();
    int xr = m_player->cTransform->pos.x + m_player->cShape->circle.getRadius();

    int yu = m_player->cTransform->pos.y - m_player->cShape->circle.getRadius();
    int yd = m_player->cTransform->pos.y + m_player->cShape->circle.getRadius();

    if (m_player->cInput->up && yu - m_playerConfig.S >= 0 )
    {
        m_player->cTransform->pos.y -= m_playerConfig.S;
    }

    if (m_player->cInput->down && yd + m_playerConfig.S <= m_window.getSize().y)
    {
        m_player->cTransform->pos.y += m_playerConfig.S;
    }
    
    if (m_player->cInput->left && xl - m_playerConfig.S >= 0)
    {
        m_player->cTransform->pos.x -= m_playerConfig.S;
    }

    if (m_player->cInput->right && (xr + m_playerConfig.S) <= m_window.getSize().x)
    {
        m_player->cTransform->pos.x += m_playerConfig.S;
    }
    
    //enemy Moment 
    std::string enemy = "enemy";
    for( auto &e : m_entities.getEntities(enemy))
    {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
        bounceEntity(e);
    }

    //small enemy
    std::string smallEnemy = "smallEnemy";
    for (auto& e : m_entities.getEntities(smallEnemy))
    {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
    }

    //bullet Moment 
    std::string bullet = "bullet";
    for (auto& e : m_entities.getEntities(bullet))
    {
        e->cTransform->pos.x += e->cTransform->velocity.x;
        e->cTransform->pos.y += e->cTransform->velocity.y;
        bounceEntity(e);
    }


}

//collision system 
void Game::sCollision()
{
    //bullet -- enemy
    std::string bullet = "bullet", enemy = "enemy";
    for (auto& b : m_entities.getEntities(bullet))
    {
        for (auto& e : m_entities.getEntities(enemy))
        {
            //check collision and distroy both 
            int rb = b->cShape->circle.getRadius();
            int re = e->cShape->circle.getRadius();
            //int rb = b->cCollision->radius ;
            //int re = e->cCollision->radius ;

            if (b->cTransform->pos.dist(e->cTransform->pos) <= rb + re)
            {
                spawnSmallEnemies(e);
                m_score += 100 * e->cShape->circle.getPointCount();
                std::cout << m_player->cScore->score << std::endl;
                e->destroy();
                b->destroy();
                
                m_text.setString("SCORE " + std::to_string(m_score));
            }
        }
    }

    //player - enemy
    for (auto& e : m_entities.getEntities(enemy))
    {
        //check collision and distroy both 
        int rp = m_player->cShape->circle.getRadius();
        int re = e->cShape->circle.getRadius();
        //int rb = b->cCollision->radius ;
        //int re = e->cCollision->radius ;

        if (m_player->cTransform->pos.dist(e->cTransform->pos) <= rp + re)
        {
            e->destroy();
            m_player->destroy();
            spawnPlayer();
            m_death++;
            m_specialBullet = 0;
            break;
        }
    }
}

//lifespan
void Game::sLifespan()
{
    //bullet Lifespan 
    std::string bullet = "bullet";
    for (auto& e : m_entities.getEntities(bullet))
    {
        sf::Color color = e->cShape->circle.getFillColor();
        color.a = ( (float)e->cLifespan->remaining / (float)e-> cLifespan->total) * 255.0f ;
        e->cShape->circle.setFillColor(color);

        sf::Color Outlinecolor = e->cShape->circle.getOutlineColor();
        Outlinecolor.a = ((float)e->cLifespan->remaining / (float)e->cLifespan->total) * 255.0f;
        e->cShape->circle.setOutlineColor(Outlinecolor);

        e->cLifespan->remaining -= 1 ;
        if (e->cLifespan->remaining <= 0)
        {
            e->destroy();
        }
    }

    //small enemy Lifespan 
    std::string smallEnemy = "smallEnemy";
    for (auto& e : m_entities.getEntities(smallEnemy))
    {
        sf::Color color = e->cShape->circle.getFillColor();
        color.a = ((float)e->cLifespan->remaining / (float)e->cLifespan->total) * 255.0f;
        e->cShape->circle.setFillColor(color);

        sf::Color Outlinecolor = e->cShape->circle.getOutlineColor();
        Outlinecolor.a = ((float)e->cLifespan->remaining / (float)e->cLifespan->total) * 255.0f;
        e->cShape->circle.setOutlineColor(Outlinecolor);


        e->cLifespan->remaining -= 1;
        if (e->cLifespan->remaining <= 0)
        {
            e->destroy();
        }
    }

    //special wepon lifespan 
    if ((m_currentFrame + 1) % 600 == 0) {
        m_specialBullet = 5;
    }
   
}

//enemy spawner 
void Game::sEnemySpawner()
{
    if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SI)
    {
        spawnEnemy();
        m_lastEnemySpawnTime = m_currentFrame;
    }
    
}


//rendering system 
void Game::sRender()
{
	m_window.clear();


	
    m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y );

	m_player->cTransform->angle += 1.0f;
    m_player->cShape->circle.setRotation(m_player->cTransform->angle);

	m_window.draw(m_player->cShape->circle);

    std::string enemy = "enemy";
    for (auto& e : m_entities.getEntities(enemy))
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);
        m_window.draw(e->cShape->circle);
    }

    std::string smallEnemy = "smallEnemy";
    for (auto& e : m_entities.getEntities(smallEnemy))
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);
        m_window.draw(e->cShape->circle);
    }

    std::string bullet = "bullet";
    for (auto& e : m_entities.getEntities(bullet))
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);
        m_window.draw(e->cShape->circle);
    }
   
    m_window.draw(m_text);
    
    m_text_death.setString("DEATH " + std::to_string(m_death));
    m_window.draw(m_text_death);

    m_text_specialBullet.setString("SPECIAL WEAPON " + std::to_string(m_specialBullet));
    m_window.draw(m_text_specialBullet);
 

	m_window.display();
}

//userInput
void Game::sUserInput()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        if (event.type == sf::Event::KeyPressed) 
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                std::cout << "W key pressed! Move forward." << std::endl;
                m_player->cInput->up = true;
                break;
            case sf::Keyboard::A:
                std::cout << "A key pressed! Move left." << std::endl;
                m_player->cInput->left = true;
                break;
            case sf::Keyboard::S:
                std::cout << "S key pressed! Move backward." << std::endl;
                m_player->cInput->down = true;
                break;
            case sf::Keyboard::D:
                std::cout << "D key pressed! Move right." << std::endl;
                m_player->cInput->right = true;
                break;
            default:
                break;
            }
        }
        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                std::cout << "W key pressed! Move forward." << std::endl;
                m_player->cInput->up = false;
                break;
            case sf::Keyboard::A:
                std::cout << "A key pressed! Move left." << std::endl;
                m_player->cInput->left = false;
                break;
            case sf::Keyboard::S:
                std::cout << "S key pressed! Move backward." << std::endl;
                m_player->cInput->down = false;
                break;
            case sf::Keyboard::D:
                std::cout << "D key pressed! Move right." << std::endl;
                m_player->cInput->right = false;
                break;
            default:
                break;
            }
        }


        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left )
        {
            // left mouse button is pressed: shoot
            // get the local mouse position (relative to a window)
            Vec2 localPosition;
            localPosition.x = sf::Mouse::getPosition(m_window).x; // window is a sf::Window
            localPosition.y = sf::Mouse::getPosition(m_window).y; // window is a sf::Window
            spawnBullet(m_player , localPosition );
            std::cout << "mouse left pressed \n";
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {   
            spawnSpecialWeapon(m_player);
            std::cout << "mouse left pressed \n";
        }

            
    }


}