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

	void print(Tree* leaf) {
		if (leaf) {
			print(leaf->left);
			cout << "Индекс: " << leaf->student.index << "\n";
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

	}
};