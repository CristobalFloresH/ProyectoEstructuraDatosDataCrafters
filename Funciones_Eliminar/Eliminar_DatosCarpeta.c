void eliminarCarpetaDeCausa(struct nodoCausas **listaCausas, char *ruc) {
    struct nodoCausas *causa;
    struct nodoDatosCarpetas *actualCarpeta;
    struct nodoDatosCarpetas *sig;

    if (listaCausas == NULL) {
        printf("No hay causas registradas.\n");
        return;
    }

    causa = buscarNodoCausa(*listaCausas, ruc);
    if (causa == NULL) {
        printf("No se encontro una causas con ese RUC.\n");
        return;
    }

    actualCarpeta = causa->datosCausa->datosCarpetas;
    while (actualCarpeta != NULL) {
        sig = actualCarpeta->siguiente;
        liberarDatosCarpeta(actualCarpeta->datosCarpeta);
        free(actualCarpeta);
        actualCarpeta = sig;
    }

    causa->datosCausa->datosCarpetas = NULL;
    printf("Carpetas eliminadas correctamente.\n");
}
