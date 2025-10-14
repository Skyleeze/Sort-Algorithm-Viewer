void triInsertion(int* tab, int taille, void (*render)()) {
    int j;
    for(int i = 1; i<taille;i++) {
        int x = tab[i];
        for(j = i; tab[j-1] > x; j--) {
            tab[j] = tab[j-1];
            //if (render){ render(); } // Mettre ici pour aumgenter la précision
        }
        if (render){ render(); } // Mettre ici pour diminuer la complexité
        tab[j] = x;

    }
}