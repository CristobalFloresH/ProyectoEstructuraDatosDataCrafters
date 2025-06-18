void agregarCarpetaInvestigativa(struct nodoDatosCarpetas **carpetas, struct datosCarpeta *nuevaCarpeta) {
    struct nodoDatosCarpetas *nuevoNodo;
    struct nodoDatosCarpetas *actual;

    // Revisamos que la nueva carpeta exista
    if(nuevaCarpeta == NULL){
        printf("Nueva carpeta no existe\n");
        return;
    }

    // Definimos nuevo nodo para asignarle nuevaCarpeta y corroboramos que se asigne memoria
    nuevoNodo = (struct nodoDatosCarpetas *)malloc(sizeof(struct nodoDatosCarpetas));
    if(nuevoNodo == NULL){
        printf("Error al asignar memoria para el nuevo nodo\n");
        return;
    }

    // Se asignan los campos al nuevo nodo
    nuevoNodo->datosCarpeta = nuevaCarpeta;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    // Si está vacía, asignar al inicio
    if(*carpetas == NULL){
        *carpetas = nuevoNodo;
    } else {
        // Recorre hasta el final de la lista
        actual = *carpetas;
        while(actual->siguiente != NULL) {
            actual = actual->siguiente;
        }

        // Asigna los punteros al nuevo nodo
        actual->siguiente = nuevoNodo;
        nuevoNodo->anterior = actual;
    }
    printf("Carpeta agregada exitosamente.\n");
}
