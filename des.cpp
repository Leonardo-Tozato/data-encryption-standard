/*
* Implementacao DES
* Autores : Leonardo Muniz Tozato - Felipe Lopes Rita
* RA : 620483 - ??????
*/

#include <bits/stdc++.h>
using namespace std;
#define printhex(x) cout<< hex << x <<endl
#define rep(i,s,N) for(int i=s;i<N;i++)
typedef long long ll;

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

void encrypt(ll msg, ll key){
    
}

int main(){
    ll msg = read();
    ll key = read(); 

    printf("Message in hex: %llx\n", msg);
    printf("Key in hex: %llx\n", key);

    encrypt(msg, key);

    return 0;
}