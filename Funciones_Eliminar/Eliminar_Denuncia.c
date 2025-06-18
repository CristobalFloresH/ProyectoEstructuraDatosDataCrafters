void eliminarDenuncia(struct nodoDenuncias **listaDenuncia, char *ruc) {
    struct nodoDenuncias *actual;

    if (listaDenuncia == NULL) {
        printf("No se han encontrado denuncias");
        return;
    }

    actual = *listaDenuncia;

    while (actual != NULL) {
        if (strcmp(actual->datosDenuncia->ruc, ruc) == 0) {
            reenlazarDenuncias(listaDenuncia, actual);
            liberarDenuncia(actual->datosDenuncia);
            free(actual);
            printf("Denuncia eliminada correctamente.\n");
            return;
        }
        actual = actual->siguiente;
    }
}
