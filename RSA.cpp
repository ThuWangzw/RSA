//
// Created by wangzw on 2020/10/27.
//

#include "RSA.h"
#include <vector>
#include <iostream>
using namespace std;

Integer RSA::find_prime(uint32_t digit = 384) {
    int ori_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
    vector<Integer> primes(sizeof(ori_primes)/ sizeof(0), Integer(0));
    for(int i=0; i< sizeof(ori_primes)/ sizeof(0); i++) primes[i] = Integer(ori_primes[i]);
    Integer find_cnt(0);
    Integer actual_find_cnt(0);
    Integer one(1);
    Integer two(2);

    Integer max(UINT32_MAX);
    vector<uint32_t> num(digit, 0);
    uint32_t base = 0;
    for(uint32_t i = 0; i*32<digit; i+=1) {
        base = random_int32();
        if (((i+1)*32 >= digit)) {
            base = random_int32(1<<(digit-i*32-1));
            base += 1<<(digit-i*32-1);
        }
        if((i == 0) && (base % 2 == 0)) {
            i -= 1;
            continue;
        }
        num[i] = base;
    }
    Integer n(num);

    clock_t begin = clock();
    clock_t end = clock();
    double little_prime = 0;
    double miller = 0;
    while (true) {
        begin = clock();
        find_cnt = Integer::add(find_cnt, one);
        // random generate a integer
        bool is_prime = true;
        for(int i=0; i<primes.size(); i++) {
            Integer& p = primes[i];
            auto res = Integer::div(n, p);
            if(Integer::is_zero(res.second)) {
                is_prime = false;
                break;
            }
        }
        if(!is_prime) {
            n = Integer::add(n, two);
            continue;
        };
        begin = clock();
        Integer s(0);
        Integer d = Integer::sub(n, one);
        while (true) {
            auto res = Integer::div(d, two);
            if(Integer::equal(res.second, one)) {
                break;
            }
            s = Integer::add(s, one);
            d = res.first;
        }
        end = clock();
        little_prime += (double)(end-begin)/CLOCKS_PER_SEC;
        begin = clock();
        actual_find_cnt = Integer::add(actual_find_cnt, one);
        int max_trial = 5;
        Integer n_minus = Integer::sub(n, one);
        bool pass = false;
        for(int i=0; i<max_trial; i++) {
            Integer a = random_int(n);
            if(Integer::equal(Integer::debug_mod_in_exp(a, d, n), one)) {
                pass = true;
            } else {
                Integer dd = d;
                for(Integer j(0); !Integer::equal(j, s); j = Integer::add(j, one)) {
                    if(Integer::equal(Integer::debug_mod_in_exp(a, dd, n), n_minus)) {
                        pass = true;
                        break;
                    }
                    dd = Integer::mul(dd, two);
                }
            }
            if(!pass) break;
        }
        if(pass) {
            return n;
        }
        n = Integer::add(n, two);
        end = clock();
        miller += (double)(end-begin)/CLOCKS_PER_SEC;
        begin = clock();
    }
}

Integer RSA::find_in_rrs(Integer t_n) {
    Integer one(1);
    Integer t_e(2);
    for(; !Integer::equal(t_n, t_e); t_e = Integer::add(t_e, one)) {
        if(Integer::equal(Integer::gcd(t_n, t_e), one)) {
            return t_e;
        }
    }
}

void RSA::set_up(Integer &np, Integer &nq) {
    p = np;
    q = nq;
    n = Integer::mul(p, q);
    Integer euler_n = euler_func(n, p, q);
    e = find_in_rrs(euler_n);
    d = Integer::inverse(euler_n, e);
    cout << "set up done" << endl;
}

void RSA::set_up() {
    Integer np = find_prime();
    Integer nq = find_prime();
    while(Integer::equal(np, nq)) {
        nq = find_prime();
    }
    set_up(np, nq);
}

Integer RSA::decryption(Integer &C) {
    return Integer::mod_in_exp(C, d, n);
    Integer one(1);
    Integer p1 = Integer::sub(p, one);
    Integer q1 = Integer::sub(q, one);
    auto pe = Integer::div(d, p1);
    auto qe = Integer::div(d, q1);
    auto pmod = Integer::mod_in_exp(C, pe.second, p);
    auto qmod = Integer::mod_in_exp(C, qe.second, q);
//    pmod = Integer::mod_in_exp(pmod, d, p);
//    qmod = Integer::mod_in_exp(qmod, d, q);

    return Integer::crt(n, p, q, pmod, qmod);
}

Integer RSA::encryption(Integer &M) {
    return Integer::mod_in_exp(M, e, n);
}

Integer RSA::euler_func(Integer &t_n, Integer &t_p, Integer &t_q) {
    auto num = Integer::sub(t_n, t_p);
    num = Integer::sub(num, t_q);
    Integer one(1);
    return Integer::add(num, one);
}

RSA::RSA() {
    srand(time(nullptr));
}

uint32_t RSA::random_int32(uint32_t max) {
    double p = (double)rand() / (RAND_MAX+1);
    return max * p;
}

Integer RSA::random_int(Integer &max) {
    vector<uint32_t> nn = max.getNN();
    uint32_t digit = nn.size();
    uint32_t mid_digit = rand() % digit;
    nn[mid_digit] = random_int32(nn[mid_digit]);
    for(uint32_t i = 0; i<mid_digit; i++) {
        nn[i] = random_int32();
    }
    return Integer(nn);
}


