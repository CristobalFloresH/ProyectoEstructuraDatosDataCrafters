struct involucrados* buscarInvolucradoPorRut(struct involucrados **involucrados, int tam, char *rut) {
    int i;
    
    if (involucrados == NULL) return NULL;
    
    for (i = 0; i < tam; i++) {
        if (involucrados[i] != NULL && involucrados[i]->persona != NULL) {
            if (strcmp(involucrados[i]->persona->rut, rut) == 0) {
                return involucrados[i];
            }
        }
    }
    return NULL;
}
