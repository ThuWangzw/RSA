//
// Created by wangzw on 2020/10/27.
//

#ifndef RSA_INTEGER_H
#define RSA_INTEGER_H

#include <vector>
#include <utility>
#include <cstdint>


class Integer {
    std::vector<uint32_t> n;
public:
    Integer();
    explicit Integer(std::vector<uint32_t>& nn);
    explicit Integer(uint32_t num);
    void setInteger(std::vector<uint32_t>& nn);
    std::vector<uint32_t> getNN();

    static bool larger_than(std::vector<uint32_t>& a, uint32_t begin, uint32_t end, std::vector<uint32_t>& b);

private:
    Integer cut(uint32_t start, uint32_t end);

    static void _remove_zero(std::vector<uint32_t>& a);

public:
    static Integer add(Integer& a, Integer& b);
    static Integer sub(Integer& a, Integer& b);
    static Integer mul(Integer& a, Integer& b);
    static std::pair<Integer, Integer> div(Integer& a, Integer& b);
    static Integer inverse(Integer& n, Integer& a);
    static Integer gcd(Integer& n, Integer& a);
    static bool equal(Integer a, Integer& b);
    static bool is_even(Integer& a);
    static Integer mod_in_exp(Integer& a, Integer& e, Integer& p);
    static Integer crt(Integer& n, Integer& p, Integer& q, Integer& rp, Integer& rq);
    static bool is_zero(Integer& a);
};


#endif //RSA_INTEGER_H
