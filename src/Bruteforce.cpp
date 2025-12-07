#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<limits>
#include<fstream>

using namespace std;

double maxDouble = numeric_limits<double>::max();

double distance(const pair<double, double> &c1, const pair<double, double> &c2){  
    return sqrt(pow(c1.first - c2.first , 2) + pow(c1.second - c2.second , 2));
}

void bruteForce(const vector<pair<double,double>> &cities , bool print_file){
    vector<vector<double>> mat;
    vector<double> row(cities.size() , 0);

    vector<int> save;

    double minC = maxDouble;

    for(unsigned int i = 0 ; i < cities.size() ; i++){
        for(unsigned int j = 0 ; j < i ; j++)
            row[j] = mat[j][i];

        row[i] = 0;

        for(unsigned int j = i+1 ; j < cities.size() ; j++)
            row[j] = distance(cities[i] , cities[j]);

        mat.push_back(row);
    }

    vector<int> tmp(cities.size() , 0);

    for(unsigned int i = 1 ; i < tmp.size() ; i++)
        tmp[i] = i;

    do{
        if(tmp[1] > tmp.back() )
            continue;

        double cost = mat[tmp[0]][tmp.back()];

        for(unsigned int i = 1 ; i < tmp.size() ; i++)
            cost += mat[tmp[i]][tmp[i-1]];

        if(cost < minC){
            minC = cost;
            save = tmp;
        }
    }while(next_permutation(tmp.begin()+1 , tmp.end()));

    cout << "Brute Force: ";

    for(auto &i : save)
        cout << i << ' ';

    cout << endl;

    if(print_file){
        ofstream fout("dat/paths.dat");

        for(auto &i : save)
            fout << i << ' ';
            
        fout << endl;

        fout.close();
    }
    
    return;
}