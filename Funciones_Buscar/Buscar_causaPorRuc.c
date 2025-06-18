struct causa *buscarCausaPorRuc(struct nodoCausas *causas, char *rucBuscado) {
    struct nodoCausas *actual;
    //si la lista de causas o el ruc buscado es null, retorna null ya que no hay nada que buscar
    if (causas == NULL || rucBuscado == NULL) return NULL;

    actual = causas;

    //se recorre lista circular hasta encontrar el ruc igual, si no se encuentra retorna null
    do {
        if (strcmp(actual->datosCausa->ruc, rucBuscado) == 0)
        {
            return actual->datosCausa;
        }

        actual = actual->siguiente;
    } while (actual != causas);

    return NULL;
}
