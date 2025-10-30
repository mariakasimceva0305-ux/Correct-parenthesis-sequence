#include <stdlib.h>
#include <string.h>
#include "../include/cbs.h"

static int nayti_sleduyushuyu_posledovatelnost(char* seq, unsigned n) {
    int open = 0;
    int close = 0;

    for (int i = 2*n - 1; i >= 0; i--) {
        if (seq[i] == '(') {
            open++;
            if (close > open) {
                
                // Оставшаяся часть - минимальная ПСП
                int remaining = 2*n - i - 1;
                int open_needed = (remaining - (open - close)) / 2;
                
                for (int j = i + 1; j < i + 1 + open_needed; j++)
                    seq[j] = '(';
                for (int j = i + 1 + open_needed; j < 2*n; j++)
                    seq[j] = ')';
                    
                return 1;
            }
        } else {
            close++;
        }
    }
    return 0; 
}

void nachalo_iteracii(iterator_t *moj_iterator, unsigned n) {
    moj_iterator->N_param = n;
    moj_iterator->zakoncheno_li = 0;
    moj_iterator->sleduyushaya_posledovatelnost = NULL;

    if (n == 0) {
        moj_iterator->tekuyee_znachenie.skobki = (char*)malloc(1);
        moj_iterator->tekuyee_znachenie.skobki[0] = '\0';
        moj_iterator->tekuyee_znachenie.dlina = 0;
        return;
    }

    // Первая ПСП: "((...))"
    moj_iterator->tekuyee_znachenie.skobki = (char*)malloc(2*n + 1);
    moj_iterator->tekuyee_znachenie.dlina = 2*n;
    for (unsigned i = 0; i < n; i++) {
        moj_iterator->tekuyee_znachenie.skobki[i] = '(';
    }
    for (unsigned i = n; i < 2*n; i++) {
        moj_iterator->tekuyee_znachenie.skobki[i] = ')';
    }
    moj_iterator->tekuyee_znachenie.skobki[2*n] = '\0';

    // Следующая псп
    moj_iterator->sleduyushaya_posledovatelnost = (char*)malloc(2*n + 1);
    memcpy(moj_iterator->sleduyushaya_posledovatelnost, 
           moj_iterator->tekuyee_znachenie.skobki, 2*n + 1);

    if (!nayti_sleduyushuyu_posledovatelnost(moj_iterator->sleduyushaya_posledovatelnost, n)) {
        free(moj_iterator->sleduyushaya_posledovatelnost);
        moj_iterator->sleduyushaya_posledovatelnost = NULL;
    }
}

const my_bs_t *poluchit_tekuyee(const iterator_t *moj_iterator) {
    if (moj_iterator->zakoncheno_li) return NULL;
    return &(moj_iterator->tekuyee_znachenie);
}

int est_li_sleduyushiy(const iterator_t *moj_iterator) {
    if (moj_iterator->zakoncheno_li) return 0;
    return moj_iterator->sleduyushaya_posledovatelnost != NULL;
}

void pereyti_k_sleduyushemu(iterator_t *moj_iterator) {
    if (moj_iterator->zakoncheno_li || moj_iterator->sleduyushaya_posledovatelnost == NULL) {
        moj_iterator->zakoncheno_li = 1;
        return;
    }

    // Следующая копирование в текущую
    memcpy(moj_iterator->tekuyee_znachenie.skobki, 
           moj_iterator->sleduyushaya_posledovatelnost, 
           2*moj_iterator->N_param + 1);

    // следующая
    if (!nayti_sleduyushuyu_posledovatelnost(moj_iterator->sleduyushaya_posledovatelnost, 
                                           moj_iterator->N_param)) {
        free(moj_iterator->sleduyushaya_posledovatelnost);
        moj_iterator->sleduyushaya_posledovatelnost = NULL;
    }
}

void zakonchit_iteraciyu(iterator_t *moj_iterator) {
    if (moj_iterator->tekuyee_znachenie.skobki != NULL) {
        free(moj_iterator->tekuyee_znachenie.skobki);
        moj_iterator->tekuyee_znachenie.skobki = NULL;
    }
    if (moj_iterator->sleduyushaya_posledovatelnost != NULL) {
        free(moj_iterator->sleduyushaya_posledovatelnost);
        moj_iterator->sleduyushaya_posledovatelnost = NULL;
    }
    moj_iterator->zakoncheno_li = 1;
}
