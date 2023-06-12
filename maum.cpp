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
			points = points + 1;
		}else if(cd == 'B'){
			points = points + 2;
		
		}else if(cd == 'C'){
			points = points + 3;
		
		}else if(cd == 'D'){
			points = points + 4;
		
		}else if(cd == 'E'){
			points = points + 5;
		
		}else if(cd == 'F'){
			points = points + 6;
		
		}else if(cd == 'G'){
			points = points + 7;
		
		}else if(cd == 'H'){
			points = points + 8;
		
		}else if(cd == 'I'){
			points = points + 9;
		
		}else if(cd == 'J'){
			points = points + 10;
		
		}else if(cd == 'K'){
			points = points + 11;
		
		}else if(cd == 'L'){
			points = points + 12;
		
		}else if(cd == 'M'){
			points = points + 13;
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
	int tam;
	
	public:
		int id;
		BunchPlayer();
		bool insertNext(CreateCard cd);
		bool Erase();
		bool itPP();
		bool itMM();
		int size();
		CreateCard pointedIt();
	
};


BunchPlayer::BunchPlayer(){
	head = it = 0;
	tam = 0;
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
	int tam;
	
	public:
		Players();
		bool insertNext(BunchPlayer Bp);
		bool Erase();
		bool itPP();
		bool itMM();
		void begin();
		BunchPlayer pointedIt();
};

Players::Players(){
	it = head = 0;
	tam = 0;
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
			it = head = NdListD;
		
		}else{
			it->next = NdListD;
			NdListD->prev = it;
			it = NdListD;
			NdListD->next = head;
			head->prev = NdListD;
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
			it = it->next;
			head = it;
			NodeListD::removeNodeListD(itAux);
		}else{
			(it->prev)->next = it->next;
			(it->next)->prev = it->prev;
			it = it->next;
			NodeListD::removeNodeListD(itAux);
		}
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
		

	//cout<<"carta foiadicionado ao monte. Tamanho:["<<Bunch[2].size()<<"]: "<<Bunch[2].Top().GetCard()<<Bunch[2].Top().GetValue()<<endl;
	
	}
	//cout<<"\n\n\n";
	
	
	
	
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
	//cout<<"\nTamanho da monte: "<<Bunch[2].size()<<endl;
	
	
	// lixo é mesa do jogo, aonde vai ser jogada as cartas dos players
	CreateBunch lixo;
	
	int turnPlayer = Qplayers - 1;
	
	
//	cout<<"vez: "<<turnPlayer;
	
	
	for(int i = 0; i < Qmatch; i++){ // quantidade de partidas
		
		gameRotation.begin();
		
		turnPlayer = (turnPlayer + 1) % Qplayers; // qual vez do jogador
		
		
		while(false){ // rodadas
			
				if(lixo.size() == 0){ // rodada acabou de começar!
					lixo.push(gameRotation.pointedIt().pointedIt()); // adicionar carta de tal player no lixo
					gameRotation.pointedIt().Erase();// remove carta do player
					cout<<"Jogador ["<<gameRotation.pointedIt().id<<"] jogou um carta!"<<endl;
				}else{
					
					
					
					
					
				}
			
			
		}
		
	}
	
	

	// ultima coisa feita foi indicar qual carta do player é maior no insert e na exclusão
	
	return 0;
	
}