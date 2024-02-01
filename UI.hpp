#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

class UI : public sf::Drawable{
	private:
		sf::Font font;
		sf::Text bestTextScore;
		sf::Text textScore;
		sf::Text textGameOver;
		sf::Text textNewScore;
		int bestScore=0;
		int score=0;
		bool newScore=0;
		bool gameOver=0;
	public:
		UI();
		void SetScore(int);
		void GameOver();
		virtual void draw(sf::RenderTarget &rt, sf::RenderStates rs) const;
};

