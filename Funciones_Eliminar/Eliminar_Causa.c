int eliminarCausa(struct nodoCausas **listaCausa, char *ruc) {
    struct nodoCausas *aEliminar = buscarNodoCausa(*listaCausa, ruc);
    if (listaCausa == NULL) {
        return 0;
    }

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
