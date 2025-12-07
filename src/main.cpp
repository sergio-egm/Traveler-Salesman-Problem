#include<iostream>
#include<fstream>
#include<vector>
#include<ctime>
#include"Bruteforce.cpp"
#include"MST.cpp"

using namespace std;

vector<pair<double,double>> random(unsigned int N);
void run(vector<pair<double , double>> &cities , bool print_file);

int main(int argc , char** argv){
    int print_file = 0;
    if(argc < 2){
        cerr << "ERROR: Number of cities not specified!" << endl;
        return -1; 
    }
    else if(argc > 2)
        print_file = atoi(argv[2]);

    vector<pair<double,double>> cities = random(atoi(argv[1]));
    run(cities , print_file);
    
    return 0;
}

vector<pair<double, double>> random(unsigned int N){
    vector<pair<double, double>> res;
    srand(3);

    ofstream fout("dat/cities.dat");

    for(unsigned int i = 0 ; i < N ; i++){
        res.push_back(pair<double,double>((double) (rand())/RAND_MAX ,  (double) (rand())/RAND_MAX));

        fout << res[i].first << ' ' << res[i].second << endl;
    }

    fout.close();

    return res;
}

void run(vector<pair<double, double>> &cities , bool print_file){
    bruteForce(cities , print_file);
    MST mst(&cities , print_file);

    mst.path();
}
