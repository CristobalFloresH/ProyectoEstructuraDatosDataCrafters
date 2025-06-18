void agregarCausa(struct nodoCausas **listaCausas, struct causa *nuevaCausa){
    struct nodoCausas *nuevoNodo;
    struct nodoCausas *ultimo;

    // Se crea el nuevo Nodo al que se le asignará la nueva causa
    nuevoNodo = (struct nodoCausas *)malloc(sizeof(struct nodoCausas));
    if(nuevoNodo == NULL){
        printf("Error al asignar memoria");
        return;
    }

    // Se le asigna al nuevo nodo la nueva causa
    nuevoNodo->datosCausa = nuevaCausa;

    if(*listaCausas == NULL){
        // Lista vacía, se agrega al inicio
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
        *listaCausas = nuevoNodo;
    } else {
        // Si la lista no está vacía se reenlazan los nodos
        ultimo = (*listaCausas)->anterior;

        nuevoNodo->siguiente = *listaCausas;
        nuevoNodo->anterior = ultimo;

        ultimo->siguiente = nuevoNodo;
        (*listaCausas)->anterior = nuevoNodo;
    }
}
