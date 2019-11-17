#include<bits/stdc++.h>
using namespace std;
const int digit = 100000;
const long long base = 2147483648;
class Nbc{
    public: long long fsize = digit - 1;
    public: vector<long long> data = vector<long long>(digit);
    //�擪���̈ʒu��2^32�i���̋^���I�Ȑ��l�ƌ���vector���Ǘ�
    public: Nbc(long long num = 0){
            this->data.at(this->fsize) = num % base;
        if(num >= base){
            this->fsize--;
            this->data.at(this->fsize) = num / base;
        }
        //�C�ӂ�long long�ŏ���������R���X�g���N�^
    }
    Nbc operator+(Nbc obj){
        Nbc some;
        int pl = min(this->fsize, obj.fsize);
        for(int i = digit - 1; i >= pl; i--){
            some.data.at(i) += this->data.at(i) + obj.data.at(i);//A+B
            some.data.at(i - 1) += some.data.at(i) / base;//�J��オ�����ʌ��ɑ���
            some.data.at(i) %= base;//�J��オ��̕����炷
        }
        if(some.data.at(pl - 1) != 0)some.fsize = pl - 1;
        else some.fsize = pl;
        //�擪�����󂯓n�����J��オ��̏ꍇ�X�V
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
        //0����2^31 - 1�ɂȂ邱�Ƃ��S�ۂ���Ă���̂ň������Ƃ��ł���
        for(int i = digit - 1; i > some.fsize; i--){
            if(some.data.at(i) < 0){
                some.data.at(i) += base;
                some.data.at(i - 1)--;
            }
        }
        //�O�̏����ŕ��̐��ɂȂ��Ă�����̂���ʌ�����1���炢���^
        //-2^31�܂ŋ��e����̂�1�����Ă����Ȃ�
        for(int i = some.fsize; i < digit; i++){
            if(some.data.at(i) != 0){
                some.fsize = i;
                break;
            }
        }
        //�擪�����珉�߂�0�ȊO�ɂȂ����Ƃ���ɍX�V
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
        if(a >= base)cout << "error:Nbc * long long int, a��int�̍ő�l���傫���ł�" << a << endl;
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
        if(a >= base)cout << "error:Nbc * long long int, a��int�̍ő�l���傫���ł�:" << a << endl;
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
        //���ʂ�base��������ƃG���[���N����̂�bit�V�t�g�ŉ��
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
        //�擪�����猩�Ă�������
        return false;
    }
    bool operator<(Nbc obj){
        long long pl = min(this->fsize, obj.fsize);
        for(int i = pl; i < digit; i++){
            if(this->data.at(i) > obj.data.at(i))return false;
            else if(this->data.at(i) < obj.data.at(i))return true;
        }
        //�擪�����猩�Ă�������
        return false;
    }
    bool operator>=(Nbc obj){
        long long pl = min(this->fsize, obj.fsize);
        for(int i = pl; i < digit; i++){
            if(this->data.at(i) > obj.data.at(i))return true;
            else if(this->data.at(i) < obj.data.at(i))return false;
        }
        //�擪�����猩�Ă�������
        return true;
    }
    bool operator<=(Nbc obj){
        long long pl = min(this->fsize, obj.fsize);
        for(int i = pl; i < digit; i++){
            if(this->data.at(i) > obj.data.at(i))return false;
            else if(this->data.at(i) < obj.data.at(i))return true;
        }
        //�擪�����猩�Ă�������
        return true;
    }
    bool operator==(Nbc obj){
        long long pl = min(this->fsize, obj.fsize);
        for(int i = pl; i < digit; i++){
            if(this->data.at(i) > obj.data.at(i))return false;
            else if(this->data.at(i) < obj.data.at(i))return false;
        }
        //�擪�����猩�Ă�������
        return true;
    }
    long long operator/(Nbc obj){
        //A/B�̓�����Ԃ��AA�͂��܂�ɂȂ�
        //A/B>=10�̏ꍇ�͋��߂��Ȃ�
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