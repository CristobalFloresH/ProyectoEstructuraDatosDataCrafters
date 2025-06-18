struct nodoCausas *buscarNodoCausa(struct nodoCausas *causas, char *rucBuscado) {
    struct nodoCausas *actual;
    
    if (causas == NULL || rucBuscado == NULL) return NULL;

    actual = causas;

    do {
        if (strcmp(actual->datosCausa->ruc, rucBuscado) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != causas);

    return NULL;
}
