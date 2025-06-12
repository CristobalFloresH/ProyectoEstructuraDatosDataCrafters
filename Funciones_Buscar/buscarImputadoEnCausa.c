struct involucrados* buscarImputadoEnCausa(struct causa *c, char *rutImputado) {
    if (c == NULL || rutImputado == NULL) {
        printf("Error: causa o RUT inválido.\n");
        return NULL;
    }
    int i;
    for (i = 0; i < c->tamInvolucrados; i++) {
        struct involucrados *inv = c->involucrados[i];
        if (inv != NULL &&
            inv->tipoInvolucrado == 2 && // Tipo imputado
            inv->persona != NULL &&
            strcmp(inv->persona->rut, rutImputado) == 0) {
            return inv;
            }
    }
    return NULL;
}
