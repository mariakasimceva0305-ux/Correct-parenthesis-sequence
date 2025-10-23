#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/cbs.h"

void test_n0() {
    iterator_t iter;
    nachalo_iteracii(&iter, 0);
    assert(poluchit_tekuyee(&iter) != NULL);
    assert(poluchit_tekuyee(&iter)->dlina == 0);
    zakonchit_iteraciyu(&iter);
    printf("n=0 test proyden\n");
}

void test_n1() {
    iterator_t iter;
    nachalo_iteracii(&iter, 1);
    assert(strcmp(poluchit_tekuyee(&iter)->skobki, "()") == 0);
    assert(est_li_sleduyushiy(&iter) == 0);
    zakonchit_iteraciyu(&iter);
    printf("n=1 test proyden\n");
}

void test_n2() {
    iterator_t iter;
    nachalo_iteracii(&iter, 2);
    
    assert(strcmp(poluchit_tekuyee(&iter)->skobki, "(())") == 0);
    assert(est_li_sleduyushiy(&iter) == 1);
    
    pereyti_k_sleduyushemu(&iter);
    assert(strcmp(poluchit_tekuyee(&iter)->skobki, "()()") == 0);
    assert(est_li_sleduyushiy(&iter) == 0);
    
    zakonchit_iteraciyu(&iter);
    printf("n=2 test proyden\n");
}

void test_n3() {
    iterator_t iter;
    nachalo_iteracii(&iter, 3);
    
    printf("Pervaya: %s\n", poluchit_tekuyee(&iter)->skobki);
    
    const char* expected[] = {"((()))", "(()())", "(())()", "()(())", "()()()"};
    int count = 0;
    
    while (poluchit_tekuyee(&iter) != NULL) {
        printf("Polucheno: %s, Ozhidalos: %s\n", poluchit_tekuyee(&iter)->skobki, expected[count]);
        assert(strcmp(poluchit_tekuyee(&iter)->skobki, expected[count]) == 0);
        count++;
        if (est_li_sleduyushiy(&iter)) {
            pereyti_k_sleduyushemu(&iter);
        } else {
            break;
        }
    }
    
    assert(count == 5);
    zakonchit_iteraciyu(&iter);
    printf("n=3 test proyden\n");
}

void test_validnost() {
    iterator_t iter;
    nachalo_iteracii(&iter, 5);
    
    while (poluchit_tekuyee(&iter) != NULL) {
        const my_bs_t* val = poluchit_tekuyee(&iter);
        int balans = 0;
        for (unsigned i = 0; i < val->dlina; i++) {
            if (val->skobki[i] == '(') balans++;
            else balans--;
            assert(balans >= 0);
        }
        assert(balans == 0);
        
        if (est_li_sleduyushiy(&iter)) {
            pereyti_k_sleduyushemu(&iter);
        } else {
            break;
        }
    }
    
    zakonchit_iteraciyu(&iter);
    printf("validnost test proyden\n");
}

int main() {
    test_n0();
    test_n1();
    test_n2();
    test_n3();
    test_validnost();
    printf("Vse testy proydeny uspeshno!\n");
    return 0;
}