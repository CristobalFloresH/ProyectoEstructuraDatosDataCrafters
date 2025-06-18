int eliminarDenuncia(struct nodoDenuncias **listaDenuncia, char *ruc) {
    struct nodoDenuncias *actual = *listaDenuncia;
    if (listaDenuncia == NULL) {
        return 0;
    }

    while (actual != NULL) {
        if (strcmp(actual->datosDenuncia->ruc, ruc) == 0) {
            reenlazarDenuncias(listaDenuncia, actual);
            liberarDenuncia(actual->datosDenuncia);
            free(actual);
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}
