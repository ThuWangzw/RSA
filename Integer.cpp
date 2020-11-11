//
// Created by wangzw on 2020/10/27.
//

#include "Integer.h"
#include <vector>
#include <ctime>
#include <cmath>
#include <string>
#include <iostream>

using namespace std;
double mod_time = 0;
double mod_time1=0;
double mod_time2 = 0;
double mod_time3 = 0;
double mod_time4 = 0;
double fast_time = 0;
double fast_time1 = 0;
double fast_time2 = 0;
double fast_time3 = 0;
uint32_t fast_cnt = 0;
double mul_time = 0;
double mul_core_time = 0;
uint32_t mul_cnt = 0;

Integer::Integer() {
    n = vector<uint32_t>(1, 0);
};

Integer::Integer(uint32_t num) {
    n = vector<uint32_t>(1, num);
    reciprocal = vector<uint32_t>(1, 0);
}

Integer::Integer(std::vector<uint32_t> &nn) {
    n = nn;
    reciprocal = vector<uint32_t>(1, 0);
    _remove_zero(n);
}

void Integer::setInteger(std::vector<uint32_t> &nn) {
    reciprocal = vector<uint32_t>(1, 0);
    n = nn;
}

Integer Integer::add(Integer& a, Integer& b) {
    vector<uint32_t > aa = a.getNN();
    vector<uint32_t > ba = b.getNN();
    auto max_len = (aa.size()>ba.size())?aa.size():ba.size();
    aa.resize(max_len, 0);
    ba.resize(max_len, 0);
    vector<uint32_t > ca(max_len+1);
    uint32_t carry = 0;
    uint32_t  digit = 0;
    for(digit = 0; digit < max_len; digit++) {
        uint64_t res = (uint64_t)aa[digit] + ba[digit] + carry;
        if(res > UINT32_MAX) carry = 1;
        else carry = 0;
        ca[digit] = res;
    }
    ca[digit] = carry;
    _remove_zero(ca);
    return Integer(ca);
}

Integer Integer::sub(Integer& a, Integer& b) {
    // 这里假定a>=b
    vector<uint32_t >& aa = a.n;
    vector<uint32_t >& ba = b.n;
    auto max_len = (aa.size()>ba.size())?aa.size():ba.size();
    aa.resize(max_len, 0);
    ba.resize(max_len, 0);
    vector<uint32_t > ca = a.n;
    for(uint32_t digit = 0; digit < max_len; digit++) {
        if(ca[digit] >= ba[digit]) {
            ca[digit] = ca[digit] - ba[digit];
        } else{
            for(uint32_t next_digit = digit+1; next_digit < max_len; next_digit++) {
                if(ca[next_digit] > 0){
                    ca[next_digit]--;
                    for(uint32_t between_digit = next_digit-1; between_digit > digit; between_digit--) {
                        ca[between_digit] = UINT32_MAX;
                    }
                    ca[digit] = (UINT32_MAX-ba[digit])+1+ca[digit];
                    break;
                }
            }
        }
    }
    _remove_zero(ca);
    return Integer(ca);
}

Integer Integer::mul64(Integer& a, Integer& b) {
    mul_cnt++;
    clock_t begin = clock();
    vector<uint32_t >& aa = a.n;
    vector<uint32_t >& ba = b.n;
    auto a_len = aa.size();
    auto b_len = ba.size();
    auto max_len = (a_len>b_len)?a_len:b_len;
    vector<uint32_t> ca(max_len*2, 0);
    uint32_t max_cdigit = 0;
    clock_t core_begin = clock();
    for(uint32_t bdigit = 0; bdigit < b_len; bdigit++) {
        uint32_t bnum = ba[bdigit];
        uint64_t carry = 0;
        for(uint32_t adigit = 0; adigit < a_len+1; adigit++) {
            uint32_t aaadigit = (adigit==a_len)?0:aa[adigit];
            uint64_t res = (uint64_t)bnum*(uint64_t)aaadigit + carry;
            carry = res>>32;
            uint32_t subcarry = res;
            uint32_t digit;
            for(digit = bdigit+adigit; digit<max_len*2; digit++) {
                uint64_t res = (uint64_t)ca[digit] + (uint64_t)subcarry;
                ca[digit] = (uint32_t)res;
                subcarry = res>>32;
                if(subcarry == 0) break;
            }
            max_cdigit = (digit > max_cdigit)?digit:max_cdigit;
        }
    }
    mul_core_time += (double)(clock() - core_begin)/CLOCKS_PER_SEC;
    _remove_zero(ca);
    mul_time += (double)(clock() - begin)/CLOCKS_PER_SEC;
    return Integer(ca);
}

std::pair<Integer, Integer> Integer::div(Integer& a, Integer& b) {
    // 假定a > b
    vector<uint32_t > aa = a.getNN();
    vector<uint32_t > ba = b.getNN();
    Integer two(2);
    if(ba.size() == 1) {
        return _div(a, ba[0]);
    }
    auto a_len = aa.size();
    auto b_len = ba.size();
    auto max_len = (a_len>b_len)?a_len:b_len;
    vector<uint32_t> ra(aa);
    vector<uint32_t> pa(max_len, 0);
    for(long int digit = a_len-b_len; digit >= 0; digit--) {
        // if a[len-digit:] > b
        Integer cnt(0);
        Integer one(1);
        while (Integer::larger_than(ra, digit, a_len, ba)) {
            vector<uint32_t > bbaa = b.getNN();
            Integer bba(bbaa);
            while (Integer::larger_than(ra, digit, a_len, bba.n)) {
                bba = mul64(bba, two);
            }
            auto res = div(bba, two);
            bba = res.first;
            bbaa = bba.n;
            uint32_t bb_len = bbaa.size();
//            Integer::_sub(ra, digit, a_len, ba, 0, b_len);
            cnt = add(cnt, one);
            for(uint32_t i = digit; i < digit+bb_len; i++) {
                if(ra[i] >= bbaa[i-digit]) {
                    ra[i] = ra[i] - bbaa[i-digit];
                } else{
                    for(uint32_t next_digit = i+1; next_digit < a_len; next_digit++) {
                        if(ra[next_digit] > 0){
                            ra[next_digit]--;
                            for(uint32_t between_digit = next_digit-1; between_digit > digit; between_digit--) {
                                ra[between_digit] = UINT32_MAX;
                            }
                            ra[i] = (UINT32_MAX-bbaa[i-digit])+1+ra[i];
                            break;
                        }
                    }
                }
            }
            pa[digit]+=1;
            _remove_zero(ra);
            a_len = ra.size();
        }
    }
    _remove_zero(ra);
    _remove_zero(pa);
    return std::pair<Integer, Integer>(Integer(pa), Integer(ra));
}

Integer Integer::inverse(Integer &n, Integer &a) {
    Integer r0 = n;
    Integer r1 = a;

    Integer& t0 = *(new Integer(0));
    Integer& t1 = *(new Integer(1));
    Integer t;
    while (!is_zero(r1)) {
        std::pair<Integer, Integer> res = div(r0, r1);
        Integer& p = res.first;
        Integer& r = res.second;
        Integer tmp = mul64(p, t1);
        while (larger_than(tmp.n, 0, tmp.n.size(), t0.n)) {
            t0 = add(t0, n);
        }
        t = sub(t0, tmp);
        r0 = r1;
        r1 = r;
        t0 = t1;
        t1 = t;
    }
    return t0;
}

Integer Integer::mod_in_exp(Integer &a, Integer &e, Integer &p) {
    Integer one(1);
    Integer two(2);

    vector<uint32_t>& ea = e.n;
    uint32_t ea_digit = e.get_digit();
    Integer res(1);
    Integer aa(a);
    for(uint32_t i=0; i<ea_digit; i++) {
        if(e.getDigit(i)) {
            res = mul64(aa, res);
            res = fast_mod_in_exp(res, p);
        }
        aa = mul64(aa, aa);
        aa = fast_mod_in_exp(aa, p);
    }
    return res;
}

Integer Integer::crt(Integer &n, Integer &p, Integer &q, Integer &rp, Integer &rq) {
    Integer ip = inverse(p, q);
    Integer iq = inverse(q, p);
    Integer c1 = mul(rp, q);
    c1 = mul(c1, ip);
    Integer c2 = mul(rq, p);
    c2 = mul(c2, iq);
    auto num = add(c1, c2);
    auto res = div(num, n);
    return res.second;
}

std::vector<uint32_t> Integer::getNN() {
    return n;
}

Integer Integer::cut(uint32_t start, uint32_t end) {
    return Integer(*(new vector<uint32_t>(n.begin(), n.begin())));
}

bool Integer::larger_than(std::vector<uint32_t>& a, uint32_t begin, uint32_t end, std::vector<uint32_t>& b) {
    // 假定a的位数比b高
    uint32_t a_len = end-begin;
    if(a_len > b.size())
        return true;
    else if(a_len < b.size())
        return false;
    for(long long digit = a_len-1; digit >= 0; digit--){
        if(a[digit+begin] > b[digit]) return true;
        else if(a[digit+begin] < b[digit]) return false;
    }
    return true;
}

void Integer::_remove_zero(std::vector<uint32_t> &a) {
    for(long long digit = a.size()-1; digit >= 0; digit--) {
        if(a[digit] > 0) {
            a.resize(digit+1);
            return;
        }
    }
    a.resize(1);
}

bool Integer::is_zero(Integer &a) {
    vector<uint32_t>& n = a.n;
    for(uint32_t i = 0; i<n.size(); i++) {
        if(n[i] != 0) return false;
    }
    return true;
}

bool Integer::equal(Integer a, Integer &b) {
    _remove_zero(a.n);
    _remove_zero(b.n);
    if(a.n.size() != a.n.size()) return false;
    for(uint32_t i = 0; i < a.n.size(); i++) {
        if(a.n[i] != b.n[i]) return false;
    }
    return true;
}

bool Integer::is_even(Integer &a) {
    return a.n[0] % 2 == 0;
}

Integer Integer::gcd(Integer &n, Integer &a) {
    Integer r0 = n;
    Integer r1 = a;
    while (!is_zero(r1)) {
        std::pair<Integer, Integer> res = div(r0, r1);
        Integer& p = res.first;
        Integer& r = res.second;

        r0 = r1;
        r1 = r;
    }
    return r0;
}

uint32_t Integer::get_digit() {
    uint32_t digit = n.size()*32 - 32;
    uint32_t large = n[n.size()-1];
    while (large > 0) {
        digit++;
        large /= 2;
    }
    return digit;
}

uint32_t Integer::get_large() {
    return n[n.size()-1];
}

std::pair<Integer, Integer> Integer::_div(Integer &a, uint32_t b) {
    vector<uint32_t > aa = a.getNN();
    vector<uint32_t > ca(aa.size(), 0);
    uint32_t r;
    uint64_t last = 0;
    for(int digit=aa.size()-1; digit>=0; digit--) {
        last = last*UINT32_MAX+last+aa[digit];
        ca[digit] = last/b;
        last = last % b;
    }
    r = last;
    return pair<Integer, Integer>(Integer(ca), Integer(r));
}

Integer Integer::debug_mod_in_exp(Integer &a, Integer &e, Integer &p) {
    clock_t begin = clock();
    auto res = mod_in_exp(a, e, p);
    clock_t end = clock();
    mod_time += (double)(end-begin)/CLOCKS_PER_SEC;
    return res;
}

void Integer::getReciprocalNewton() {
    Integer& n = *this;
    Integer n_reciprocal = Integer(1);
    uint32_t m=n.get_digit()*2;
    Integer c(1);
    c.leftShift(m);
    n_reciprocal.leftShift(n.get_digit());
    Integer two(2);
    uint32_t trails = 1000;
    Integer zero(0);
    for(uint32_t i=0; i<trails; i++) {
        Integer delta = mul64(n, n_reciprocal);
        if(large_than(delta, c)) {
            cout << "error!" << endl;
        }
        delta = sub(c, delta);
        delta = mul64(n_reciprocal, delta);
        delta.rightShift(m);
        if(equal(delta, zero)) {
            break;
        }
        n_reciprocal = add(n_reciprocal, delta);
    }
    reciprocal = n_reciprocal.n;
}

void Integer::leftShift(uint32_t m) {
    uint32_t digit = get_digit();
    uint32_t n_size = ceil((double)(digit+m)/32);
    n.resize(n_size, 0);
    uint32_t large_shift = m/32;
    uint32_t small_shift = m%32;
    for(long long i=n_size-1; i>=0; i--) {
        n[i] = i>=large_shift?((n[i-large_shift]<<small_shift)+((i>=large_shift+1)?(n[i-large_shift-1]>>(32-small_shift)):0)):0;
    }
}

void Integer::rightShift(uint32_t m) {
    uint32_t digit = get_digit();
    if(digit <= m) {
        n = vector<uint32_t>(1, 0);
        return;
    }
    uint32_t begin_digit = m/32;
    uint32_t shift = m%32;
    for(uint32_t i=0; begin_digit < n.size(); i++, begin_digit++) {
        n[i] = (n[begin_digit]>>shift)+ (((begin_digit+1<n.size()) && (shift>0))?(n[begin_digit+1]<<(32-shift)):0);
    }
    n.resize(uint32_t(ceil((double)(digit-m)/32)), 0);
}

Integer Integer::fast_mod_in_exp(Integer &a, Integer &p) {
    fast_cnt++;
    clock_t begin = clock();
    clock_t allbegin = begin;
    if(!p.ReciprocalFinished()) {
        p.getReciprocalNewton();
    }
    begin = clock();
    Integer reciprocal(p.reciprocal);
    uint32_t m=p.get_digit()*2;

    Integer res = mul64(a, reciprocal);
    fast_time1 += (double)(clock()-begin)/CLOCKS_PER_SEC;
    begin = clock();
    res.rightShift(m);

    res = mul64(res, p);
    fast_time2 += (double)(clock()-begin)/CLOCKS_PER_SEC;
    begin = clock();
    res = sub(a, res);
    fast_time3 += (double)(clock()-begin)/CLOCKS_PER_SEC;
    while (larger_than(res.n, 0, res.n.size(), p.n)) {
        res = sub(res, p);
    }

    fast_time += (double)(clock()-allbegin)/CLOCKS_PER_SEC;
    return res;
}

bool Integer::ReciprocalFinished() {
    vector<uint32_t>& n = reciprocal;
    for(uint32_t i = 0; i<n.size(); i++) {
        if(n[i] != 0) return true;
    }
    return false;
}

std::string Integer::toString()
{
    string str;
    char buffer[100];
    for (uint32_t i = 0; i < n.size(); i++) {
        sprintf_s(buffer, "%x", n[i]);
        str += string(buffer);
    }
    return str;
}

Integer Integer::test_reci(Integer &p) {
    if(!p.ReciprocalFinished()) {
        p.getReciprocalNewton();
    }
    Integer reciprocal(p.reciprocal);
    Integer one(1);
    uint32_t m=p.get_digit()*2;
    one.leftShift(m);
    Integer res = mul64(p, reciprocal);
    return sub(one, res);
}

Integer Integer::get_Integer_from_input() {
    Integer num(0);
    Integer digit(10);
    string s;
    cin >> s;
    uint32_t i = 0;
    for(string::iterator p = s.begin(); p != s.end(); p++) {
        char c = *(p)-'0';
        Integer tc(c);
        num = mul64(num, digit);
        num = add(num, tc);
        i++;
    }
    return num;
}

bool Integer::large_than(Integer &a, Integer &b) {
    return larger_than(a.n, 0, a.n.size(), b.n);
}

void Integer::print(Integer m) {
    vector<int> mm;
    Integer ten(10);
    while (!is_zero(m)) {
        auto res = div(m, ten);
        mm.push_back(res.second.n[0]);
        m = res.first;
    }
    for(int i=mm.size()-1; i >= 0; i--) {
        cout << mm[i];
    }
    cout << endl;
}

uint8_t Integer::getDigit(uint32_t m) {
    return (n.size()>(m/32))? ((n[m/32] >> (m%32)) & 1) : 0;
}

Integer Integer::mul(Integer &a, Integer &b) {
    mul_cnt++;
    clock_t begin = clock();
    vector<uint32_t >& aa = a.n;
    vector<uint32_t >& ba = b.n;
    auto a_len = aa.size();
    auto b_len = ba.size();
    auto max_len = (a_len>b_len)?a_len:b_len;
    uint64_t mask = UINT32_MAX;
    vector<uint64_t> ca(max_len*2, 0);
    vector<uint32_t> cca(max_len*2, 0);
    for(uint32_t ai=0; ai<a_len; ai++) {
        for(uint32_t bi=0; bi<b_len; bi++) {
            ca[ai+bi] += (uint64_t)aa[ai]*(uint64_t)ba[bi];
            ca[ai+bi+1] += ca[ai+bi]>>32u;
            ca[ai+bi] =ca[ai+bi]&mask;
        }
    }
    for(uint32_t i=0; i<a_len+b_len; i++) {
        cca[i] = ca[i];
    }
    _remove_zero(cca);
    mul_time += (double)(clock() - begin)/CLOCKS_PER_SEC;
    return Integer(cca);
}
