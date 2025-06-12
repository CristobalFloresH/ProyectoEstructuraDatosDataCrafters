void agregarPersonas(struct ministerio **ministerio, struct persona *nuevaPersona) {
    if (ministerio == NULL || nuevaPersona == NULL) {
        printf("Error: ministerio o persona inválidos.\n");
        return;
    }

    // Si el árbol está vacío, se inicializa
    if ((*ministerio)->personas == NULL) {
        struct nodoPersonasABB *nuevoNodo = (struct nodoPersonasABB *)malloc(sizeof(struct nodoPersonasABB));
        if (nuevoNodo == NULL) {
            printf("Error al asignar memoria.\n");
            return;
        }
        nuevoNodo->datosPersona = nuevaPersona;
        nuevoNodo->izquierda = NULL;
        nuevoNodo->derecha = NULL;
        (*ministerio)->personas = nuevoNodo;
        return;
    }

    // Reutilizamos la lógica anterior de inserción en ABB
    struct nodoPersonasABB *actual = (*ministerio)->personas;
    struct nodoPersonasABB *padre = NULL;
    int cmp = 0;

    while (actual != NULL) {
        cmp = strcmp(nuevaPersona->rut, actual->datosPersona->rut);
        if (cmp == 0) {
            printf("Esta persona ya se registró.\n");
            return;
        }
        padre = actual;
        if (cmp < 0) {
            if (actual->izquierda == NULL) break;
            actual = actual->izquierda;
        } else {
            if (actual->derecha == NULL) break;
            actual = actual->derecha;
        }
    }

    struct nodoPersonasABB *nuevoNodo = (struct nodoPersonasABB *)malloc(sizeof(struct nodoPersonasABB));
    if (nuevoNodo == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }
    nuevoNodo->datosPersona = nuevaPersona;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;

    if (cmp < 0) {
        padre->izquierda = nuevoNodo;
    } else {
        padre->derecha = nuevoNodo;
    }
    printf("La persona fue agregara con exito.\n");
}
