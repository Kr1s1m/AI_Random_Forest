#pragma once

#include <random>
#include <iterator>

template<class bidiiter>
bidiiter random_unique(bidiiter begin, bidiiter end, size_t num_random) 
{
    size_t left = std::distance(begin, end);

    std::random_device randomDevice;
    std::mt19937 randomGenerator(randomDevice());
    

    while (num_random--) {
        bidiiter r = begin;
       
        std::uniform_int_distribution<> uniformDistirbution(0, left - 1);
        std::advance(r, uniformDistirbution(randomGenerator));
        std::swap(*begin, *r);
        ++begin;
        --left;
    }
    return begin;
}