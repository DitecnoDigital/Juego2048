#include <iostream>
#include <vector>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "Piece.hpp"

class Board : public sf::Drawable {
	private:
		sf::Font font;
		sf::Texture pieceTexture;
		std::vector<std::vector<Piece>> piece;
		bool makeMovement = true;
		std::pair<int,int> movement = {0,0};
		std::vector<std::vector<sf::Vector2f>> dest;
		int score;
	public:
		Board();
		bool isGameOver();
		void MoveCheck();
		bool PieceCheck(int i, int j);
		void MakeMovement();
		void NewPieces();
		int GetScore();
		void Update();
		virtual void draw(sf::RenderTarget &rt, sf::RenderStates rs) const;
};
