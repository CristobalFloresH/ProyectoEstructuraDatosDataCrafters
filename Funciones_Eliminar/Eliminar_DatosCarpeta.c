int eliminarCarpetaDeCausa(struct nodoCausas **listaCausas, char *ruc) {
    struct nodoCausas *causa;
    struct nodoDatosCarpetas *actualCarpeta;
    struct nodoDatosCarpetas *sig;

    if (listaCausas == NULL || *listaCausas == NULL) {
        return 0;
    }

    causa = buscarNodoCausa(*listaCausas, ruc);
    if (causa == NULL) {
        return 0;
    }

    actualCarpeta = causa->datosCausa->datosCarpetas;
    while (actualCarpeta != NULL) {
        sig = actualCarpeta->siguiente;
        liberarDatosCarpeta(actualCarpeta->datosCarpeta);
        free(actualCarpeta);
        actualCarpeta = sig;
    }
    causa->datosCausa->datosCarpetas = NULL;
    return 1;
}
