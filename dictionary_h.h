#include <iostream>
#include <string>
#include <fstream>

using namespace std;
struct Node;
Node* MaxRequest(Node * nextBranch);
void AddBranch(string EnWord, string RuWord, int request, Node *& nextBranch);
void ShowTree(Node * node);
void DeleteTree(Node *& nextBranch);
void Dictionary(Node *& nextBranch);
void TreeSorting(Node *& nextBranch, Node *& nextBranchS);
void Copying(Node * nextBranch, Node *& sortedNode);
bool Find(string findWord, Node *nextBranch, bool success);
bool CheckEn(char en[]);
bool CheckRu(char ru[]);
bool CheckInt(char menu[]);