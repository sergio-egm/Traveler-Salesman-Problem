#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include"Bruteforce.cpp"
#include"MST.cpp"

using namespace std;

vector<pair<double,double>> random(unsigned int N);
void run(vector<pair<double , double>> &cities);

int main(int argc , char** argv){
    if(argc < 2){
        cerr << "ERROR: Number of cities not specified!" << endl;
        return -1; 
    }

    vector<pair<double,double>> cities = random(atoi(argv[1]));
    run(cities);
    
    return 0;
}

vector<pair<double, double>> random(unsigned int N){
    vector<pair<double, double>> res;
    srand(3);

    ofstream fout("cities.dat");

    for(unsigned int i = 0 ; i < N ; i++){
        res.push_back(pair<double,double>((double) (rand())/RAND_MAX ,  (double) (rand())/RAND_MAX));

        fout << res[i].first << ' ' << res[i].second << endl;
    }

    fout.close();

    return res;
}

void run(vector<pair<double, double>> &cities){
    bruteForce(cities);
    MST mst(&cities);

    mst.path();
}
