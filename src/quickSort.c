#include <stdbool.h>
void swap(int* a, int* b, bool needToShow ,void (*render)(int* x, int* y, bool show )) {
    int temp = *b;
    *b = *a;
    *a = temp;
    if (render) {
        render(a,b, needToShow);
    }
}


void quickSort(int* tab, int taille, void (*render)(int* x, int* y, bool show)) {
    if (taille <= 1) return;
    int pivot = tab[0];
    int iPivot = 0;
    
    for (int i = 1; i<taille; i++) {
        if (tab[i] <= pivot) {
            if (i!=iPivot+1) {
                swap(&tab[iPivot+1],&tab[i], false ,render);
            }
            swap(&tab[iPivot], &tab[iPivot+1], true , render);
            iPivot++;
        }
    }
    if (iPivot > 0) {
        quickSort(tab,iPivot, render);
    }
    if (taille-iPivot-1 > 0) {quickSort(&tab[iPivot+1],taille-iPivot-1, render);} 

}


