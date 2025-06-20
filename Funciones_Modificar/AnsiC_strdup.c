char* duplicarCadena(char* origen) {
    char* destino;
    int longitud;
    int i;

    if (origen == NULL) {
        return NULL;
    }

    /* Calcular longitud de la cadena */
    longitud = 0;
    while (origen[longitud] != '\0') {
        longitud++;
    }

    /* Asignar memoria */
    destino = (char*)malloc((longitud + 1) * sizeof(char));
    if (destino == NULL) {
        return NULL;
    }

    /* Copiar cadena */
    for (i = 0; i <= longitud; i++) {
        destino[i] = origen[i];
    }

    return destino;
}
