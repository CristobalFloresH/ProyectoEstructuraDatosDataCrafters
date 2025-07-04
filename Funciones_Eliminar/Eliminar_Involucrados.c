void compactarInvolucrados(struct involucrados **involucrados, int *tam) {
    int i, j = 0;

    if (involucrados == NULL || tam == NULL || *tam == 0)
        return;

    for (i = 0; i < *tam; i++) {
        if (involucrados[i] != NULL) {
            if (i != j) {
                involucrados[j] = involucrados[i];
                involucrados[i] = NULL;
            }
            j++;
        }
    }
    *tam = j;
}

int eliminarInvolucradoPorRut(struct involucrados **involucrados, int tam, char *rut) {
    struct involucrados *involucrado;
    int i;
    involucrado = buscarInvolucradoPorRut(involucrados, tam, rut);
    if (involucrado == NULL) {
        return 0;
    }

    if (involucrado->tipoInvolucrado == 2 && involucrado->datosImputados != NULL) {
        liberarDatosImputados(involucrado->datosImputados);
        involucrado->datosImputados = NULL;
    }
    involucrado->persona = NULL;

    for (i = 0; i < tam && involucrados[i] != NULL; i++) {
  		if(involucrados[i]->persona->rut ==  NULL){
          free(involucrados[i]);
          involucrados[i] = NULL;
          compactarInvolucrados(involucrados, &tam);
        }

        if (involucrados[i] == involucrado) {
            free(involucrados[i]);
            involucrados[i] = NULL;
            compactarInvolucrados(involucrados, &tam);
            return 1;
        }
    }
    return 0;
}


int eliminarInvolucrado(struct nodoCausas **listaCausas, char *ruc, char *rut) {
    struct nodoCausas *actual;
    struct nodoCausas *inicio;

    if (listaCausas == NULL || *listaCausas == NULL) {
        return 0;
    }

    actual = *listaCausas;
    inicio = *listaCausas;

    do {
        if (actual->datosCausa != NULL && strcmp(actual->datosCausa->ruc, ruc) == 0 && actual->datosCausa->involucrados != NULL) {

            return eliminarInvolucradoPorRut(actual->datosCausa->involucrados, actual->datosCausa->tamInvolucrados, rut);
            }

        actual = actual->siguiente;
    } while (actual != inicio);

    return 0;
}
