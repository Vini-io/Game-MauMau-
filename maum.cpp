#include <iostream>

using namespace std;


struct CreateCard{
		
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


class BunchPlayer{
	Node* top;
	int tam;
	public:
		
		BunchPlayer();
		
		bool push(CreateCard card);
		void pop();
		int size();
	
};

BunchPlayer::BunchPlayer(){
	top = 0;
	tam = 0;
}


bool BunchPlayer::push(CreateCard card){
	Node* node = Node::createNode(card);
	
	if(node){
		node->next = top;
		top = noode;
		tam++;
		return true;
	}
	return false;
}

void BunchPlayer::pop(){
	if(top){
		Node* NodeAux = top;
		top = top->next;
		Node::removeNode(NodeAux);
		tam--;
	}
}
	
////////////////////////////////////////////////////////////////////////////////////////




class NodeListD{
	public:
	NodeListD* next;
	NodeListD* prev;
	BunchPlayer Bp;
	
	static NodeListD* createNodeListD(BunchPlayer Bp);
	static void removeNodeListD(NodeListD* NdLD);
	
};

NodeListD* NodeListD::createNodeListD(BunchPlayer BunchP){
	NodeListD NdLD = new NodeListD;
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
	
	CreateBunch Bunch[3];
	CreateCard card;
	
	char cardChar;
	int full = 0, j = 1;
	
	
	
	while(full < 104){
		
			for(int i = 0; i < 2; i++){
				cin>>cardChar;
				card.Card(cardChar, i);
			}
			
			j = (j + 1) % 2;
			Bunch[j].push(card);
			
		full++;
	}
	
	
	while(Bunch[0].size() != 0 || Bunch[1].size() != 0){
		
		if(Bunch[0].size() != 0){
			Bunch[2].push(Bunch[0].Top());
			Bunch[0].pop();
		}
		if(Bunch[1].size() != 0){
			Bunch[2].push(Bunch[1].Top());
			Bunch[1].pop();
		}
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
	
}