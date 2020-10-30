//
// Created by wangzw on 2020/10/27.
//

#include "RSA.h"

Integer RSA::find_prime(uint32_t digit = 768) {
    // random generate
    Integer max(UINT32_MAX);

    return Integer();
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
}

void RSA::set_up() {

}

Integer RSA::decryption(Integer &C) {
//    return Integer::mod_in_exp(C, d, n);
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
