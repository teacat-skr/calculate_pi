#include<bits/stdc++.h>
#include"Nbc.hpp"
void root(Nbc A, Nbc B, Nbc& C, Nbc& D){
    //A/B‚Ì•½•ûª‚ğC/D‚É•Ô‚·ŠÖ”
    C = A;
    D = B;
    Nbc E, F, G;
    for(long long i = 0; i < 5; i++){
        E = B;
        E *= C;
        F = E;
        E *= C;
        G = A;
        G *= D;
        G *= D;
        E += G;
        F *= D;
        F *= 2;
        C = E;
        D = F;
    }
}
int main(){
    Nbc ua(1), da(1), ub(1), db(2), ut(1), dt(4);
    long long p = 1;
    root(ub, db, ub, db);
    Nbc uaa, daa, ubb, dbb, utt, dtt, baf, temp;
    for(int i = 0; i < 2; i++){
        cout << i << endl;
        if(i != 0){
            ua = uaa;
            da = daa;
            ub = dbb;
            db = dbb;
            ut = utt;
            dt = dtt;
            p *= 2;
        }
        uaa = ua * db + ub * da;
        daa = da * db;
        daa *= 2;
        cout << "endaa" << endl;
        //aa‚±‚±‚Ü‚Å
        ubb = ua * ub;
        dbb = da * db;
        root(ubb, dbb, ubb, dbb);
        cout << "endbb" << endl;
        //bb‚±‚±‚Ü‚Å
        dtt = daa * da;
        dtt *= dtt;
        utt = dtt;
        dtt *= dt;
        utt *= ut;
        baf = ua * daa;
        temp = uaa * da;
        //if(baf > temp)
        baf -= temp;
        //else baf = temp - baf;
        baf *= baf;
        baf *= dt;
        baf *= p;
        utt -= baf;
        cout << "endtt" << endl;
        //tt‚±‚±‚Ü‚Å
    }
    Nbc a, b;
    a = uaa * dbb + ubb * daa;
    a *= a;
    a *= dtt;
    b = daa * dbb;
    b *= b;
    b *= utt;
    b *= 4;
    cout << a.fsize << ' ' << b.fsize << endl;
    for(int i = 0; i < 15360; i++){
        cout << a / b;
        if(i == 0)cout << '.';
        if(i % 10 == 0)cout << ' ';
        if(i % 100 == 0)cout << endl;
        a *= 10;
    }
}