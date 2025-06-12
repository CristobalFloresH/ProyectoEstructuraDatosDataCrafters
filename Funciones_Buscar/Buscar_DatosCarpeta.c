struct nodoDatosCarpetas *buscarDatosCarpetaPorTipo(struct causa *causa, int tipoDeDato)
{
    struct nodoDatosCarpetas *listaResultado = NULL;
    struct nodoDatosCarpetas *nodoActualCarpeta = NULL;

    if (causa == NULL || causa->datosCarpetas == NULL)
    {
        return NULL;
    }

    nodoActualCarpeta = causa->datosCarpetas;

    while (nodoActualCarpeta != NULL)
    {
        if (nodoActualCarpeta->datosCarpeta != NULL &&
            nodoActualCarpeta->datosCarpeta->tipoDeDato == tipoDeDato)
        {
            struct nodoDatosCarpetas *nuevoNodoResultado = (struct nodoDatosCarpetas *)malloc(sizeof(struct nodoDatosCarpetas));
            if (nuevoNodoResultado == NULL)
            {
                return NULL;
            }
            // Apunta al mismo datosCarpeta original (NO se hace copia profunda)
            nuevoNodoResultado->datosCarpeta = nodoActualCarpeta->datosCarpeta;
            nuevoNodoResultado->siguiente = NULL;
            nuevoNodoResultado->anterior = NULL;

            // Si la lista de resultados está vacía, este es el primer nodo
            if (listaResultado == NULL)
            {
                listaResultado = nuevoNodoResultado;
            }
            else
            {
                // Si no, recorre la lista resultado hasta el último nodo
                struct nodoDatosCarpetas *nodoFinal = listaResultado;
                while (nodoFinal->siguiente != NULL)
                {
                    nodoFinal = nodoFinal->siguiente;
                }
                // Enlaza el nuevo nodo al final
                nodoFinal->siguiente = nuevoNodoResultado;
                nuevoNodoResultado->anterior = nodoFinal;
            }
        }
        nodoActualCarpeta = nodoActualCarpeta->siguiente;
    }
    return listaResultado;
}
