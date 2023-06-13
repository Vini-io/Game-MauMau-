 #include <iostream>

using namespace std;



// Estrutura da carta


struct CreateCard{;
		
	char card[2];
	int points;
	
	CreateCard(){
		points = 0;
	}
		
	void Card(char cd, int i){
		this->card[i] = cd;
		
		if(cd == 'A'){
			points = 1;
		}else if(cd == 'B'){
			points = 2;
		
		}else if(cd == 'C'){
			points = 3;
		
		}else if(cd == 'D'){
			points = 4;
		
		}else if(cd == 'E'){
			points = 5;
		
		}else if(cd == 'F'){
			points = 6;
		
		}else if(cd == 'G'){
			points = 7;
		
		}else if(cd == 'H'){
			points = 8;
		
		}else if(cd == 'I'){
			points = 9;
		
		}else if(cd == 'J'){
			points = 10;
		
		}else if(cd == 'K'){
			points = 11;
		
		}else if(cd == 'L'){
			points = 12;
		
		}else if(cd == 'M'){
			points = 13;
		}
		
	}
		
	char GetValue(){
		return card[0];
	}
		
	char GetCard(){
		return card[1];
	}
	
			
};


////////////////////////////////////////////////////////////////////////////////////////





// Nó para criar carta


class Node{
	public:
	Node* next;
	
	CreateCard card;
	
	static Node* createNode(CreateCard cd);
	static void removeNode(Node* nd);

};

Node* Node::createNode(CreateCard cd){
	Node* nd = new Node;
	if(nd){
		nd->next = 0;
		nd->card = cd;
	}
	return nd;
}

void Node::removeNode(Node* nd){
	delete nd;
}

////////////////////////////////////////////////////////////////////////////////





// Criador de monte


class CreateBunch{
	
	Node* top;
	int tam;
	
	public:
	CreateBunch();
	CreateCard Top();
	bool push(CreateCard card);
	void pop();
	int size();
};

CreateBunch::CreateBunch(){
	tam = 0;
	top = 0;
}


bool CreateBunch::push(CreateCard card){
	Node* node = Node::createNode(card);
	if(node){
		node->next = top;
		top = node;
		tam++;
		return true;
	}
	return false;
}

void CreateBunch::pop(){
	if(top){
		Node* topAux = top;
		top = top->next;
		Node::removeNode(topAux);
		tam--;
	}
}


int CreateBunch::size(){
	return tam;
}

CreateCard CreateBunch::Top(){
	return top->card;
}



////////////////////////////////////////////////////////////////////////////////////////


// Nó para criar monte para os players

class NodeListBunchPlayer{
	public:
	NodeListBunchPlayer* next;
	NodeListBunchPlayer* prev;
	CreateCard cd;
	
	static NodeListBunchPlayer* createNodeListD(CreateCard BunchCd);
	static void removeNodeListD(NodeListBunchPlayer* NdLD);
	
};

NodeListBunchPlayer* NodeListBunchPlayer::createNodeListD(CreateCard BunchCd){
	NodeListBunchPlayer* NdLD = new NodeListBunchPlayer;
	if(NdLD){
		NdLD->next = NdLD->prev = 0;
		NdLD->cd = BunchCd;
	}
	return NdLD;
}

void NodeListBunchPlayer::removeNodeListD(NodeListBunchPlayer* NdLD){
	delete NdLD;
}

//////////////////////////////////////////////////////////////


// Criador de monte para cada player (lista encardeada circula)


class BunchPlayer{
	NodeListBunchPlayer* head;
	NodeListBunchPlayer* it;
	NodeListBunchPlayer** toIt;
	int tam;
	
	public:
		int id;
		int allPoints;
		
		BunchPlayer();
		bool insertNext(CreateCard cd);
		bool Erase();
		bool itPP();
		bool itMM();
		int size();
		bool hasIt();
		CreateCard pointedIt();
	
};


BunchPlayer::BunchPlayer(){
	head = it = 0;
	id = allPoints = tam = 0;
	
}

bool BunchPlayer::hasIt(){
	if(*toIt == it) return true;
	return false;
}

int BunchPlayer::size(){
	return tam;
}

CreateCard BunchPlayer::pointedIt(){
	return it->cd;
}

bool BunchPlayer::insertNext(CreateCard cd){
	
	NodeListBunchPlayer* NdListBunchPlayer = NodeListBunchPlayer::createNodeListD(cd);
	
	if(NdListBunchPlayer){
		
		allPoints = allPoints + NdListBunchPlayer->cd.points;
		
		if(!head){
			it = head = NdListBunchPlayer;
			it->next = it->prev = NdListBunchPlayer;
		}else{
			
			(it->next)->prev = NdListBunchPlayer;
			NdListBunchPlayer->next = it->next;
			NdListBunchPlayer->prev = it;
			it->next = NdListBunchPlayer;
		}
		if(NdListBunchPlayer->cd.points > it->cd.points){
			it = NdListBunchPlayer;
			toIt = &it;
		}
		tam++;
	return true;
	}
	return false;
}

bool BunchPlayer::Erase(){ // ***************************** verificar exclusão ****************************************
	
	if(head){
		
		NodeListBunchPlayer* itAux = it;
		
		if(it == head){
			
			(it->prev)->next = it->next;
			(it->next)->prev = it->prev;
			head = it->next;
			NodeListBunchPlayer::removeNodeListD(itAux);
		}else{
			(it->prev)->next = it->next;
			(it->next)->prev = it->prev;
			NodeListBunchPlayer::removeNodeListD(itAux);
		}
		
		it = it->next;
		itAux = it;
		
		while(itAux->next != it){
			
			itAux = itAux->next;
			
			if(itAux->cd.points > it->cd.points){
				it = itAux;
				toIt = &it;
			}
			
		}
		
		tam--;
		return true;
	}
	return false;
}

bool BunchPlayer::itPP(){
	if(!it || !it->next) return false;
	
	it = it->next;
	return true;
}

bool BunchPlayer::itMM(){
	if(!it || !it->prev) return false;
	
	it = it->prev;
	return true;
}





	
////////////////////////////////////////////////////////////////////////////////////////



// Nó para lista circular para rotacionar o jogo

class NodeListD{
	public:
	NodeListD* next;
	NodeListD* prev;
	BunchPlayer Bp;
	
	static NodeListD* createNodeListD(BunchPlayer Bp);
	static void removeNodeListD(NodeListD* NdLD);
	
};

NodeListD* NodeListD::createNodeListD(BunchPlayer BunchP){
	NodeListD* NdLD = new NodeListD;
	if(NdLD){
		NdLD->next = NdLD->prev = 0;
		NdLD->Bp = BunchP;
	}
	return NdLD;
}

void NodeListD::removeNodeListD(NodeListD* NdLD){
	delete NdLD;
}

////////////////////////////////////////////////////////////////////////////////////////





// class Player é uma lista circular para rotacionar o jogo, para cada vez de cada player.

class Players{ // gameRotation
	NodeListD* head;
	NodeListD* it;
	NodeListD* it2;
	int tam;
	
	public:
		Players();
		bool insertNext(BunchPlayer Bp);
		void deletePlayer();
		int size();
		bool Erase();
		bool itPP();
		bool itMM();
		void begin();
		BunchPlayer pointedIt();
};

Players::Players(){
	it2 = it = head = 0;
	tam = 0;
}

int Players::size(){
	return tam;
}

void Players::deletePlayer(){
	
	do{
		it2 = it2->next;
		
		if(it2->Bp.allPoints > it->Bp.allPoints){
			it = it2;
		}
		
	}while(it != it2->next);
	
	cout<<"Player["<<it->Bp.id<<"]"<<" foi removido! com "<<it->Bp.allPoints<<" pontos."<<endl;
	
	Players::Erase();

}

BunchPlayer Players::pointedIt(){
	return it->Bp;
}


void Players::begin(){
	it = head;
}


bool Players::insertNext(BunchPlayer Bp){
	
	NodeListD* NdListD = NodeListD::createNodeListD(Bp);
	
	if(NdListD){
		if(!head){
			it2 = it = head = NdListD;
			it->prev = it->next = NdListD;
		}else{
			
			
			(it->next)->prev = NdListD;
			NdListD->next = it->next;
			NdListD->prev = it;
			it->next = NdListD;
			it2 = it = NdListD;
		}
		tam++;
	return true;
	}
	return false;
}

bool Players::Erase(){
	
	if(head){
		
		NodeListD* itAux = it;
		
		if(it == head){
			
			(it->prev)->next = it->next;
			(it->next)->prev = it->prev;
			head = it->next;
			NodeListD::removeNodeListD(itAux);
		}else{
			(it->prev)->next = it->next;
			(it->next)->prev = it->prev;
			NodeListD::removeNodeListD(itAux);
		}
		it2 = it = it->next;
		tam--;
		return true;
	}
	return false;
}

bool Players::itPP(){
	if(!it || !it->next) return false;
	
	it = it->next;
	return true;
}

bool Players::itMM(){
	if(!it || !it->prev) return false;
	
	it = it->prev;
	return true;
}


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////


int main(){
	
	CreateBunch Bunch[3]; // criar montes para embaralhar cartas //Posição 0 e 1 são montes para embaralhar, quanto posição 2 é monte principal
	CreateCard card; // criador de estruturas para cartas
	
	char cardChar; //criador de tipo da carta
	int full = 0, j = 1;
	
	
	int Qplayers = 0, Qmatch = 0;
	
	cin>>Qmatch;
	
	do{
		cin>>Qplayers;
	
	}while(Qplayers < 2 || Qplayers > 10);
	
	//montar cartas para embaralhar
	while(full < 104){
		
			for(int i = 0; i < 2; i++){
				cin>>cardChar;
				card.Card(cardChar, i);
			}
			
			j = (j + 1) % 2;
			Bunch[j].push(card);
			
		full++;
	}
	
	
	//Embaralhar cartas no monte
	while(Bunch[0].size() != 0 || Bunch[1].size() != 0){
		
		if(Bunch[0].size() != 0){
			Bunch[2].push(Bunch[0].Top());
			Bunch[0].pop();
		}
		if(Bunch[1].size() != 0){
			Bunch[2].push(Bunch[1].Top());
			Bunch[1].pop();
		}
	//Bunch[2]: Bunch da posição 2 é monte princial aonde foi embaralhado todas cartas
		
	}

	
	
	
	
	// Criador de monte dos players
	BunchPlayer PlayerBunch[Qplayers]; //(Qplayers): Quantidade de players. (PlayerBunch): são monte de cada player
	
	
	// gameRotation é uma lista rotativa para qual jogador ou sentido está o jogo
	Players gameRotation;
	
	
	
	// Distribuindo cartas do monte main para cada player.
	for(int i = 0; i < Qplayers; i++){
		
		while(PlayerBunch[i].size() < 5){
			PlayerBunch[i].insertNext(Bunch[2].Top());
			PlayerBunch[i].id = i;
			Bunch[2].pop();
		}
		
		gameRotation.insertNext(PlayerBunch[i]);
		
	}
	
	
	// lixo é mesa do jogo, aonde vai ser jogada as cartas dos players
	CreateBunch lixo;
	
	bool cardToLixo, wayGame, NextToNext, buyCard2, buyCard3, finishRound, finishMatch;
	

	for(int i = 0; i < Qmatch; i++){ // quantidade de partidas
		
		finishMatch = false;
		
		while(!finishMatch){ // rodadas
			
			gameRotation.begin();
			finishRound = false;
			while(!finishRound){ // rotação das cartas
			
				// aqui o jogador compra as cartas
					if(buyCard2){
						gameRotation.pointedIt().insertNext(Bunch[2].Top());
						Bunch[2].pop();
						gameRotation.pointedIt().insertNext(Bunch[2].Top());
						Bunch[2].pop();
					} 
					else if(buyCard3){
						gameRotation.pointedIt().insertNext(Bunch[2].Top());
						Bunch[2].pop();
						gameRotation.pointedIt().insertNext(Bunch[2].Top());
						Bunch[2].pop();
						gameRotation.pointedIt().insertNext(Bunch[2].Top());
						Bunch[2].pop();
					}
			
			
			
				cardToLixo = false;
				
				if(lixo.size() == 0){ // rodada acabou de começar!
					lixo.push(gameRotation.pointedIt().pointedIt()); // adicionar carta de tal player no lixo
					gameRotation.pointedIt().Erase();// remove carta do player
					cout<<"Jogador ["<<gameRotation.pointedIt().id<<"] jogou um carta!"<<endl;
					cardToLixo = true;
				}else{
						
					do{
						
						if(lixo.Top().GetValue() == gameRotation.pointedIt().pointedIt().GetValue() || lixo.Top().GetCard() == gameRotation.pointedIt().pointedIt().GetCard()){
			
							lixo.push(gameRotation.pointedIt().pointedIt());// adicionar carta de tal player no lixo
							gameRotation.pointedIt().Erase();// remove carta do player
							cout<<"Jogador ["<<gameRotation.pointedIt().id<<"] jogou um carta!"<<endl;
							cardToLixo = true;
						}else
							gameRotation.pointedIt().itPP(); // proxima carta do player que it está apontado
						}
						while(!gameRotation.pointedIt().hasIt() || cardToLixo);
						
						
						if(!cardToLixo){  // jogador não teve carta para jogar
							gameRotation.pointedIt().insertNext(Bunch[2].Top());
							Bunch[2].pop();
							
							if(lixo.Top().GetValue() == gameRotation.pointedIt().pointedIt().GetValue() || lixo.Top().GetCard() == gameRotation.pointedIt().pointedIt().GetCard()){
								lixo.push(gameRotation.pointedIt().pointedIt());// adicionar carta de tal player no lixo
								gameRotation.pointedIt().Erase();// remove carta do player
								cout<<"Jogador ["<<gameRotation.pointedIt().id<<"] jogou um carta!"<<endl;
								cardToLixo = true;
							}
						}
					}
					
					wayGame = buyCard2 = buyCard3 = false;
					
					if(cardToLixo){ //penalidades
						if(lixo.Top().GetValue() == 'L'){
							if(wayGame) wayGame = false;
							else wayGame = true;
						}else if(lixo.Top().GetValue() == 'A'){
							NextToNext = true;
						}else if(lixo.Top().GetValue() == 'G'){
							buyCard2 = true;
						}else if(lixo.Top().GetValue() == 'I'){
							buyCard3 = true;
						}
					}
					
					if(wayGame){
						if(NextToNext){
							gameRotation.itPP(); // proximo do proximo jogador
							gameRotation.itPP();
						}
						else{
							gameRotation.itPP();
						}
						
					}else{
						if(NextToNext){
							gameRotation.itMM(); // anterior do anterior
							gameRotation.itMM(); 
						}
						else{
							gameRotation.itMM(); // jogador anterior
						}
					}
					 
					 
					 
					
					if(gameRotation.pointedIt().size() == 0){
						finishRound = true;
						gameRotation.deletePlayer();
					}		
			}
			if(gameRotation.size() == 1){ // verificar se tem apenas 1 jogador
				finishMatch = true;
			}		
		}
		
		cout<<"Vencedor da partida "<<i+1<<": Jogador "<<gameRotation.pointedIt().id + 1<<endl;
		
	}
	

	return 0;
	
}