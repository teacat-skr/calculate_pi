#include<bits/stdc++.h>
using namespace std;
const int digit = 100000;
const long long base = 2147483648;
class Nbc{
    public: long long fsize = digit - 1;
    public: vector<long long> data = vector<long long>(digit);
    //先頭桁の位置と2^32進数の疑似的な数値と見たvectorを管理
    public: Nbc(long long num = 0){
            this->data.at(this->fsize) = num % base;
        if(num >= base){
            this->fsize--;
            this->data.at(this->fsize) = num / base;
        }
        //任意のlong longで初期化するコンストラクタ
    }
    Nbc operator+(Nbc obj){
        Nbc some;
        int pl = min(this->fsize, obj.fsize);
        for(int i = digit - 1; i >= pl; i--){
            some.data.at(i) += this->data.at(i) + obj.data.at(i);//A+B
            some.data.at(i - 1) += some.data.at(i) / base;//繰り上がりを上位桁に足す
            some.data.at(i) %= base;//繰り上がりの分減らす
        }
        if(some.data.at(pl - 1) != 0)some.fsize = pl - 1;
        else some.fsize = pl;
        //先頭桁を受け渡すかつ繰り上がりの場合更新
        return some;
    }
    void operator+=(Nbc obj){
        Nbc some;
        int pl = min(this->fsize, obj.fsize);
        for(int i = digit - 1; i >= pl; i--){
            some.data.at(i) += this->data.at(i) + obj.data.at(i);
            some.data.at(i - 1) += some.data.at(i) / base;
            some.data.at(i) %= base;
        }
        if(some.data.at(pl - 1) != 0)some.fsize = pl - 1;
        else some.fsize = pl;
        *this = some;
    }
    Nbc operator-(Nbc obj){
        Nbc some = *this;
        for(int i = this->fsize; i < digit; i++){
            some.data.at(i) -= obj.data.at(i);
        }
        //0から2^31 - 1になることが担保されているので引くことができる
        for(int i = digit - 1; i > some.fsize; i--){
            if(some.data.at(i) < 0){
                some.data.at(i) += base;
                some.data.at(i - 1)--;
            }
        }
        //前の処理で負の数になっているものを上位桁から1もらい成型
        //-2^31まで許容するので1引いても問題ない
        for(int i = some.fsize; i < digit; i++){
            if(some.data.at(i) != 0){
                some.fsize = i;
                break;
            }
        }
        //先頭桁から初めて0以外になったところに更新
        return some;
    }
    void operator-=(Nbc obj){
        Nbc some = *this;
        for(int i = this->fsize; i < digit; i++){
            some.data.at(i) -= obj.data.at(i);
        }
        for(int i = digit - 1; i > some.fsize; i--){
            if(some.data.at(i) < 0){
                some.data.at(i) += base;
                some.data.at(i - 1)--;
            }
        }
        for(int i = some.fsize; i < digit; i++){
            if(some.data.at(i) != 0){
                some.fsize = i;
                break;
            }
        }
        *this = some;
    }
    Nbc operator*(long long a){
        if(a >= base)cout << "error:Nbc * long long int, aがintの最大値より大きいです" << a << endl;
        Nbc some;
        long long baf;
        for(int i = digit - 1; i >= this->fsize; i--){
            baf = this->data.at(i) * a;
            some.data.at(i) += baf % base;
            some.data.at(i - 1) += baf / base;
        }
        if(some.data.at(this->fsize - 1) != 0)some.fsize = this->fsize - 1;
        else some.fsize = this->fsize;
        return some;
    }
    void operator*=(long long a){
        if(a >= base)cout << "error:Nbc * long long int, aがintの最大値より大きいです:" << a << endl;
        Nbc some;
        long long baf;
        for(int i = digit - 1; i >= fsize; i--){
            baf = this->data.at(i) * a;
            some.data.at(i) += baf % base;
            some.data.at(i - 1) += baf / base;
        }
        if(some.data.at(this->fsize - 1) != 0)some.fsize = this->fsize - 1;
        else some.fsize = this->fsize;
        *this = some;
    }
    void operator<<(int a){
        //普通にbaseをかけるとエラーが起こるのでbitシフトで回避
        for(int i = this->fsize; i < digit; i++){
            this->data.at(i - a) = this->data.at(i);
        }
        for(int i = digit - a; i < digit; i++){
            this->data.at(i) = 0;
        }
        this->fsize -= a;
    }
    Nbc operator*(Nbc obj){
        Nbc some, baf = *this;
        for(int i = digit - 1; i >= obj.fsize; i--){
            some += baf * obj.data.at(i);
            baf << 1;
        }
        for(int i = 0; i < digit; i++){
            if(some.data.at(i) != 0){
                some.fsize = i;
                break;
            }
        }
        return some;
    }
    void operator*=(Nbc obj){
        Nbc some, baf = *this;
        for(int i = digit - 1; i >= obj.fsize; i--){
            some += baf * obj.data.at(i);
            baf << 1;
        }
        for(int i = 0; i < digit; i++){
            if(some.data.at(i) != 0){
                some.fsize = i;
                break;
            }
        }
        *this = some;
    }
    bool operator>(Nbc obj){
        long long pl = min(this->fsize, obj.fsize);
        for(int i = pl; i < digit; i++){
            if(this->data.at(i) > obj.data.at(i))return true;
            else if(this->data.at(i) < obj.data.at(i))return false;
        }
        //先頭桁から見ていき判定
        return false;
    }
    bool operator<(Nbc obj){
        long long pl = min(this->fsize, obj.fsize);
        for(int i = pl; i < digit; i++){
            if(this->data.at(i) > obj.data.at(i))return false;
            else if(this->data.at(i) < obj.data.at(i))return true;
        }
        //先頭桁から見ていき判定
        return false;
    }
    bool operator>=(Nbc obj){
        long long pl = min(this->fsize, obj.fsize);
        for(int i = pl; i < digit; i++){
            if(this->data.at(i) > obj.data.at(i))return true;
            else if(this->data.at(i) < obj.data.at(i))return false;
        }
        //先頭桁から見ていき判定
        return true;
    }
    bool operator<=(Nbc obj){
        long long pl = min(this->fsize, obj.fsize);
        for(int i = pl; i < digit; i++){
            if(this->data.at(i) > obj.data.at(i))return false;
            else if(this->data.at(i) < obj.data.at(i))return true;
        }
        //先頭桁から見ていき判定
        return true;
    }
    bool operator==(Nbc obj){
        long long pl = min(this->fsize, obj.fsize);
        for(int i = pl; i < digit; i++){
            if(this->data.at(i) > obj.data.at(i))return false;
            else if(this->data.at(i) < obj.data.at(i))return false;
        }
        //先頭桁から見ていき判定
        return true;
    }
    long long operator/(Nbc obj){
        //A/Bの答えを返し、Aはあまりになる
        //A/B>=10の場合は求められない
        Nbc C;
        long long ans = 0;
        for (int i = 0; i < 9; i++){
            C += obj;
            if(*this < C){
                C -= obj;
                break;
            }
            ans++;
        }
        *this -= C;
        return ans;
    }
};