#include "UI.hpp"

UI::UI(){
	std::ifstream in("bestScore.txt");
	in>>bestScore;
	
	if(!font.loadFromFile("resources/Heavitas/Heavitas.ttf")){
		std::cout<<"Error loading font\n";
	}
	
	bestTextScore.setFont(font);
	bestTextScore.setString(std::to_string(bestScore));
	bestTextScore.setCharacterSize(16);
	bestTextScore.setFillColor(sf::Color(255,255,255));
	bestTextScore.setOrigin(bestTextScore.getGlobalBounds().width/2,bestTextScore.getGlobalBounds().height/2);
	bestTextScore.setPosition(332.f,float(53.5));
	
	textScore.setFont(font);
	textScore.setString(std::to_string(score));
	textScore.setCharacterSize(16);
	textScore.setFillColor(sf::Color(255,255,255));
	textScore.setOrigin(textScore.getGlobalBounds().width/2,textScore.getGlobalBounds().height/2);
	textScore.setPosition(332.f,112.f);
	
	textGameOver.setFont(font);
	textGameOver.setString("Game Over");
	textGameOver.setCharacterSize(35);
	textGameOver.setFillColor(sf::Color(255,255,255));
	textGameOver.setOrigin(textGameOver.getGlobalBounds().width/2,textGameOver.getGlobalBounds().height/2);	
	textGameOver.setPosition(200,300);
	
	textNewScore.setFont(font);
	textNewScore.setString("New Score");
	textNewScore.setCharacterSize(35);
	textNewScore.setFillColor(sf::Color(255,255,255));
	textNewScore.setOrigin(textNewScore.getGlobalBounds().width/2,textNewScore.getGlobalBounds().height/2);	
	textNewScore.setPosition(200,300);
}

void UI::SetScore(int val){
	score=val;
	textScore.setString(std::to_string(score));
	textScore.setOrigin(textScore.getGlobalBounds().width/2,textScore.getGlobalBounds().height/2);
}

void UI::GameOver(){
	if(score>bestScore){
		newScore=true;
		std::ofstream out("bestScore.txt");
		out<<score;
	}else gameOver=true;
}

void UI::draw(sf::RenderTarget &rt, sf::RenderStates rs) const{
	rt.draw(bestTextScore,rs);
	rt.draw(textScore,rs);
	if(gameOver) rt.draw(textGameOver,rs);
	if(newScore) rt.draw(textNewScore,rs);
}


