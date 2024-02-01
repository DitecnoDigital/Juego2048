#include "Board.hpp"

Board::Board(){
	if(!font.loadFromFile("resources/Heavitas/Heavitas.ttf")){
		std::cout<<"Error loading font\n";
	}
	
	if(!pieceTexture.loadFromFile("resources/piece.png")){
		std::cout<<"Error loading texture\n";
	}
	
	piece.resize(4,std::vector<Piece>(4,Piece(0,0,font,pieceTexture)));
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			piece[i][j]=Piece(37+85*j,151+85*i,font,pieceTexture);
		}
	}
	
	dest.resize(4,std::vector<sf::Vector2f>(4));
	piece[0][0].SetValue(2);
	piece[3][3].SetValue(2);
}


bool Board::isGameOver(){
	
	bool gameOver = true;
	
	std::pair<int,int> mov={0,0};
	
	for(int k = 0; k < 4; k++){
		
		if(k==0) mov={0,-1};
		if(k==1) mov={0,1};
		if(k==2) mov={-1,0};
		if(k==3) mov={1,0};
		
		int iniI=0;
		int movI=1;
		int iniJ=0;
		int movJ=1;
		
		if(mov.first==1)  iniI=3,movI=-1;
		if(mov.second==1) iniJ=3, movJ=-1;
		
		for(int i = iniI; i>=0 && i<4; i+=movI){
			for(int j = iniJ; j>=0 && j<4; j+=movJ){
				
				if(piece[i][j].GetValue()!=0){
					
					if(i+mov.first<0||i+mov.first>3||j+mov.second<0||j+mov.second>3) continue;
					
					if(piece[i+mov.first][j+mov.second].GetValue()==piece[i][j].GetValue()){
						gameOver=false;
						//std::cout<<"1\n";
					}
					if(piece[i+mov.first][j+mov.second].GetValue()==0){
						gameOver=false;
						//std::cout<<i+mov.first<<" "<<j+mov.second<<"\n";
					}
					if(dest[i+mov.first][j+mov.second]!=sf::Vector2f(i+mov.first,j+mov.second)){
						gameOver=false;
						//std::cout<<"3\n";
					}
				}
			}	
		}
	}
	return gameOver;
}



void Board::MoveCheck(){
	int iniI=0;
	int movI=1;
	int iniJ=0;
	int movJ=1;
		
	if(movement.first==1)  iniI=3,movI=-1;
	if(movement.second==1) iniJ=3, movJ=-1;
	
	
	for(int i = iniI; i>=0 && i<4; i+=movI){
		for(int j = iniJ; j>=0 && j<4; j+=movJ){
			dest[i][j]=sf::Vector2f(i,j);
			
			if(piece[i][j].GetValue()!=0){
				
				if(i+movement.first<0||i+movement.first>3||j+movement.second<0||j+movement.second>3) continue;
				
				if(piece[i+movement.first][j+movement.second].GetValue()==0||dest[i+movement.first][j+movement.second]!=sf::Vector2f(i+movement.first,j+movement.second)){
					dest[i][j]=sf::Vector2f(i+movement.first,j+movement.second);
					makeMovement=false;				
				}else if(piece[i+movement.first][j+movement.second].GetValue()==piece[i][j].GetValue()){
					dest[i][j]=sf::Vector2f(i+movement.first,j+movement.second);
					score+=piece[i][j].GetValue()*2;
					piece[i][j].SetValue(piece[i][j].GetValue()*2);
					piece[i+movement.first][j+movement.second].SetValue(0);
					makeMovement=false;
				}
				
			}
		}
	}
}


bool Board::PieceCheck( int i , int j){
	if(movement.second==-1) return piece[i][j].GetPos().x<=37+85*dest[i][j].y;
	if(movement.second==1) return piece[i][j].GetPos().x>=37+85*dest[i][j].y;
	if(movement.first==-1) return piece[i][j].GetPos().y<=151+85*dest[i][j].x;
	if(movement.first==1) return piece[i][j].GetPos().y>=151+85*dest[i][j].x;
	return false;
}


void Board::MakeMovement(){
	
	int iniI=0;
	int movI=1;
	int iniJ=0;
	int movJ=1;
		
	if(movement.first==1)  iniI=3,movI=-1;
	if(movement.second==1) iniJ=3, movJ=-1;
	
	int listo = 0;
	
	for(int i = iniI; i>=0 && i<4; i+=movI){
		for(int j = iniJ; j>=0 && j<4; j+=movJ){
		
			if(i+movement.first<0||i+movement.first>3||j+movement.second<0||j+movement.second>3) continue;
			
			if(piece[i][j].GetValue()!=0){
				if(PieceCheck(i,j)){
					listo++;
					piece[i][j].SetPos(sf::Vector2f(37+85*j,151+85*i));
					int val = piece[i][j].GetValue();
					piece[i][j].SetValue(0);
					piece[dest[i][j].x][dest[i][j].y].SetValue(val);
				}
			}else listo++;
		}
	}
	
	if(listo==12){
		makeMovement=true;
		MoveCheck();
	}else{
		for(int i = iniI; i>=0 && i<4; i+=movI){
			for(int j = iniJ; j>=0 && j<4; j+=movJ){
				if(i+movement.first<0||i+movement.first>3||j+movement.second<0||j+movement.second>3) continue;
			
				if(piece[i][j].GetValue()!=0&&!PieceCheck(i,j)){
					if(movement.second==-1) piece[i][j].Move(std::pair<int,int>({-10,0}));
					if(movement.second==1) piece[i][j].Move(std::pair<int,int>({10,0}));
					if(movement.first==-1) piece[i][j].Move(std::pair<int,int>({0,-10}));
					if(movement.first==1) piece[i][j].Move(std::pair<int,int>({0,10}));
				}
			}
		}
	}
}


void Board::NewPieces(){

	int I,J;
	std::map<int,int> mp;
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			mp[piece[i][j].GetValue()]++;
		}
	}
	
	makeMovement = false;
	
	for(auto i:mp){
		if(i.first!=0&&i.second>1){
			makeMovement=true;	
		}
	}
	
	if(!makeMovement){
		for(int i = 0; i < 2; i++){
			srand(time(NULL));
			do{
				I=rand()%4;
				J=rand()%4;
			}while(piece[I][J].GetValue()!=0);
			
			piece[I][J].SetValue(2);
			
			if(i==0){
				i=2;
				for(int h = 0; h < 4; h++){
					for(int j = 0; j < 4; j++){
						if(piece[h][j].GetValue()==0) i = 0; 
					}
				}
			}
		}
		
	}else{
		srand(time(NULL));
		do{
			I=rand()%4;
			J=rand()%4;
		}while(piece[I][J].GetValue()!=0);
			
		if(rand()%2==0) piece[I][J].SetValue(2);
		else piece[I][J].SetValue(4);
	}
	makeMovement=true;
}

int Board::GetScore(){
	return score;
}

void Board::Update(){
	if(makeMovement){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			movement={0,-1};
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			movement={0,1};
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			movement={-1,0};
		}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			movement={1,0};
		}else{
			movement={0,0};
		}
		
		if(movement.first!=movement.second) MoveCheck();
	}else{
		MakeMovement();
		if(makeMovement){
			NewPieces();
		}
	}
}


void Board::draw(sf::RenderTarget &rt,sf::RenderStates rs) const{
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(piece[i][j].GetValue()==0) rt.draw(piece[i][j],rs);
		}
	}
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(piece[i][j].GetValue()!=0) rt.draw(piece[i][j],rs);
		}
	}
}
