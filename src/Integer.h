//
// Created by wangzw on 2020/10/27.
//

#ifndef RSA_INTEGER_H
#define RSA_INTEGER_H

#include <vector>
#include <utility>
#include <cstdint>
#include <string>
#include <cstdlib>


class Integer {
    std::vector<uint32_t> n;
    std::vector<uint32_t> reciprocal;
public:
    Integer();
    explicit Integer(std::vector<uint32_t>& nn);
    explicit Integer(uint32_t num);
    void setInteger(std::vector<uint32_t>& nn);
    std::vector<uint32_t> getNN();

    static bool larger_than(std::vector<uint32_t>& a, uint32_t begin, uint32_t end, std::vector<uint32_t>& b);
    uint32_t get_digit();
    uint32_t get_large();

private:
    Integer cut(uint32_t start, uint32_t end);

    static std::pair<Integer, Integer> _div(Integer& a, uint32_t b);
    static void _remove_zero(std::vector<uint32_t>& a);

public:
    void rightShift(uint32_t m);
    void leftShift(uint32_t m);
    void getReciprocalNewton();
    bool ReciprocalFinished();
    std::string toString();
    static void print(Integer m);
    inline uint8_t getDigit(uint32_t m);
    static Integer get_Integer_from_input();
    static Integer test_reci(Integer& p);
    static Integer add(Integer& a, Integer& b);
    static Integer sub(Integer& a, Integer& b);
    static Integer mul(Integer& a, Integer& b);
    static Integer mul64(Integer& a, Integer& b);
    static std::pair<Integer, Integer> div(Integer& a, Integer& b);
    static Integer inverse(Integer& n, Integer& a);
    static Integer gcd(Integer& n, Integer& a);
    static bool equal(Integer a, Integer& b);
    static bool is_even(Integer& a);
    static Integer mod_in_exp(Integer& a, Integer& e, Integer& p);
    static Integer fast_mod_in_exp(Integer& a, Integer& p);
    static Integer debug_mod_in_exp(Integer& a, Integer& e, Integer& p);
    static Integer crt(Integer& n, Integer& p, Integer& q, Integer& rp, Integer& rq);
    static bool is_zero(Integer& a);
    static bool large_than(Integer& a, Integer& b);
};


#endif //RSA_INTEGER_H
