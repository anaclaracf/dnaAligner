#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <random>
#include <string>
#include <tuple>

using namespace std;
typedef vector<vector<int>> matrix;

struct max_value{
    string seq;
    int score_max;
};



matrix max_score(matrix H, string first_seq, string second_seq, int k, int w){
    int diagonal, deletion, insertion;
    string seq_max;

    for (int i = 1; i <= k; i++){
        for (int j = 1; j <= k; j++){
            w = first_seq[i] == second_seq[j] ? 2 : -1;

            diagonal = H[i-1][j-1] + w;
            deletion = H[i-1][j] - 1;
            insertion = H[i][j-1] - 1;

            H[i][j] = max({0, diagonal, deletion, insertion});
        }
    }

    return H;
}

int main(){

    ofstream output_file;
    output_file.open ("output");

    int n, m;
    int max_k, k;
    int i, j , p;
    int w = 0;
    string seqA, seqB;
    string new_seqA, new_seqB;
    string sub_seqA, sub_seqB;
    
    
    char first_signal = '-';

    cin >> n >> m;
    cin >> seqA >> seqB;

    // descobrindo qual o maior valor possível para poder aleatoriazar o k
    // escolhendo o tamanho da menor sequencia 
    if(n>=m){
        max_k = m;
    }else{
        max_k = n;
    }

    default_random_engine generator;

    for(int g=0; g < 100; g++){

        vector<max_value> valores_max;

        // calculando o k aleatório
        uniform_int_distribution<int> k_aleatorio(1, max_k);
        k = k_aleatorio(generator);
        // k = 5;

        // calculando o j aleatorio
        uniform_int_distribution<int> j_aleatorio(0, m - k);
        j = j_aleatorio(generator);

        // calculando o i aleatorio 
        uniform_int_distribution<int> i_aleatorio(0, n - k);
        
        // cout << "k = " << k << endl;
        // cout << "j = " << j << endl;
        
        // gerando a subsequencia de b
        sub_seqB = seqB.substr(j, k);

        // gerando um número aleatorio para p
        uniform_int_distribution<int> p_aleatorio(1, n+m);
        p = p_aleatorio(generator);

        // cout << "p = " << p << endl;

        // criando matriz para calculo do max score
        new_seqB = first_signal + sub_seqB;
        matrix H;
        H.resize(k+1);
        for(int e=0; e<=k; e++){
            H[e].resize(k+1);
        }

        // gerando a subsequencia de a
        for(int e = 0; e < p; e++){
            
            max_value highScore;

            i = i_aleatorio(generator);
            sub_seqA = seqA.substr(i, k);
            new_seqA = first_signal + sub_seqA;
            // cout << sub_seqA << " " <<new_seqA << " " << k << endl;
            // calculando os scores de cada alinhamento
            H = max_score(H, new_seqA, new_seqB, k, w);
            int max = 0;
            

            // descobrindo os maiores scores
            for (i = 0; i < k; i++){
                for (j = 0; j < k; j++){
                    if(H[i][j] > max){
                        max = H[i][j];
                    }
                }
            }

            highScore.score_max = max;
            highScore.seq = sub_seqA;
            valores_max.push_back(highScore);
        
        }

        int tamanho_vetor = valores_max.size();
        int score_max = 0;
        string seq_final;

        // atribuindo os scores as sequencias utilizadas
        for (int i = 0; i < tamanho_vetor; i++){
            if(valores_max[i].score_max >= score_max){
                score_max = valores_max[i].score_max;
                seq_final = valores_max[i].seq;
            }
        } 

        cout << "max score: " << score_max << endl;
        cout << "sub sequencia A utilizada: " << seq_final << endl;
        cout << "sub sequencia B utilizada: " << sub_seqB << endl;
        cout << endl;

        

        output_file << "Max Score: "<< score_max << endl;
        output_file << "sub sequencia A utilizada: " << seq_final << endl;
        output_file << "sub sequencia B utilizada: " << sub_seqB << endl;
        output_file << "-----------------------------------" << endl;


    }

    output_file.close();

    


    return 0;
}
