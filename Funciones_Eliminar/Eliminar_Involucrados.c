void eliminarInvolucradoPorRut(struct involucrados **involucrados, int tam, char *rut) {
    struct involucrados *involucrado;
    int i;

    involucrado = buscarInvolucradoPorRut(involucrados, tam, rut);
    if (involucrado == NULL) {
        printf("No se encontró involucrado con RUT %s.\n", rut);
        return;
    }

    if (involucrado->tipoInvolucrado == 2 && involucrado->datosImputados != NULL) {
        liberarDatosImputados(involucrado->datosImputados);
        involucrado->datosImputados = NULL;
    }

    liberarPersona(involucrado->persona);
    involucrado->persona = NULL;

    for (i = 0; i < tam; i++) {
        if (involucrados[i] == involucrado) {
            free(involucrados[i]);
            involucrados[i] = NULL;
            break;
        }
    }

    printf("Involucrado con RUT %s eliminado correctamente.\n", rut);
}
void eliminarInvolucrado(struct nodoCausas **listaCausas, char *ruc, char *rut) {
    struct nodoCausas *actual;
    struct nodoCausas *inicio;

    if (listaCausas == NULL || *listaCausas == NULL) {
        printf("No hay causas registradas.\n");
        return;
    }

    actual = *listaCausas;
    inicio = *listaCausas;

    do {
        if (actual->datosCausa != NULL &&
            strcmp(actual->datosCausa->ruc, ruc) == 0 &&
            actual->datosCausa->involucrados != NULL) {

            eliminarInvolucradoPorRut(actual->datosCausa->involucrados,
                                      actual->datosCausa->tamInvolucrados,
                                      rut);
            return;
        }

        actual = actual->siguiente;
    } while (actual != inicio);

    printf("No se encontró la causa con RUC %s.\n", ruc);
}

