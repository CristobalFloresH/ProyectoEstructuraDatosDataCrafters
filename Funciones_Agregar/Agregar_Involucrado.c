void agregarInvolucrado(struct causa *causaDestinada, struct involucrados *nuevoInvolucrado){
    int i;
    int nuevoTam;
    struct involucrados **nuevoArreglo;

    nuevoTam = 0;  // Inicialización por seguridad en TurboC

    // Revisamos que causaDestinada y nuevoInvolucrado tengan datos
    if (causaDestinada == NULL || nuevoInvolucrado == NULL) {
        printf("Error: la causa o el involucrado están vacíos.\n");
        return;
    }

    nuevoTam = causaDestinada->tamInvolucrados + 1;

    // Asignamos memoria y validamos que esta sea correcta
    nuevoArreglo = (struct involucrados **) malloc(sizeof(struct involucrados *) * nuevoTam);
    if (nuevoArreglo == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }

    // Recorre el array hasta el último dato
    for(i = 0; i < causaDestinada->tamInvolucrados; i++){
        nuevoArreglo[i] = causaDestinada->involucrados[i];
    }

    // Se añade al final el nuevo involucrado
    nuevoArreglo[causaDestinada->tamInvolucrados] = nuevoInvolucrado;

    // Se libera memoria del array anterior
    if(causaDestinada->involucrados != NULL){
        free(causaDestinada->involucrados);
    }

    causaDestinada->involucrados = nuevoArreglo;
    causaDestinada->tamInvolucrados = nuevoTam;
}
