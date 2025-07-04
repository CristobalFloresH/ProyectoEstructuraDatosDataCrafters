void mostrarTodosInvolucradosCausa(struct causa *causa) {
    int i;
    
    if (causa == NULL) {
        printf("No se encontro la causa seleccionada.\n");
        return;
    }
    if (causa->involucrados == NULL) {
        printf("Esta causa no tiene involucrados registrados.\n");
        return;
    }

    for (i = 0; i < causa->tamInvolucrados; i++)
    {
        //1 = victima, 2 = imputado, 3 = fiscal, 4 = juez
        if (causa->involucrados[i] != NULL)
        {
            printf("\n========================================\n");
            printf("INVOLUCRADO #%d\n", i + 1);
            printf("========================================\n");
            printf("RUT           : %s\n", causa->involucrados[i]->persona->rut);
            printf("Nombre        : %s\n", causa->involucrados[i]->persona->nombre);
            printf("Apellido      : %s\n", causa->involucrados[i]->persona->apellido);
            if (causa->involucrados[i]->tipoInvolucrado == 1) {
                printf("Rol dentro de la causa: Victima\n");
            }
            else if (causa->involucrados[i]->tipoInvolucrado == 2) {
                printf("Rol dentro de la causa: Imputado\n");
                mostrarDatosImputados(causa->involucrados[i]->datosImputados);
            }
            else if (causa->involucrados[i]->tipoInvolucrado == 3) {
                printf("Rol dentro de la causa: Fiscal\n");
            }
            else if (causa->involucrados[i]->tipoInvolucrado == 4) {
                printf("Rol dentro de la causa: Juez\n");
            }
        }
    }

}

void mostrarInvolucradosCausaPorTipo(struct causa *causa, int tipoInvolucrado)
{
    int contador;
    int i;
    
    if (causa == NULL) {
        printf("No se encontro la causa seleccionada.\n");
        return;
    }
    if (causa->involucrados == NULL || causa->tamInvolucrados == 0) {
        printf("Esta causa no tiene involucrados registrados.\n");
        return;
    }

    contador = 0;

    for (i = 0; i < causa->tamInvolucrados; i++)
    {
        if (causa->involucrados[i] != NULL && causa->involucrados[i]->tipoInvolucrado == tipoInvolucrado)
        {
            contador++;
            printf("\n========================================\n");
            printf("INVOLUCRADO #%d\n", contador);
            printf("========================================\n");
            printf("RUT           : %s\n", causa->involucrados[i]->persona->rut);
            printf("Nombre        : %s\n", causa->involucrados[i]->persona->nombre);
            printf("Apellido      : %s\n", causa->involucrados[i]->persona->apellido);

            // Imprime rol textual segun el tipo solicitado
            if (tipoInvolucrado == 1)
                printf("Rol dentro de la causa: Victima\n");
            else if (tipoInvolucrado == 2) {
                printf("Rol dentro de la causa: Imputado\n");
                mostrarDatosImputados(causa->involucrados[i]->datosImputados);
            }
            else if (tipoInvolucrado == 3)
                printf("Rol dentro de la causa: Fiscal\n");
            else if (tipoInvolucrado == 4)
                printf("Rol dentro de la causa: Juez\n");
            else
                printf("Rol dentro de la causa: Desconocido\n");
        }
    }

    if (contador == 0) {
        if (tipoInvolucrado == 1)
            printf("No hay victimas en esta causa.\n");
        else if (tipoInvolucrado == 2)
            printf("No hay imputados en esta causa.\n");
        else if (tipoInvolucrado == 3)
            printf("No hay fiscales en esta causa.\n");
        else if (tipoInvolucrado == 4)
            printf("No hay jueces en esta causa.\n");
        else
            printf("No hay involucrados de ese tipo en esta causa.\n");
    }
}
