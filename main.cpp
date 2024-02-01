#include <iostream>
#include <SFML/Graphics.hpp>
#include "Board.hpp"
#include "UI.hpp"


Board board;
UI ui;

sf::Texture  backgroundTexture;
sf::Sprite background;

int main(){
	
	if(!backgroundTexture.loadFromFile("resources/background.png")){
		std::cout<<"Error loading texture\n";
	}
	
	background.setTexture(backgroundTexture);
	background.setPosition(0,0);

	sf::RenderWindow window(sf::VideoMode(400,515),"2048");
	window.setFramerateLimit(60);
	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event)){
			if(event.type==sf::Event::Closed) window.close();
		}
		
		board.Update();
		ui.SetScore(board.GetScore());
		if(board.isGameOver()) ui.GameOver();
		//std::cout<<board.isGameOver()<<'\n';
		
		window.clear();
		window.draw(background);
		window.draw(board);
		window.draw(ui);
		window.display();
	}
	return 0;
}
