/*
* Implementacao DES
* Autores : Leonardo Muniz Tozato - Felipe Lopes Rita
* RA : 620483 - 613762
*/

#include <bits/stdc++.h>
using namespace std;
#define printhex(x) cout<< hex << x <<endl
#define rep(i,s,N) for(int i=s;i<N;i++)
#define repi(i,s,N) for(int i=s;i<=N;i++)
typedef long long ll;
typedef unsigned long long ull;
typedef bitset<32> bi;

//Todas as S-Box ficam concatenadas
int Sbox[512]={
        14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
		0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
		4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
		15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,
		15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
		3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
		0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
		13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,
		10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
		13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
		13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
		1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,
		7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
		13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
		10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
		3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,
		2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
		14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
		4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
		11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,
		12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
		10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
		9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
		4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,
		4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
		13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,			
		1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
		6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,
		13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
		1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
		7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
		2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
    };

//Le a mensagem em caracteres acsii e converte para um long long que representa a cadeia de bits da mensagem.
ll read(){
    ll buffer = 0;
    char digit;

    rep(i, 0, 8) {
        scanf("%c", &digit);
        //Vai juntando os caracteres convertendo para long long e deslocando bits.
        buffer += ((ll) digit<<((7-i)*8));
    }
    scanf("%c", &digit);
    
    return buffer;
}

//Auxilia na exibição de resultados, printando uma mensagem junto do texto em hexa maisculo, 
//completando com 0s quando necessário
void print(string message, ll value, int offset = 16){
    cout << message << endl;
    stringstream ss;
    ss << hex << uppercase << value;
    string s = ss.str();
    rep(i, s.size(), offset) printf("%c", '0');
    cout << s << endl;    
}

void IP(ll &msg){
    //Tabela de indices para permutar a mensagem.
    int map[64]={
        58,50,42,34,26,18,10,2,
        60,52,44,36,28,20,12,4,
        62,54,46,38,30,22,14,6,
        64,56,48,40,32,24,16,8,
        57,49,41,33,25,17,9,1,
        59,51,43,35,27,19,11,3,
        61,53,45,37,29,21,13,5,
        63,55,47,39,31,23,15,7
    };

    //Auxiliares para permutação de mensagem
    bitset<64> bitMsg(msg);
    bitset<64> bitIP(0);

    //Efetua a permutação inicial de fato
    rep(i, 0, 64) bitIP.set(63 - i, bitMsg[64 - map[i]]);
    msg = bitIP.to_ullong();
}

void inverseIP(ll &msg){
    //Tabela de indices para permutar a mensagem.
    int map[64]={
        40,8,48,16,56,24,64,32,
        39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,
        37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,
        35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,
        33,1,41,9,49,17,57,25
    };

    //Auxiliares para permutação de mensagem
    bitset<64> bitMsg(msg);
    bitset<64> bitIP(0);

    //Efetua a permutação inicial de fato
    rep(i, 0, 64) bitIP.set(63 - i, bitMsg[64 - map[i]]);
    msg = bitIP.to_ullong();
}


void PC1(ll &key){
    //Tabela de indices para permutar a chave.
    int map[56]={
        57,49,41,33,25,17,9,
        1,58,50,42,34,26,18,
        10,2,59,51,43,35,27,
        19,11,3,60,52,44,36,
        63,55,47,39,31,23,15,
        7,62,54,46,38,30,22,
        14,6,61,53,45,37,29,
        21,13,5,28,20,12,4
    };

    //Auxiliares para permutação de chave
    bitset<64> bitkey(key);
    bitset<56> bitPC(0);

    //Efetua a permutação escolhida 1 de fato
    rep(i, 0, 56) bitPC.set(55 - i, bitkey[64 - map[i]]);
    key = bitPC.to_ullong();
}


//Faz o circular left shift das metades de chave
void rotate(bitset<28>& b){
    b = b << 1 | b >> 27;
}

void PC2(ull& key){
    int map[48]={
        14,17,11,24,1,5,3,28,
        15,6,21,10,23,19,12,4,
        26,8,16,7,27,20,13,2,
        41,52,31,37,47,55,30,40,
        51,45,33,48,44,49,39,56,
        34,53,46,42,50,36,29,32
	};

    //Auxiliares para permutação de chave
    bitset<56> bitkey(key);
    bitset<48> bitPC(0);

    //Efetua a permutação escolhida 2 de fato
    rep(i, 0, 48) bitPC.set(47 - i, bitkey[56 - map[i]]);
    key = bitPC.to_ullong();
}

//Função de expansao
ll E(int msgR){
    bitset<32> bitR(msgR);
    bitset<48> bitE(0);
    int map[48]={
        32,1,2,3,4,5,4,5,
        6,7,8,9,8,9,10,11,
        12,13,12,13,14,15,16,17,
        16,17,18,19,20,21,20,21,
        22,23,24,25,24,25,26,27,
        28,29,28,29,30,31,32,1
    };
    
    rep(i, 0, 48) bitE.set(47 - i, bitR[32 - map[i]]);
    return bitE.to_ullong();
}

//Encontra o índice adequado na super S-box a partir dos valores dos bits, retornando o valor naquele indice.  
unsigned getBox(unsigned sindex, int i){
    bitset<6> bits(sindex);
    bitset<2> row(0);
    bitset<4> column((sindex << 27 >> 28));
    row.set(1, bits[5]);
    row.set(0, bits[0]);

    return Sbox[(8 - i)*64+row.to_ulong()*16+column.to_ulong()];
    
}

int P(int value){
    bitset<32> b(value);
    bitset<32> p(0);

    int map[32] = { 
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };

    rep(i, 0, 32) p.set(31 - i, b[32 - map[i]]);
    return (int) p.to_ulong();
}

//Executa a parte da função F
int F(int r, ll key){
    ll expMsg = E(r);
    print("Expancao:", expMsg, 12);
    expMsg = expMsg ^ key;
    print("Add Key:", expMsg, 12);
    unsigned boxValue = 0;
    for(int i = 8; i >= 1; i--){
        boxValue = boxValue << 4;
        boxValue += getBox(((unsigned long) expMsg << (64 - i * 6) >> 58), i) ;
    }
    print("S-Box:", boxValue, 8);
    int last = P(boxValue);
    print("Permuta:", last, 8);
    return last;
}

//Função que faz a cifragem, controlando e chamando as outras funções
void encrypt(ll msg, ll key){
    IP(msg);
    print("IP", msg);

    PC1(key);
    print("PC1 - SELECIONA CHAVE", key, 14);

    ull shiftedKey = key;
    bitset<28> bR(shiftedKey);
    bitset<28> bL(shiftedKey >> 28);
    ll msgSwap;
    repi(i, 1, 16) {
        printf("CHAVE DE ROUND %d\n", i);
        
        //Faz o deslocamento circular a esquerda da chave para o round.  
        rotate(bL);
        rotate(bR);
        if (i != 1 && i!=2 && i!=9 && i!=16) {
            rotate(bL);
            rotate(bR);
        }
        cout << hex << bL.to_ullong() << endl;
        shiftedKey = (bL.to_ullong() << 28) | (bR.to_ullong());
        print("Deslocamento:", shiftedKey, 14);

        //Faz a PC2 para a sub-chave de round gerada
        PC2(shiftedKey);
        print("PC2:", shiftedKey, 12);

        printf("ROUND %d\n", i);
        print("MENSAGEM ATUAL", msg);

        unsigned msgR = (int) msg;
        unsigned roundMsgL = (int) (msg>>32);
        unsigned msgL = msgR;
        msgR = roundMsgL ^ F(msgR, shiftedKey);
        print("Add Left:", msgR, 8);

        msg = ((ll) msgL << 32) | ((ll)msgR);
        print("MENSAGEM ATUAL", msg);
        msgSwap = ((ll) msgR << 32) | ((ll)msgL);
    }

    print("SWAP", msgSwap);
    inverseIP(msgSwap);
    print("IP Inverso:", msgSwap);
}

int main(){
    ll msg = read();
    ll key = read(); 

    print("PLAIN TEXT", msg);
    print("CHAVE", key);
    

    encrypt(msg, key);

    return 0;
}
