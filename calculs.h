#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <math.h>
using namespace std;

double moyenneVect(vector<double> vecteurInit); //calcule la moyenne d'un vecteur

double varianceVect(vector<double> vecteurInit); //calcule la variance d'un vecteur

double norme(vector<double> v); //calcule la norme d'un vecteur

vector<vector <double>> calculL(int n, vector<double> infos); // calcule la decomposition de cholesky d'une matrice symetrique definie positive de taille n,la matrice étant un vecteur a n^2 entrées
vector<vector <double>> inversionL(vector<vector <double>> L, int n); // inverse une matrice triangulaire inférieure de taille n
vector<double> produitmatricevec(vector<double> X, vector<vector<double>> M); // fait le produit XM

void lecture(vector<vector<double>> L); //affiche le contenu d'une matrice
