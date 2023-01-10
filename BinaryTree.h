#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class BinaryTree {
public:
    void setDepth(int depth) {
        if (depth < _depth) { // on supprime toutes les valeurs apr�s 
            _tree.resize(depth + 1);
        }
        else {
            for (int i = _depth; i < depth; i++) {//on rajoute un vecteur de taille+1 � chaque it�ration
                vector<T> vec;
                vec = vector<T>(i + 1 + 1);
                _tree.push_back(vec);
            }
        }
        _depth = depth;
    };

    void setNode(int i, int j, T val) {  //set une valeur � un noeud
        _tree[i][j] = val;
    };

    T getNode(int i, int j) { return _tree[i][j]; };  //acceder � un noeud

    void display() {   //affichage
        for (int i = 0; i < _tree.size(); i++) {
            for (int j = 0; j < _tree[i].size(); j++) {
                cout << _tree[i][j] << "  ";
            }
            cout << endl;
        }
        cout << endl;
        displaybis();
    };


    void disp(int n) {      //affichage ++
        for (int i = 0; i < n; i++) {
            cout << " ";
        }
    }

    void slash(int n) {
        for (int i = 0; i < n; i++) {
            cout << "/ \\ ";
        }
        cout << endl;
    }

    void displaybis() {
        int n_spaces = _tree.size() * 2;
        for (int i = 0; i < _tree.size(); i++) {
            disp(n_spaces - 2 * i - 1);
            for (int j = 0; j < _tree[i].size(); j++) {
                cout << _tree[i][j];
                disp(3);
            }
            cout << endl;
            if (i < _tree.size() - 1) {
                disp(n_spaces - 2 * i - 2);
                slash(_tree[i].size());
            }
        }
        cout << endl;
    }

private:
    vector<vector<T> > _tree;
    int _depth = -1; //size of the tree  //en indice
};