void reenlazarCausas(struct nodoCausas **listaCausas, struct nodoCausas *nodoEliminar) {
    if (*listaCausas == NULL || nodoEliminar == NULL) return;

    // Si solo hay un nodo en la lista
    if (nodoEliminar->siguiente == nodoEliminar && nodoEliminar->anterior == nodoEliminar) {
        *listaCausas = NULL;
        return;
    }

    // Enlazamos
    nodoEliminar->anterior->siguiente = nodoEliminar->siguiente;
    nodoEliminar->siguiente->anterior = nodoEliminar->anterior;

    // Si el nodo a eliminar es el nodo apuntado por lista (inicio), movemos el puntero
    if (*listaCausas == nodoEliminar) {
        *listaCausas = nodoEliminar->siguiente;
    }
}
void reenlazarDenuncias(struct nodoDenuncias **listaDenuncias, struct nodoDenuncias *nodoEliminar) {
    if (listaDenuncias == NULL || *listaDenuncias == NULL || nodoEliminar == NULL) return;

    if (nodoEliminar->anterior == NULL && nodoEliminar->siguiente == NULL) {
        *listaDenuncias = NULL;
        return;
    }

    if (*listaDenuncias == nodoEliminar) {
        *listaDenuncias = nodoEliminar->siguiente;
    }

    if (nodoEliminar->anterior != NULL)
        nodoEliminar->anterior->siguiente = nodoEliminar->siguiente;

    if (nodoEliminar->siguiente != NULL)
        nodoEliminar->siguiente->anterior = nodoEliminar->anterior;
}

void reenlazarDatosCarpeta(struct nodoDatosCarpetas **listaCarpetas, struct nodoDatosCarpetas *nodoEliminar) {
    if (*listaCarpetas == NULL || nodoEliminar == NULL) return;

    if (*listaCarpetas == nodoEliminar) {
        *listaCarpetas = nodoEliminar->siguiente;
        if (*listaCarpetas != NULL) {
            (*listaCarpetas)->anterior = NULL;
        }
    } else {
        if (nodoEliminar->anterior != NULL) {
            nodoEliminar->anterior->siguiente = nodoEliminar->siguiente;
        }
        if (nodoEliminar->siguiente != NULL) {
            nodoEliminar->siguiente->anterior = nodoEliminar->anterior;
        }
    }
}
