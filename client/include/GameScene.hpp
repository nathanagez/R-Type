#ifndef Game_SCENE_HPP
#define Game_SCENE_HPP

#include "Scene.hpp"
#include "Entity.hpp"
#include "Application.hpp"
#include "ConnectScene.hpp"
#include "interfaces/IPackets.hpp"
#include <SFML/Audio.hpp>

class GameScene : public Scene
{
	public:
		GameScene(const std::string &name);

		void onCreate();
		void onDestroy();

		bool onEnable();
		bool onEvent(const sf::Event &event, sf::RenderWindow &window);
		bool onUpdate(const float fElapsedTime);
		bool onRender(sf::RenderWindow &window);
		bool onDisable();
		static void handleUDP_connection();
		static Sockets *client_udp;
		static void spawn_player_UDP();
		std::vector<std::string> user_list;
		static void move_UDP(UNUSED sf::Vector2f direction,UNUSED std::string username, UNUSED sf::Vector2f position);
		static void fire_UDP(std::string username);
		int score;

	private:
		int player_life;
		int boss_life;
		sf::SoundBuffer buffer;
		sf::SoundBuffer buffer_boom;
		sf::Sound pew;
		sf::Sound boom;
		int paralax_offset;
		std::string direction;
		sf::Font font;

		Entity background;
		Entity game_over;
		Entity fg_stars;
		std::vector<Entity*> player_list;
		std::vector<Entity*> entity_list;
		std::vector<Player_t> players_structs;

		sf::Text score_text;

		std::string my_username;
};

#endif /* Game_SCENE_HPP */
