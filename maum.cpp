 #include <iostream>

using namespace std;



// Estrutura da carta


struct CreateCard{;
		
	char card[2];
		
	void Card(char card, int i){
		this->card[i] = card;
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





// Criador de monte para cada player


class BunchPlayer{
	Node* top;
	int tam;
	public:
		
		BunchPlayer();
		
		bool push(CreateCard card);
		void pop();
		int size();
		CreateCard Top();
	
};

BunchPlayer::BunchPlayer(){
	top = 0;
	tam = 0;
}


bool BunchPlayer::push(CreateCard card){
	Node* node = Node::createNode(card);
	
	if(node){
		node->next = top;
		top = node;
		tam++;
		return true;
	}
	return false;
}

int BunchPlayer::size(){
	return tam;
}

void BunchPlayer::pop(){
	if(top){
		Node* NodeAux = top;
		top = top->next;
		Node::removeNode(NodeAux);
		tam--;
	}
}

CreateCard BunchPlayer::Top(){
	return top->card;
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

/////





// class Player é uma lista circular para rotacionar o jogo, para cada vez de cada player.

class Players{
	NodeListD* head;
	NodeListD* it;
	int tam;
	
	public:
		Players();
		bool insertNext(BunchPlayer Bp);
		bool Erase();
		bool itPP();
		bool itMM();
		
};

Players::Players(){
	it = head = 0;
	tam = 0;
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
	CreateCard card; // criador de cartas
	
	char cardChar; //criador de tipo da carta
	int full = 0, j = 1;
	
	
	int Qplayers, QRounds = 0;
	
	cin>>QRounds;
	
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
		

	cout<<"carta foiadicionado ao monte. Tamanho:["<<Bunch[2].size()<<"]: "<<Bunch[2].Top().GetCard()<<Bunch[2].Top().GetValue()<<endl;
	
	}
	cout<<"\n\n\n";
	
	
	
	
	// Criador de monte dos players
	BunchPlayer PlayerBunch[Qplayers]; //(Qplayers): Quantidade de players. (PlayerBunch): são monte de cada player
	
	
	// Distribuindo cartas do monte main para cada player.
	for(int i = 0; i < Qplayers; i++){
		
		while(PlayerBunch[i].size() < 5){
			PlayerBunch[i].push(Bunch[2].Top());
			Bunch[2].pop();
		}
		
		
	}
	cout<<"\nTamanho da monte: "<<Bunch[2].size()<<endl;
	
	
	
	
	
	Players gameRotation[Qplayers];
	
	
	
	
	
	
	
	
	return 0;
	
}