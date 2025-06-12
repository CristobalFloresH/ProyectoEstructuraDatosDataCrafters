struct nodoPersonasABB* minimo(struct nodoPersonasABB *arbol) { // esta funcion busca el rut mas bajo, es decir el nodo mas a la izquierda en el arbol.
    while (arbol != NULL && arbol->izquierda != NULL)
        arbol = arbol->izquierda; // simplemente nos movemos a la izquierda hasta encontrar el menor.
    return arbol;
}

void eliminarPersona(struct nodoPersonasABB **personas, char *rut) {
    if (personas == NULL || *personas == NULL) {
        printf("No se encontraron personas\n");
        return;
    }

    int comparar = strcmp(rut, (*personas)->datosPersona->rut);

    if (comparar < 0) {
        eliminarPersona(&((*personas)->izquierda), rut);
    }
    else if (comparar > 0) {
        eliminarPersona(&((*personas)->derecha), rut);
    }
    else {
        struct nodoPersonasABB *nodoEliminar = *personas;

        if (nodoEliminar->izquierda == NULL) {
            *personas = nodoEliminar->derecha;
            liberarPersona(nodoEliminar->datosPersona);
            free(nodoEliminar);
        }
        else if (nodoEliminar->derecha == NULL) {
            *personas = nodoEliminar->izquierda;
            liberarPersona(nodoEliminar->datosPersona);
            free(nodoEliminar);
        }
        else {
            struct nodoPersonasABB *minNodo = minimo(nodoEliminar->derecha);

            struct persona *aux = nodoEliminar->datosPersona;
            nodoEliminar->datosPersona = minNodo->datosPersona;
            minNodo->datosPersona = aux;

            eliminarPersona(&(nodoEliminar->derecha), aux->rut);
        }
    }
    printf("Persona eliminada correctamente.");
}
