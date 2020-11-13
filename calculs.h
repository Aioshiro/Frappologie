#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <math.h>
using namespace std;

double moyenneVect(vector<double> vecteurInit); //calcule la moyenne d'un vecteur

double varianceVect(vector<double> vecteurInit); //calcule la variance d'un vecteur

double CalcScore(vector<double> vecteurInit, double valeur);

double norme(vector<double> v); //calcule la norme d'un vecteur

vector<vector <double>> calculL(int n, vector<double> infos);
vector<vector <double>> inversionL(vector<vector <double>> L, int n);
vector<double> produitmatricevec(vector<double> X, vector<vector<double>> M);

void lecture(vector<vector<double>> L);
