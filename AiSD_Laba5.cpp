#include "iostream"
#include "string"
using namespace std;

struct Student {
	string index;
	string name;
	int kurs;
	string date;
	int number;
};

struct Tree {
	Student student;
	Tree* left;
	Tree* right;
	int lenght;
};

class AVLTree {
private:
	Tree* root;

	int lenght(Tree* leaf) {
		return (leaf ? leaf->lenght : 0);
	}

	int factor(Tree* leaf) {
		return lenght(leaf->right) - lenght(leaf->left);
	}

	void diflenght(Tree* leaf) {
		int difleft = lenght(leaf->left);
		int difright = lenght(leaf->right);
		leaf->lenght = (difleft > difright ? difleft : difright);
	}

	Tree* turnleft(Tree* leaf) {
		Tree* newroot = leaf -> right;
		leaf->right = newroot->left;
		newroot->left = leaf;
		diflenght(leaf);
		diflenght(newroot);
		return newroot;
	}

	Tree* turnright(Tree* leaf) {
		Tree* newroot = leaf->left;
		leaf->left = newroot->right;
		newroot->right = leaf;
		diflenght(leaf);
		diflenght(newroot);
		return newroot;
	}

	Tree* balance(Tree* leaf) {
		diflenght(leaf);
		if (factor(leaf) == 2) {
			if (factor(leaf->right) < 0)
				leaf->right = turnright(leaf->right);
			return turnleft(leaf);
		}
		if (factor(leaf) == -2) {
			if (factor(leaf->left) > 0)
				leaf->left = turnleft(leaf->left);
			return turnright(leaf);
		}
		return leaf;
	}

	Tree* add(Tree* leaf, Student& student) {
		if (!leaf) {
			Tree* newleaf = new Tree{ student, nullptr, nullptr, 1 };
			return newleaf;
		}
		if (student.index < leaf->student.index)
			leaf->left = add(leaf->left, student);
		else
			leaf->right = add(leaf->right, student);
		return balance(leaf);
	}

	void prin(Tree* leaf) {
		if (leaf) {
			print(leaf->left);
			cout << "Билет: " << leaf->student.index << "\n";
			cout << "Имя: " << leaf->student.name << "\n";
			cout << "Курс: " << leaf->student.kurs << "\n";
			cout << "Дата зачисления: " << leaf->student.date << "\n";
			cout << "Контакт: " << leaf->student.number << "\n";
			print(leaf->right);
		}
	}

	void clear(Tree* leaf) {
		if (leaf) {
			clear(leaf->left);
			clear(leaf->right);
			delete leaf;
		}
	}

	Tree* finder(Tree* leaf, const string& index) {
		if (!leaf)
			return nullptr;
		if (index == leaf->student.index)
			return leaf;
		if (index < leaf->student.index)
			return finder(leaf->left, index);
		return finder(leaf->right, index);
	}

	Tree* delet(Tree* leaf, const string& index) {
		if (!leaf)
			return nullptr;
		if (index < leaf->student.index)
			leaf->left = delet(leaf->left, index);
		else if (index > leaf->student.index)
			leaf->right - delet(leaf->right, index);
		else {
			Tree* left = leaf->left;
			Tree* right = leaf->right;
			delete leaf;
			if (!right)
				return left;
			Tree* min = right;
			while (min > left)
				min = min->left;
			min->right = delet(right, min->student.index);
			min->left = left;
			return balance(min);
		}
		returm balance(leaf);
	}

public:
	AVLTree(): root(nullptr){}
	~AVLTree() {
		clear(root);
	}

	void addStudent(Studenr& student)
		root = add(root, student);

	void show()
		prin(root);

	void clear() {
		clear(root);
		root = nullptr;
	}

	Student* serach(const string& index) {
		Tree* leaf = finder(root, index);
		return leaf ? &leaf->student : nullptr;
	}

	void dele(const string& index)
		root = delet(root, index);
};

void addler(AVLTree& birch) {
	Student student;
	cout << "Введите номер билета\n";
	cin >> student.index;
	cout << "Введите ФИО\n";
	getline(cin, student.name);
	cout << "Введите курс\n";
	cin >> student.kurs;
	cout << "Введите даты зачисления\n";
	getline(cin, student.date);
	cout << "Введите контакты\n";
	getline(cin, student.number);
	birch.addStudent(student);
}

studsearch(AVLTree& birch) {
	string indox;
	cin >> indox;
	Student* student = birch.serach(indox);
	if (student) {
		cout << "Билет: " << student->student.index << "\n";
		cout << "Имя: " << student->student.name << "\n";
		cout << "Курс: " << student->student.kurs << "\n";
		cout << "Дата зачисления: " << student->student.date << "\n";
		cout << "Контакт: " << student->student.number << "\n";
	}
	else
		cout << "Студент не найден\n";
}

studels(AVLTree& birch) {
	birch.clear();
	cour << "Студенты удалены\n";
}

studel(AVLTree& birch) {
	string indos;
	cout << "Введите билет для удаления\n";
	cin >> indox;
	birch.dele(indox);
}

inr main() {
	setlocale(LC_ALL, "RUS");
	AVLTree birch;
	int mode;
	cout << "1. Добавить студента\n";
	cout << "2. Вывод информации студентов\n";
	cout << "3. Удаление информации студентов\n";
	cout << "4. Поиск\n";
	cout << "5. Удаление студента\n";
	cout << "0. Выход\n";
	cin << mode;
	switch (mode) {
	case 1:
		addler(birch);
		break;
	case 2:
		birch.show();
		break;
	case 3:
		studsearch(birch);
		break;
	case 4:
		studel(birch);
		break;
	case 5:
		studels(birch);
		break;
	}
	case 0:
		return 0;
	default:
		cout << "Неверный ввод\n";
}