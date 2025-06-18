struct involucrados* buscarImputadoEnCausa(struct causa *c, char *rutImputado) {
    int i;
    struct involucrados *inv;
    
    if (c == NULL || rutImputado == NULL) {
        printf("Error: causa o RUT inválido.\n");
        return NULL;
    }
    for (i = 0; i < c->tamInvolucrados; i++) {
        inv = c->involucrados[i];
        if (inv != NULL &&
            inv->tipoInvolucrado == 2 && // Tipo imputado
            inv->persona != NULL &&
            strcmp(inv->persona->rut, rutImputado) == 0) {
            return inv;
            }
    }
    return NULL;
}
