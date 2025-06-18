void mostrarRucDePersonaBuscada(struct ministerio *ministerio, char *rutBuscado)
{
    int minimoUnEncontrado;
    int i;
    struct nodoCausas *actual;
    struct nodoDatosCarpetas *actualCarpeta;
    int encontrado;

    if (ministerio == NULL || ministerio->causas == NULL)
    {
        printf("No se encontraron causas en el sistema\n");
        return;
    }

    minimoUnEncontrado = 0;
    actual = ministerio->causas;

    do
    {
        encontrado = 0;

        // Buscar en involucrados
        for (i = 0; i < actual->datosCausa->tamInvolucrados; i++)
        {
            if (actual->datosCausa->involucrados[i] != NULL &&
                actual->datosCausa->involucrados[i]->persona != NULL &&
                actual->datosCausa->involucrados[i]->persona->rut != NULL &&
                strcmp(actual->datosCausa->involucrados[i]->persona->rut, rutBuscado) == 0)
            {
                encontrado = 1;
            }
        }

        // Buscar en denuncia (denunciante y denunciado)
        if (actual->datosCausa->denuncia != NULL)
        {
            if (actual->datosCausa->denuncia->denunciante != NULL &&
                actual->datosCausa->denuncia->denunciante->rut != NULL &&
                strcmp(actual->datosCausa->denuncia->denunciante->rut, rutBuscado) == 0)
            {
                encontrado = 1;
            }
            if (actual->datosCausa->denuncia->denunciado != NULL &&
                actual->datosCausa->denuncia->denunciado->rut != NULL &&
                strcmp(actual->datosCausa->denuncia->denunciado->rut, rutBuscado) == 0)
            {
                encontrado = 1;
            }
        }

        // Buscar en datosPersona de todas las carpetas investigativas de la causa
        actualCarpeta = actual->datosCausa->datosCarpetas;
        while (actualCarpeta != NULL)
        {
            if (actualCarpeta->datosCarpeta != NULL &&
                actualCarpeta->datosCarpeta->datosPersona != NULL &&
                actualCarpeta->datosCarpeta->datosPersona->rut != NULL &&
                strcmp(actualCarpeta->datosCarpeta->datosPersona->rut, rutBuscado) == 0)
            {
                encontrado = 1;
            }
            actualCarpeta = actualCarpeta->siguiente;
        }

        if (encontrado == 1)
        {
            printf("La persona con RUT %s esta en la causa con RUC: %s\n", rutBuscado, actual->datosCausa->ruc);
            minimoUnEncontrado = 1;
        }

        actual = actual->siguiente;
    } while (actual != ministerio->causas);

    if (minimoUnEncontrado == 0)
    {
        printf("La persona con RUT %s no fue encontrada en el sistema.\n", rutBuscado);
    }
}
