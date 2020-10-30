//
// Created by wangzw on 2020/10/27.
//

#include "Integer.h"
#include <vector>

using namespace std;

Integer::Integer() {
    n = vector<uint32_t>(1, 0);
};

Integer::Integer(uint32_t num) {
    n = vector<uint32_t>(1, num);
}

Integer::Integer(std::vector<uint32_t> &nn) {
    n = nn;
}

void Integer::setInteger(std::vector<uint32_t> &nn) {
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
        uint32_t res = aa[digit] + ba[digit] + carry;
        if((res <= aa[digit]) && (ba[digit] > 0)) carry = 1;
        else carry = 0;
        ca[digit] = res;
    }
    ca[digit] = carry;
    _remove_zero(ca);
    return Integer(ca);
}

Integer Integer::sub(Integer& a, Integer& b) {
    // 这里假定a>=b
    vector<uint32_t > aa = a.getNN();
    vector<uint32_t > ba = b.getNN();
    auto max_len = (aa.size()>ba.size())?aa.size():ba.size();
    aa.resize(max_len, 0);
    ba.resize(max_len, 0);
    vector<uint32_t > ca = aa;
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

Integer Integer::mul(Integer& a, Integer& b) {
    vector<uint32_t > aa = a.getNN();
    vector<uint32_t > ba = b.getNN();
    auto a_len = aa.size();
    auto b_len = ba.size();
    auto max_len = (a_len>b_len)?a_len:b_len;
    vector<uint32_t> ca(max_len*2, 0);
    uint32_t max_cdigit = 0;
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
    ca.resize(max_cdigit+1);
    _remove_zero(ca);
    return Integer(ca);
}

std::pair<Integer, Integer> Integer::div(Integer& a, Integer& b) {
    // 假定a > b
    vector<uint32_t > aa = a.getNN();
    vector<uint32_t > ba = b.getNN();
    auto a_len = aa.size();
    auto b_len = ba.size();
    auto max_len = (a_len>b_len)?a_len:b_len;
    vector<uint32_t> ra(aa);
    vector<uint32_t> pa(max_len, 0);
    for(long int digit = a_len-b_len; digit >= 0; digit--) {
        // if a[len-digit:] > b
        while (Integer::larger_than(ra, digit, a_len, ba)) {
//            Integer::_sub(ra, digit, a_len, ba, 0, b_len);
            for(uint32_t i = digit; i < digit+b_len; i++) {
                if(ra[i] >= ba[i-digit]) {
                    ra[i] = ra[i] - ba[i-digit];
                } else{
                    for(uint32_t next_digit = i+1; next_digit < a_len; next_digit++) {
                        if(ra[next_digit] > 0){
                            ra[next_digit]--;
                            for(uint32_t between_digit = next_digit-1; between_digit > digit; between_digit--) {
                                ra[between_digit] = UINT32_MAX;
                            }
                            ra[i] = (UINT32_MAX-ba[i-digit])+1+ra[i];
                            break;
                        }
                    }
                }
            }
            pa[digit]+=1;
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
        Integer tmp = mul(p, t1);
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

    if(equal(e, one)) {
        auto res = div(a, p);
        return res.second;
    }
    else if(equal(e, two)) {
        auto num = mul(a, a);
        auto res = div(num, p);
        return res.second;
    }
    else{
        pair<Integer, Integer> res = div(e, two);
        Integer half_mod = mod_in_exp(a, res.first, p);
        Integer full_mod = mod_in_exp(half_mod, two, p);
        if(!is_zero(res.second)) {
            full_mod = mul(full_mod, a);
        }
        return mod_in_exp(full_mod, one, p);
    }
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
    b.resize(a_len, 0);
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
