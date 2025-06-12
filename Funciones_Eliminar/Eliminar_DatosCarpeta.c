void eliminarCarpetaDeCausa(struct nodoCausas **listaCausas, char *ruc) {
    if (listaCausas == NULL) {
        printf("No hay causas registradas.\n");
        return;
    }

    struct nodoCausas *causa = buscarNodoCausa(*listaCausas, ruc);
    if (causa == NULL) {
        printf("No se encontro una causas con ese RUC.\n");
        return;
    }

    struct nodoDatosCarpetas *actualCarpeta = causa->datosCausa->datosCarpetas;
    while (actualCarpeta != NULL) {
        struct nodoDatosCarpetas *sig = actualCarpeta->siguiente;
        liberarDatosCarpeta(actualCarpeta->datosCarpeta);
        free(actualCarpeta);
        actualCarpeta = sig;
    }

    causa->datosCausa->datosCarpetas = NULL;
    printf("Carpetas eliminadas correctamente.\n");
}
