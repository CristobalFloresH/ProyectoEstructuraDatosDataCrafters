int eliminarCausa(struct nodoCausas **listaCausa, char *ruc) {
    struct nodoCausas *aEliminar;

    if (listaCausa == NULL || *listaCausa == NULL) {
        return 0;
    }

    aEliminar = buscarNodoCausa(*listaCausa, ruc);
    if (aEliminar == NULL) {
        return 0;
    }

    if (aEliminar != NULL) {
        reenlazarCausas(listaCausa, aEliminar);
        liberarCausa(aEliminar->datosCausa);
        free(aEliminar);
        aEliminar = NULL;
        return 1;
    }
    return 0;
}
