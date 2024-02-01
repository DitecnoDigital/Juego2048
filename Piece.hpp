#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include <vector>
#include <math.h>

class Piece : public sf::Drawable {
	private:
		std::vector<sf::Color> colors;
		sf::Text text;
		sf::Texture texture;
		sf::Sprite sprite;
		int value = 0;
	public:
		Piece(int x, int y, sf::Font &font, sf::Texture &texture);
		void SetValue(int val);
		int GetValue() const;
		void Move(std::pair<int,int> dir);
		void SetPos(sf::Vector2f);
		sf::Vector2f GetPos();
		virtual void draw(sf::RenderTarget &rt, sf::RenderStates rs) const;
};

