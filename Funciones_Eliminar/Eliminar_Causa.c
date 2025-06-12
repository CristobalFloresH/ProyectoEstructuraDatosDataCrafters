void eliminarCausa(struct nodoCausas **listaCausa, char *ruc) {
    if (listaCausa == NULL) {
        printf("No se han encontrado causas.\n");
        return;
    }

    struct nodoCausas *aEliminar = buscarNodoCausa(*listaCausa, ruc);
    if (aEliminar == NULL) {
        printf("No se han encontrado causas.\n");
        return;
    }

    if (aEliminar != NULL) {
        reenlazarCausas(listaCausa, aEliminar);
        liberarCausa(aEliminar->datosCausa);
        free(aEliminar);
        aEliminar = NULL;
        printf("Causa eliminada correctamente.\n");
    }
    else
        printf("No se encontró una causa con ese RUC.\n");
}
