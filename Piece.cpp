#include "Piece.hpp"

Piece::Piece(int x, int y, sf::Font &font, sf::Texture &texture){
	text.setFont(font);
	text.setString(std::to_string(value));
	text.setCharacterSize(24);
	text.setPosition(float(x+75.f/2.f),float(y+75.f/2.f)-5);
	text.setFillColor(sf::Color(255,255,255));
	
	colors={sf::Color(102,102,102),sf::Color(255,166,0),sf::Color(245,151,245),sf::Color(51,204,153),sf::Color(255,110,110),sf::Color(255,204,77),sf::Color(166,166,255),sf::Color(137,194,247),sf::Color(0,255,255),sf::Color(0,128,0),sf::Color(255,0,255), sf::Color(128,128,0)};
	
	sprite.setPosition(x,y);
	sprite.setColor(colors[0]);
	sprite.setTexture(texture);
}


void Piece::SetValue(int val){
	value=val;
	text.setString(std::to_string(value));
	text.setOrigin(text.getGlobalBounds().width/2,text.getGlobalBounds().height/2);
	
	if(value==0) sprite.setColor(colors[0]);
	else{
		bool entro = 0;
		for(int i = 1; i < 15; i++){
			if(value&(1<<i)){
				sprite.setColor(colors[i]);
				entro=1;
			}
		}
		if(!entro){
			value=0;
			sprite.setColor(colors[0]);
		}
	}
}

int Piece::GetValue() const{
	return value;
}

void Piece::Move(std::pair<int,int> dir){
	sprite.move(dir.first,dir.second);
	text.move(dir.first,dir.second);;
}


void Piece::SetPos(sf::Vector2f pos){
	sprite.setPosition(pos.x,pos.y);
	text.setPosition(float(pos.x+75.f/2.f),float(pos.y+75.f/2.f)-5);
}

sf::Vector2f Piece::GetPos(){
	return sprite.getPosition();
}

void Piece::draw(sf::RenderTarget &rt, sf::RenderStates rs) const{
	rt.draw(sprite,rs);
	if(value!=0) rt.draw(text,rs);
}




