#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void heapPermutation(string &s, int size, int n, vector<string> *v) {
    if (size == 1) {
        v->push_back(s);
        return;
    }
    for (int i = 0; i < size; i++) {
        heapPermutation(s, size - 1, n, v);
        if (size % 2 == 1)
            swap(s[0], s[size - 1]);
        else
            swap(s[i], s[size - 1]);
    }
}

/**
 * Najde vsechny mozne retezce, ktere lze vytvorit ze znaku
 * vstupniho retezce tak, ze se pouzije kazdy znak prave jednou.
 *
 * @param s Retezec tvoreny znaky, ktere se maji vyskytovat v hledanem retezci (hesle)
 * @param v Ukazatel na vektor, do nehoz funkce prida vsechny mozne kandidaty na hledane heslo
 *
 */
void generate_candidates(string s, vector<string>* v) {
    heapPermutation(s, s.length(), s.length(), v);
}


int main(int argc, char** argv)
{
    if(argc < 2){
        cerr << "Missing arguments" << endl;
        exit(-1);
    }
    auto v = new vector<string>;
    string s = argv[1];
    generate_candidates(s,v);
    sort(v->begin(), v->end());
    for(unsigned int i = 1; i<=v->size(); i++){
        cout << (*v)[i-1] << ((i%10 == 0)?'\n':' ');
    }
    delete v;
    return 1;
}