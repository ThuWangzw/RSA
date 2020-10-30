//
// Created by wangzw on 2020/10/27.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

#include "Integer.h"
#include <cstdint>

class RSA {
     Integer n,p,q,e,d;
private:
    Integer find_prime(uint32_t digit);
    static Integer find_in_rrs(Integer n);
    static Integer euler_func(Integer& t_n, Integer& t_p, Integer& t_q);
    static Integer random_int(Integer& max);

public:
    void set_up(Integer& p, Integer& q);
    void set_up();

public:
    Integer decryption(Integer& C);
    Integer encryption(Integer& M);
};


#endif //RSA_RSA_H
