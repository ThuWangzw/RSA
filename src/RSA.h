//
// Created by wangzw on 2020/10/27.
//

#ifndef RSA_RSA_H
#define RSA_RSA_H

#include "Integer.h"
#include <cstdint>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <string>

class RSA {
     Integer n,p,q,e,d;
     bool inited;
public:

    RSA();
    static Integer find_prime(uint32_t digit);
    static bool check_prime(std::vector<Integer>& primes, Integer& n);
    static void _find_prime(Integer& begin_number, Integer& step, Integer& result);

private:
    static Integer find_in_rrs(Integer n);
    static Integer euler_func(Integer& t_n, Integer& t_p, Integer& t_q);
    static Integer random_int(Integer& max);
    static uint32_t random_int32(uint32_t max = UINT32_MAX);

private:
    bool test_rsa();

public:
    void set_up(Integer& p, Integer& q);
    double set_up(uint32_t digit = 768);
    bool is_inited();

public:
    Integer decryption(Integer& C);
    Integer encryption(Integer& M);
    std::string decryption(std::vector<Integer>& C);
    std::vector<Integer> encryption(std::string& M);
    static uint32_t find_cnts;
    static uint32_t miller_cnts;
    friend class RSAToy;
};


#endif //RSA_RSA_H
