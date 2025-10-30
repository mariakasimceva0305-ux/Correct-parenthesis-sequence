#ifndef CBS_H
#define CBS_H

typedef struct {
    char* skobki;
    unsigned dlina;
} my_bs_t;

typedef struct {
    my_bs_t tekuyee_znachenie;
    char* sleduyushaya_posledovatelnost;
    unsigned N_param;
    int zakoncheno_li;
} iterator_t;

void nachalo_iteracii(iterator_t *moj_iterator, unsigned n);
const my_bs_t *poluchit_tekuyee(const iterator_t *moj_iterator);
int est_li_sleduyushiy(const iterator_t *moj_iterator);
void pereyti_k_sleduyushemu(iterator_t *moj_iterator);
void zakonchit_iteraciyu(iterator_t *moj_iterator);

#endif
