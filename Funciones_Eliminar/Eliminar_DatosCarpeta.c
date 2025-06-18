int eliminarCarpetaDeCausa(struct nodoCausas **listaCausas, char *ruc) {
    struct nodoCausas *causa = buscarNodoCausa(*listaCausas, ruc);
    struct nodoDatosCarpetas *actualCarpeta = causa->datosCausa->datosCarpetas;
    struct nodoDatosCarpetas *sig = actualCarpeta->siguiente;

    if (listaCausas == NULL) {
        return 0;
    }

    if (causa == NULL) {
        return 0;
    }
    while (actualCarpeta != NULL) {
        liberarDatosCarpeta(actualCarpeta->datosCarpeta);
        free(actualCarpeta);
        actualCarpeta = sig;
    }

    causa->datosCausa->datosCarpetas = NULL;
    return 1;
}
