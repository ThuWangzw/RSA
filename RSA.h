//
// Created by wangzw on 2020/10/27.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

#include "Integer.h"

class RSA {
     Integer n,p,q,e,d;
private:
    Integer find_prime(uint32_t digit);
    Integer find_in_rrs(Integer n);

public:
    void set_up(const Integer& p, const Integer& q);
    void set_up();

public:
    Integer decryption(Integer& M);
    Integer encryption(Integer& C);
};


#endif //RSA_RSA_H
