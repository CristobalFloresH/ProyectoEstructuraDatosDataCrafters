void eliminarDenuncia(struct nodoDenuncias **listaDenuncia, char *ruc) {
    if (listaDenuncia == NULL) {
        printf("No se han encontrado denuncias");
        return;
    }

    struct nodoDenuncias *actual = *listaDenuncia;

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
