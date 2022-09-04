//
// Created by zlysm on 9/4/22.
//

#ifndef DSA_STACK_APPLICATION_H
#define DSA_STACK_APPLICATION_H

//进制转换
void convert(Stack<char> &S, long long n, int base);

//括号匹配
void trim(const char exp[], int &lo, int &hi);

int divide(const char exp[], int lo, int hi);

bool paren(const char exp[], int lo, int hi);

#endif //DSA_STACK_APPLICATION_H
