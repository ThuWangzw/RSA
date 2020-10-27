//
// Created by wangzw on 2020/10/27.
//

#include "Integer.h"

Integer::Integer() = default;

Integer::Integer(std::vector<uint64_t> &nn) {

}

void Integer::setInteger(std::vector<uint64_t> &nn) {
    n = nn;
}

Integer Integer::add(const Integer &a, const Integer &b) {
    return Integer();
}

Integer Integer::sub(const Integer &a, const Integer &b) {
    return Integer();
}

Integer Integer::mul(const Integer &a, const Integer &b) {
    return Integer();
}

std::pair<Integer, Integer> Integer::div(const Integer &a, const Integer &b) {
    return std::pair<Integer, Integer>();
}

Integer Integer::inverse(const Integer &n, const Integer &a) {
    return Integer();
}
