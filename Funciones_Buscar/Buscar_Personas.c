void agregarDenunciaAPersona(char *rut ,struct nodoPersonasABB *nodoPersonasABB, struct denuncia *nuevaDenuncia){
    // se busca a la persona usando su rut
    struct persona *personaEncontrada = buscarPersonaPorRut(nodoPersonasABB, rut);

    // si no se encuentra la persona, se informa al usuario
    if(personaEncontrada == NULL){
        printf("No se encontraron personas\n");
        return;
    }

    // se asigna memoria y se verifica que haya sido exitoso
    struct nodoDenuncias *nuevoNodo = (struct nodoDenuncias*)malloc(sizeof(struct nodoDenuncias));
    if(nuevoNodo == NULL){
        printf("Error al asignar memoria");
        return;
    }

    // se asignan valores a nuevo nodo
    nuevoNodo->datosDenuncia = nuevaDenuncia;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    struct nodoDenuncias *actual = personaEncontrada->denuncias;
    if(actual == NULL){
        // denuncias vacia, se agrega de primero
        personaEncontrada->denuncias = nuevoNodo;
    } else {
        // se recorre hasta el final la lista de denuncias
        while(actual->siguiente != NULL){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
        nuevoNodo->anterior = actual;
    }
}
