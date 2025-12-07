#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<limits>
#include<queue>

using namespace std;

double infty = numeric_limits<double>::infinity();

class Node{
    public:
        Node(unsigned int key):key{key}{;}
        ~Node(){;}

        void add(Node* branch){return branchs.push_back(branch);}
        Node* operator[](unsigned int i) const{return branchs[i];}
        unsigned int size(void) const{return branchs.size();}

        unsigned int operator()(void){return key;}
    private:
        unsigned int key;
        vector<Node*> branchs;
};

class MST {
    public:
        MST(const vector<pair<double , double>>* cities):
            root{new Node(0)},
            arr{vector<Node*>(cities->size(), nullptr)}
        {
            unsigned int n = cities->size();
            arr[0] = root;
            
            // Computing the cost (length) of each eadge
            vector<vector<double>> cost(n, vector<double>(n));
            for (unsigned int i = 0; i < n; ++i) {
                for (unsigned int j = 0; j < i ; j++)
                    cost[i][j] = cost[j][i];
                
                cost[i][i] = infty;

                for (unsigned int j = i+1; j < n; j++) {
                    double dx = (*cities)[i].first - (*cities)[j].first;
                    double dy = (*cities)[i].second - (*cities)[j].second;
                    cost[i][j] = sqrt(dx * dx + dy * dy);
                }
            }

            vector<double> minDist(n, 0.);  // Minimum distance to one node of the MST
            vector<int> parent(n, -1);      // Closest node of the MST for each node

            minDist[0] = -1;

            for (unsigned int v = 1; v < n; ++v) {
                minDist[v] = cost[0][v];
                parent[v] = 0;
            }

            for (unsigned int i = 0; i < n-1; ++i) {
                double min = infty;
                int u = -1;
                // Find the closest 
                for (unsigned int j = 0; j < n; ++j) {
                    if (0 < minDist[j] && minDist[j] < min) {
                        min = minDist[j];
                        u = j;
                    }
                }

                minDist[u] = -1;   // Save the node has already been added

                // Add the node to the MST
                if (parent[u] != -1) {
                    Node* parentNode = arr[parent[u]];
                    arr[u] = new Node(u);
                    parentNode->add(arr[u]);
                }

                // Update the distances
                for (unsigned int v = 0; v < n; ++v) {
                    if (cost[u][v] < minDist[v]) {
                        minDist[v] = cost[u][v];
                        parent[v] = u;
                    }
                }
            }

            printEdges();
        }

        ~MST(){
            clear(root);
        }

        bool empty(void) const {
            return root == nullptr;
        }

        void print(Node* node, int depth = 0 , ostream& os = cout) const {
            if (!node)
                return;
            
            for (int i = 0; i < depth; ++i)
                os << "  ";
            
            os << (*node)() << "\n";

            for (unsigned int i = 0; i < node->size(); ++i) {
                print((*node)[i], depth + 1 , os);
            }
        }

        void path(bool print_file) const {
            cout << "Prim's MST : ";
            path(root);
            cout << endl;

            if(print_file){
                ofstream fout("dat/paths.dat" , std::ios::app);

                path(root , fout);
                fout << endl;

                fout.close();
            }
        }

        void printEdges(void) const {
            ofstream fout("dat/edges.dat");
            printEdges(root , fout);

            fout.close();
        }
    private:
        Node* root;
        vector<Node*> arr;

        void clear(Node* node) {
            if (!node) return;
            for (unsigned int i = 0; i < node->size(); ++i) {
                clear((*node)[i]);
            }
            delete node;
        }

        void path(Node* n , ostream& os = cout) const{
            os  << (*n)() << " ";
            for(unsigned int i = 0 ; i < n->size() ; i++)
                path((*n)[i] , os);
        }

        void printEdges(Node* n, ofstream& fout) const {
            for (unsigned int i = 0; i < n->size(); ++i) {
                Node* child = (*n)[i];
                fout << (*n)() << " " << (*child)() << endl;
                printEdges(child, fout);
            }
        }
};
