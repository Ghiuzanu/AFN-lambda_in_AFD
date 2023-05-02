#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

ifstream fin("input.in");
ofstream fout("output.out");

int main() {
    int nrStariFinale, nrMuchii, nrMuchiiNFA;
    vector<int> StariFinale;
    fin>>nrStariFinale;
    for (int i = 0; i < nrStariFinale; ++i) {
        int x;
        fin>>x;
        StariFinale.push_back(x);
    }
    fin>>nrMuchii;
    vector<vector<pair<char, int>>> Muchii(nrMuchii), MuchiiInverse(nrMuchii), MuchiiNFA(12);
    for (int i = 0; i < nrMuchii; ++i) {
        int x, z;
        char y;
        fin>>x>>y>>z;
        Muchii[x].push_back(make_pair(y,z));
        MuchiiInverse[z].push_back(make_pair(y, x));
    }
//    for (int i = 0; i < Muchii.size(); ++i) {
//        for (int j = 0; j < Muchii[i].size(); ++j) {
//            cout<<i<<' '<<Muchii[i][j].first<<' '<<Muchii[i][j].second<<endl;
//        }
//    }
    int ok, aux;
    for (int i = 0; i < nrStariFinale; ++i) {
        for (int j = 0; j < MuchiiInverse[StariFinale[i]].size(); ++j) {
            if (MuchiiInverse[StariFinale[i]][j].first == '0'){
                ok = 1;
                for (int k = 0; k < nrStariFinale; ++k) {
                    if (StariFinale[k] == MuchiiInverse[StariFinale[i]][j].second){
                        ok = 0;
                        break;
                    }
                }
            }
            if (ok == 1){
//                cout<<StariFinale[i]<<' '<<MuchiiInverse[StariFinale[i]][j].first<<' '<<MuchiiInverse[StariFinale[i]][j].second<<endl;
                aux = StariFinale[i];
                nrStariFinale++;
                StariFinale.push_back(MuchiiInverse[aux][j].second);
                i = -1;
                break;
            }
        }
    }
//    for (int i = 0; i < nrStariFinale; ++i) {
//        cout<<StariFinale[i]<<endl;
//    }
    vector<vector<int>> MuchiiRezolvate(20);
//    for (int i = 0; i < Muchii.size(); ++i) {
//        for (int j = 0; j < Muchii[i].size(); ++j) {
//            if (Muchii[i][j].first == '0'){
//                int to = Muchii[i][j].second;
//                for (int k = 0; k < Muchii[to].size(); ++k) {
//                    if (Muchii[to][k].first == '0'){
//                        ok = 0;
//                        if (MuchiiRezolvate.size()){
//                            for (int l = 0; l < MuchiiRezolvate[i].size(); ++l) {
//                                if (Muchii[to][k] == MuchiiRezolvate[i][l]){
//                                    ok = 1;
//                                    break;
//                                }
//                            }
//                        }
//                        if (ok == 0){
//                            Muchii[i].push_back(make_pair(Muchii[to][k].first, Muchii[to][k].second));
//                        }
//                    }
//                    else{
//                        Muchii[i].push_back(make_pair(Muchii[to][k].first, Muchii[to][k].second));
//                    }
//                }
//                MuchiiRezolvate[i].push_back(make_pair(Muchii[i][j].first, Muchii[i][j].second));
//            }
//            else{
//                MuchiiNFA[i].push_back(make_pair(Muchii[i][j].first, Muchii[i][j].second));
//            }
//        }
//    }
    for (int a1 = 0; a1 < Muchii.size(); ++a1) {
        for (int a2 = 0; a2 < Muchii[a1].size(); ++a2) {
            if (Muchii[a1][a2].first == '0'){
                int b1 = Muchii[a1][a2].second;
                for (int b2 = 0; b2 < Muchii[b1].size(); ++b2) {
                    if (Muchii[b1][b2].first == '0'){
                        ok = 0;
                        for (int r = 0; r < MuchiiRezolvate[a1].size(); ++r) {
                            if (Muchii[b1][b2].second == MuchiiRezolvate[a1][r]){
                                ok = 1;
                                break;
                            }
                        }
                        if (ok == 0){
                            Muchii[a1].push_back(make_pair(Muchii[b1][b2].first, Muchii[b1][b2].second));
                        }
                    }
                    else{
                        Muchii[a1].push_back(make_pair(Muchii[b1][b2].first, Muchii[b1][b2].second));
                    }
                }
                MuchiiRezolvate[a1].push_back( Muchii[a1][a2].second);
//                cout<<a1<<' '<<Muchii[a1][a2].first<<' '<<Muchii[a1][a2].second<<endl;
//                cout<<endl;
//                for (int i = 0; i < MuchiiRezolvate.size(); ++i) {
//                    for (int j = 0; j < MuchiiRezolvate[i].size(); ++j) {
//                        cout<<i<<' '<<MuchiiRezolvate[i][j].first<<' '<<Muchii[i][j].second<<endl;
//                    }
//                }
//                cout<<endl;
            }
            else{
                ok = 1;
                for (int i = 0; i < MuchiiRezolvate[a1].size(); ++i) {
                    if (Muchii[a1][a2].second == MuchiiRezolvate[a1][i]) {
                        ok = 0;
                        break;
                    }
                }
                if (ok == 1){
                    MuchiiNFA[a1].push_back(make_pair(Muchii[a1][a2].first, Muchii[a1][a2].second));
                }
            }
        }
    }
//    cout<<endl;
//    for (int i = 0; i < MuchiiNFA.size(); ++i) {
//        for (int j = 0; j < MuchiiNFA[i].size(); ++j) {
//            cout<<i<<' '<<MuchiiNFA[i][j].first<<' '<<MuchiiNFA[i][j].second<<endl;
//        }
//    }
    vector<int> viz(MuchiiNFA.size(), 0);
    for (int i = 0; i < MuchiiNFA.size(); ++i) {
        for (int j = 0; j < MuchiiNFA[i].size(); ++j) {
            viz[MuchiiNFA[i][j].second] = 1;
        }
    }
    for (int i = 1; i < viz.size(); ++i) {
        if (viz[i] == 0){
            MuchiiNFA[i].resize(0);
        }
    }
//    cout<<endl;
//    for (int i = 0; i < MuchiiNFA.size(); ++i) {
//        for (int j = 0; j < MuchiiNFA[i].size(); ++j) {
//            cout<<i<<' '<<MuchiiNFA[i][j].first<<' '<<MuchiiNFA[i][j].second<<endl;
//        }
//    }
    vector<vector<pair<char, int>>> NFAInvers(20);
    for (int i = 0; i < MuchiiNFA.size(); ++i) {
        for (int j = 0; j < MuchiiNFA[i].size(); ++j) {
            NFAInvers[MuchiiNFA[i][j].second].push_back(make_pair(MuchiiNFA[i][j].first, i));
        }
    }
    queue<vector<int>> neVerificat;
    vector<int> aparitii, curent;
    vector<char> cineAparitii;
    vector<int> v = {0};
    int k = -1;
    vector<vector<int>> careMaiExact(0), NeVv(0), Transformare(0);
    vector<vector<pair<char, int>>> DFA(20);
    for (int i = 0; i < MuchiiNFA.size(); ++i) {
        if (MuchiiNFA[i].size()){
            neVerificat.push({i});
            NeVv.push_back({i});
        }
    }
    for (int i = 0; i < MuchiiNFA.size(); ++i) {
//        cout<<MuchiiNFA[i].size()<<" = "<<NFAInvers[i].size()<<endl;
        if (MuchiiNFA[i].empty() && NFAInvers[i].empty()){
            NeVv.push_back({i});
        }
    }
    while (!neVerificat.empty()){
//        for (int i = 0; i < neVerificat.front().size(); ++i) {
//            cout<<neVerificat.front()[i];
//        }
//        cout<<' ';
        aparitii.resize(0);
        cineAparitii.resize(0);
        careMaiExact.resize(0);
        curent = neVerificat.front();
        for (int i = 0; i < curent.size(); ++i) {
            int c = curent[i];
            for (int j = 0; j < MuchiiNFA[c].size(); ++j) {
                ok = 1;
                for (int k = 0; k < cineAparitii.size(); ++k) {
                    if (cineAparitii[k] == MuchiiNFA[c][j].first){
                        ok = 0;
                        aparitii[k]++;
                        careMaiExact[k].push_back(MuchiiNFA[c][j].second);
                        sort(careMaiExact[k].begin(), careMaiExact[k].end());
                        break;
                    }
                }
                if (ok == 1){
                    cineAparitii.push_back(MuchiiNFA[c][j].first);
                    aparitii.push_back(1);
                    careMaiExact.push_back({MuchiiNFA[c][j].second});
                }
            }
        }
//        for (int i = 0; i < careMaiExact.size(); ++i) {
//            cout<<' ';
//            for (int j = 0; j < careMaiExact[i].size(); ++j) {
//                cout<<careMaiExact[i][j];
//            }
//        }

        for (int i = 0; i < careMaiExact.size(); ++i) {
            if (!careMaiExact[i].empty()){
                ok = 1;
                for (int j = 0; j < NeVv.size(); ++j) {
//                    for (int l = 0; l < NeVv[j].size(); ++l) {
//                        cout<<NeVv[j][l];
//                    }
//                    cout<<" = ";
//                    for (int l = 0; l < careMaiExact[i].size(); ++l) {
//                        cout<<careMaiExact[i][l];
//                    }
//                    cout<<"   ";
                    if (NeVv[j] == careMaiExact[i]){
//                        cout<<"  a intrat  ";
                        ok = 0;
                        break;
                    }
                }
                if (ok == 1 && careMaiExact[i].size() > 1){
                    NeVv.push_back(careMaiExact[i]);
                    neVerificat.push(careMaiExact[i]);
                }
            }
            if (ok == 1 && careMaiExact[i].size() > 1){
                for (int j = 0; j < MuchiiNFA.size(); ++j) {
                    if (MuchiiNFA[j].empty() && NFAInvers[j].empty()){
//                        cout<<j<<' ';
                        Transformare.push_back({j});
                        Transformare.push_back({careMaiExact[i]});
                        NFAInvers[j].push_back(make_pair('0', 1));
                        if (curent.size() > 1){
                            for (int k = 1; k < Transformare.size(); k += 2) {
                                if (Transformare[k] == curent){
                                    DFA[Transformare[k - 1][0]].push_back(make_pair(cineAparitii[i], j));
                                    break;
                                }
                            }
                        }
                        else{
                            DFA[curent[0]].push_back(make_pair(cineAparitii[i], j));
                        }
                        break;
                    }
                }
            }
            else{
                if (curent.size() > 1){
                    for (int j = 1; j < Transformare.size(); j += 2) {
//                        for (int l = 0; l < Transformare[j].size(); ++l) {
//                            cout<<Transformare[j][l];
//                        }
//                        cout<<" = ";
//                        for (int l = 0; l < curent.size(); ++l) {
//                            cout<<curent[l];
//                        }
//                        cout<<endl;
                        if (Transformare[j] == curent){
//                            cout<<1;
                            if (careMaiExact[i].size() > 1){
//                                cout<<1;
                                for (int k = 1; k < Transformare.size(); k += 2) {
                                    if (Transformare[k] == careMaiExact[i]){
                                        DFA[Transformare[j - 1][0]].push_back(make_pair(cineAparitii[i], Transformare[k - 1][0]));
                                        break;
                                    }
                                }
                            }
                            else{
//                                cout<<1;
                                DFA[Transformare[j - 1][0]].push_back(make_pair(cineAparitii[i], careMaiExact[i][0]));
                            }
                            break;
                        }
                    }
                }
                else if (careMaiExact.size() > 1){
                    for (int k = 1; k < Transformare.size(); k += 2) {
                        if (Transformare[k] == careMaiExact[i]){
//                            cout<<curent[0]<<' '<<i;
                            DFA[curent[0]].push_back(make_pair(cineAparitii[i], Transformare[k - 1][0]));
                            break;
                        }
                    }
                }
                else{
                    DFA[curent[0]].push_back(make_pair(cineAparitii[i], careMaiExact[i][0]));
                }
            }
        }
        neVerificat.pop();
        curent.resize(0);
//        cout<<endl<<endl;
    }
    cout<<endl;
    for (int i = 0; i < DFA.size(); ++i) {
        for (int j = 0; j < Transformare.size(); j += 2) {
            if (i == Transformare[j][0]){
                for (int l = 0; l < Transformare[j + 1].size(); ++l) {
                    for (int m = 0; m < StariFinale.size(); ++m) {
                        if (StariFinale[m] == Transformare[j + 1][l]){
                            StariFinale.push_back(Transformare[j][0]);
                        }
                    }
                }
            }
        }
    }
//    for (int i = 0; i < NeVv.size(); ++i) {
//        for (int j = 0; j < NeVv[i].size(); ++j) {
//            cout<<NeVv[i][j];
//        }
//        cout<<endl;
//    }
//    cout<<DFA.size()<<endl;
    cout<<"Muchiile DFA-ului:\n";
    for (int i = 0; i < DFA.size(); ++i) {
        for (int j = 0; j < DFA[i].size(); ++j) {
            cout<<i<<' '<<DFA[i][j].first<<' '<<DFA[i][j].second<<endl;
        }
    }
    cout<<"\nStarile finale a DFA-ului:\n";
    for (int i = 0; i < StariFinale.size(); ++i) {
        cout<<StariFinale[i]<<' ';
    }
    cout<<"\n\nTransformari:\n";
    for (int i = 0; i < Transformare.size(); i += 2) {
        cout<< Transformare[i][0] << " <- ";
        for (int j = 0; j < Transformare[i + 1].size(); j++) {
            cout<<Transformare[i + 1][j];
        }
        cout<<endl;
    }
    return 0;
}
