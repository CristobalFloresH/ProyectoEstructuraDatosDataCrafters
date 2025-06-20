struct nodoPersonasABB* minimo(struct nodoPersonasABB *arbol) {
    while (arbol != NULL && arbol->izquierda != NULL)
        arbol = arbol->izquierda;
    return arbol;
}
int eliminarPersona(struct nodoPersonasABB **personas, char *rut) {
    int comparar;
    struct nodoPersonasABB *nodoEliminar;
    struct nodoPersonasABB *minNodo;
    struct persona *aux;

    if (personas == NULL || *personas == NULL) {
        return 0;
    }

    comparar = strcmp(rut, (*personas)->datosPersona->rut);

    if (comparar < 0) {
        return eliminarPersona(&((*personas)->izquierda), rut);
    } else if (comparar > 0) {
        return eliminarPersona(&((*personas)->derecha), rut);
    } else {
        nodoEliminar = *personas;

        if (nodoEliminar->izquierda == NULL) {
            *personas = nodoEliminar->derecha;
            liberarPersona(nodoEliminar->datosPersona);
            free(nodoEliminar);

        } else if (nodoEliminar->derecha == NULL) {
            *personas = nodoEliminar->izquierda;
            liberarPersona(nodoEliminar->datosPersona);
            free(nodoEliminar);

        } else {
            minNodo = minimo(nodoEliminar->derecha);
            aux = nodoEliminar->datosPersona;
            nodoEliminar->datosPersona = minNodo->datosPersona;
            minNodo->datosPersona = aux;
            return eliminarPersona(&(nodoEliminar->derecha), aux->rut);
        }
        return 1;
    }
    return 0;
}
