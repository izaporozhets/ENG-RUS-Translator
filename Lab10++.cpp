#include "pch.h"
#include <windows.h>
#include "dictionary_h.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE  hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD  size;
	size.X = 20;     // кол-во символов на строку
	size.Y = 3000;  // увеличиваем до 3000 строк
	SetConsoleScreenBufferSize(hout, size);

	Node* root = nullptr;
	Node* rootSorted = nullptr;
	Node* rootCopy = nullptr;
	setlocale(LC_ALL, "rus");

	string find;
	char en[256];
	char ru[256];
	
	int request;
	int counter = 0;
	bool check = true;
	bool flag = true;

	cout << "Переводчик" << endl << endl;
	cout << "1 - Добавить слово в словарь" << endl;
	cout << "2 - Найти перевод слова и кол-во обращений к нему" << endl;
	cout << "3 - Построить новый словарь и вывести его с исходным" << endl;
	cout << "4 - Подключить словарь из 1000 слов" << endl;
	cout << "5 - Выход" << endl;
	cout << "Выберите опцию: " << endl;

	while (flag) {
		int i = 0;
		bool success = false;
		char menu[256];
		cin.getline(menu,256);
		while (CheckInt(menu)) {
			cin.getline(menu,256);
		}
		int menu1 = atoi(menu);

		switch (menu1)
		{
		case 1:
			cout << "Введите английское слово: " << endl;
			cin.getline(en, 256);
			if (CheckEn(en) == true) {
				cout << "В тексте присутствовали недопустимые символы" << endl;
				break;
			}
			cout << "Введите соотвтветствующее русское слово: " << endl;
			cin.getline(ru, 256);
			if (CheckRu(ru) == true) {
				cout << "В тексте присутствовали недопустимые символы" << endl;
				break;
			}
			cout << "Введите данные для счетчика обращений: " << endl;
			cin >> request;
			AddBranch(en, ru, request, root);
			check = false;
			break;

		case 2:
			if (!root) {
				cout << "Словарь не содержит слов" << endl;
			}
			else {
				cout << "Введите слово, которое нужно перевести: ";
				cin >> find;
				if (Find(find, root, success) == false) {
					cout << "Слово отсутствует" << endl;
				}
			}
			break;
		case 3:
			if (check == false) {
				Copying(root, rootCopy);
				TreeSorting(root, rootSorted);

				cout << endl << "Исходный словарь" << "\n\n";
				if (rootCopy != nullptr) {
					ShowTree(rootCopy);
				}
				cout << endl << "Отсортированный словарь" << "\n\n";
				ShowTree(rootSorted);

				DeleteTree(rootCopy);
				DeleteTree(rootSorted);
				check = true;
			}
			else
			{
				cout << "Старый словарь не содержит элементов" << endl;
			}
			break;
		case 4:
			if (counter == 0) {
				Dictionary(root);
				counter++;
				cout << "Словарь подключен" << endl;
				check = false;
			}
			else {
				cout << "Словарь уже подключен" << endl;
			}
			break;
		case 5:
			cout << "Exited" << endl;
			DeleteTree(root);
			DeleteTree(rootSorted);
			DeleteTree(rootCopy);
			flag = false;
			break;
		default:
			cout << "Неверный ввод" << endl;
			break;
		}
	}
		
}