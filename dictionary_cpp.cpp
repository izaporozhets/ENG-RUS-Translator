#include "pch.h"
#include "dictionary_h.h"

#define EN "EN.txt"
#define RU "RU.txt"


int max = 0;//использованo в MaxRequest
Node* temp;	//использованo в MaxRequest

struct Node {			//структура узла
	string EnWord;
	string RuWord;
	int request;
	Node* leftBranch;
	Node* rightBranch;
};


void AddBranch(string EnWord, string RuWord, int request, Node *& nextBranch) {//добавление элемента в дерево
	if (nextBranch == nullptr) {
		nextBranch = new Node;
		nextBranch->EnWord = EnWord;
		nextBranch->RuWord = RuWord;
		nextBranch->request = request;
		nextBranch->leftBranch = nullptr;
		nextBranch->rightBranch = nullptr;
		return;

	}
	else
	{
		if (nextBranch->EnWord > EnWord) {
			AddBranch(EnWord, RuWord, request, nextBranch->leftBranch);
		}
		else {
			AddBranch(EnWord, RuWord, request, nextBranch->rightBranch);
		}
	}
}

bool Find(string findWord, Node *nextBranch, bool success) {//поиск перевода по заданному слову
	if (nextBranch == nullptr) {
		return success;
	}
	else {
		if (!success) {
			if (strcmp(nextBranch->EnWord.c_str(), findWord.c_str()) < 0) {
				Find(findWord, nextBranch->rightBranch, success);

			}
			if (strcmp(nextBranch->EnWord.c_str(), findWord.c_str()) > 0) {
				Find(findWord, nextBranch->leftBranch, success);
			}

			if (strcmp(nextBranch->EnWord.c_str(), findWord.c_str()) == 0)
			{
				nextBranch->request++;
				cout << findWord << " - " << nextBranch->RuWord << "\t\t  :: " << nextBranch->request << endl;
				success = true;
				return success;
			}
		}
		else {
			return success;
		}
	}
}

void DeleteTree(Node *&nextBranch) {//удаление словаря
	if (nextBranch == nullptr) {
		return;
	}
	if (nextBranch->leftBranch != nullptr) {
		DeleteTree(nextBranch->leftBranch);
	}
	if (nextBranch->rightBranch != nullptr) {
		DeleteTree(nextBranch->rightBranch);
	}
	delete nextBranch;
	nextBranch = nullptr;
}

void Dictionary(Node *& nextBranch) {//подключение файлов с английскими словами и переводам к ним			
	string en;
	string ru;
	ifstream fileEn(EN);
	ifstream fileRu(RU);
	while (getline(fileEn, en)) {
		getline(fileRu, ru);
		AddBranch(en, ru, 0, nextBranch);
	}
	fileEn.close();
	fileRu.close();
}

Node* MaxRequest(Node *nextBranch) {//поиск адреса компоненты с максимальным счетчиком обращений

	if (nextBranch == nullptr) {
		return nextBranch;
	}
	else
	{
		MaxRequest(nextBranch->leftBranch);
		MaxRequest(nextBranch->rightBranch);

		if (nextBranch->request >= max) {
			max = nextBranch->request;
			temp = nextBranch;
			return temp;
		}
	}
}

void TreeSorting(Node *& nextBranch, Node *& nextBranchS) {//заполнение отсортированного словаря
	MaxRequest(nextBranch);
	if (temp->request == -1) {
		delete nextBranch;
		nextBranch = nullptr;
		return;
	}
	AddBranch(temp->EnWord, temp->RuWord, temp->request, nextBranchS);
	temp->request = -1;
	max = -1;
	TreeSorting(nextBranch, nextBranchS);
}

void Copying(Node * nextBranch, Node *& copyNode) {
	if (nextBranch == nullptr) {
		return;
	}
	else
	{
		AddBranch(nextBranch->EnWord, nextBranch->RuWord, nextBranch->request, copyNode);
		if (nextBranch->leftBranch != nullptr) {
			Copying(nextBranch->leftBranch, copyNode);
		}
		if (nextBranch->rightBranch != nullptr) {
			Copying(nextBranch->rightBranch, copyNode);
		}
	}
}

void ShowTree(Node * node) {
	if (node == nullptr) {
		return;
	}
	cout << node->EnWord << "   =   " << node->RuWord <<" :: "<<node->request<<endl;
	if (node->leftBranch != nullptr) {
		ShowTree(node->leftBranch);
	}
	if (node->rightBranch != nullptr) {
		ShowTree(node->rightBranch);
	}
}

bool CheckEn(char en[]) {
	bool pass = false;
	for (int i = 0; i < strlen(en); i++) {
		if (en[i] < 65 && en[i] != 32 || en[i] > 122 || (en[i] > 90 && en[i] < 97)) {
			pass = true;
			break;
		}
	}
	return pass;
}

bool CheckRu(char ru[]) {
	bool pass = false;
	for (int i = 0; i < strlen(ru); i++) {
		if (ru[i] > -1 && ru[i] != 32 || ru[i] < -65) {
			pass = true;
			break;
		}
	}
	return pass;
}

bool CheckInt(char menu[]) {
	bool pass = true;
	for (int i = 0; i < strlen(menu); i++) {
		if (strlen(menu) >= 2) {
			cout << "Неверный ввод" << endl;
			break;
		}
		if (menu[i] < 48 || menu[i] > 57) {
			cout << "Неверный ввод" << endl;
			break;
		}
		else {
			pass = false;
		}
	}
	return pass;
}