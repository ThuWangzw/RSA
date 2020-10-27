//
// Created by wangzw on 2020/10/27.
//

#ifndef RSA_INTEGER_H
#define RSA_INTEGER_H

#include <vector>
#include <utility>


class Integer {
    std::vector<uint64_t> n;
public:
    Integer();
    explicit Integer(std::vector<uint64_t>& nn);
    void setInteger(std::vector<uint64_t>& nn);

public:
    static Integer add(const Integer& a, const Integer& b);
    static Integer sub(const Integer& a, const Integer& b);
    static Integer mul(const Integer& a, const Integer& b);
    static std::pair<Integer, Integer> div(const Integer& a, const Integer& b);
    static Integer inverse(const Integer& n, const Integer& a);
    static Integer mod_in_exp(const Integer& a, const Integer& e, const Integer& p);
    static Integer crt(const Integer& n, const Integer& p, const Integer& q, const Integer& rp, const Integer& rq);
};


#endif //RSA_INTEGER_H
