void agregarInvolucrado(struct causa *causaDestinada, struct involucrados *nuevoInvolucrado){

    int i, nuevoTam = causaDestinada->tamInvolucrados + 1;
    struct involucrados **nuevoArreglo;

    // revisamos que causa destinada y el nuevo incrolucrado tengan datos
    if (causaDestinada == NULL || nuevoInvolucrado == NULL) {
        printf("Error: la causa o el involucrado están vacíos.\n");
        return;
    }

    // asignamos memoria y validamos que esta sea correcta
    nuevoArreglo = (struct involucrados **) malloc(sizeof(struct involucrados *) * nuevoTam);
    if (nuevoArreglo == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }

    // recorre el array hasta el ultimo dato
    for(i = 0; i < causaDestinada->tamInvolucrados; i++){
        nuevoArreglo[i] = causaDestinada->involucrados[i];
    }

    // se añade al final el nuevo involucrado
    nuevoArreglo[causaDestinada->tamInvolucrados] = nuevoInvolucrado;

    // se libera memoria del array anterior
    if(causaDestinada->involucrados != NULL){
        free(causaDestinada->involucrados);
    }

    causaDestinada->involucrados = nuevoArreglo;
    causaDestinada->tamInvolucrados = nuevoTam;
}
