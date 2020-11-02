//
// Created by wangzw on 2020/10/27.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

#include "Integer.h"
#include <cstdint>
#include <ctime>
#include <cstdlib>

class RSA {
     Integer n,p,q,e,d;
public:
    RSA();

    static Integer find_prime(uint32_t digit);

private:
    static Integer find_in_rrs(Integer n);
    static Integer euler_func(Integer& t_n, Integer& t_p, Integer& t_q);
    static Integer random_int(Integer& max);
    static uint32_t random_int32(uint32_t max = UINT32_MAX);

public:
    void set_up(Integer& p, Integer& q);
    void set_up();

public:
    Integer decryption(Integer& C);
    Integer encryption(Integer& M);
};


#endif //RSA_RSA_H
