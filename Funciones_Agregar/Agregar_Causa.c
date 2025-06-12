void agregarCausa(struct nodoCausas **listaCausas, struct causa *nuevaCausa){
    //Se crea el nuevo Nodo al que se le asignara la nueva causa
    struct nodoCausas *nuevoNodo = (struct nodoCausas *)malloc(sizeof(struct nodoCausas));
    if(nuevoNodo == NULL){
        printf("Error al asignar memoria");
        return;
    }

    //Se le asigna al nuevo nodo la nueva causa
    nuevoNodo->datosCausa = nuevaCausa;


    if(*listaCausas == NULL){
        //Lista vacia, se agrega al inicio
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
        *listaCausas = nuevoNodo;

    } else {
        //Si la lista no esta vacia se reenlazan los nodos
        struct nodoCausas *ultimo = (*listaCausas)->anterior;

        nuevoNodo->siguiente = *listaCausas;
        nuevoNodo->anterior = ultimo;

        ultimo->siguiente = nuevoNodo;

        //Se actualiza la lista ya que se paso por referencia
        (*listaCausas)->anterior = nuevoNodo;
    }
}
