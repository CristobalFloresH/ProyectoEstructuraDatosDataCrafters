void mostrarDatosCarpetaCausaPorTipo(struct causa *causa, int tipoDeDato)
{
    struct nodoDatosCarpetas *actual;
    int contador;
    
    if (causa == NULL)
    {
        printf("No se encontro la causa seleccionada.\n");
        return;
    }
    if (causa->datosCarpetas == NULL)
    {
        printf("Esta causa no contiene datos investigativos registrados.\n");
        return;
    }

    actual = causa->datosCarpetas;
    contador = 0;

    while (actual != NULL)
    {
        if (actual->datosCarpeta != NULL && actual->datosCarpeta->tipoDeDato == tipoDeDato)
        {
            contador++;
            printf("\n========================================\n");
            printf("DATO DE CARPETA #%d\n", contador);
            printf("========================================\n");

            if (actual->datosCarpeta->datosPersona != NULL)
            {
                printf("Persona asociada:\n");
                printf("  Nombre       : %s\n", actual->datosCarpeta->datosPersona->nombre);
                printf("  Apellido     : %s\n", actual->datosCarpeta->datosPersona->apellido);
                printf("  Rut          : %s\n", actual->datosCarpeta->datosPersona->rut);
            }

            printf("Fecha          : %s\n", actual->datosCarpeta->fecha);
            printf("Descripcion    : %s\n", actual->datosCarpeta->descripcion);

            if (tipoDeDato == 1)
                printf("Tipo de dato   : Declaracion\n");
            else if (tipoDeDato == 2)
                printf("Tipo de dato   : Prueba general (Fotos, videos, etc)\n");
            else if (tipoDeDato == 3)
            {
                printf("Tipo de dato   : Diligencia\n");
                mostrarDatosDiligencia(actual->datosCarpeta->datosDiligencias);
            }
            else if (tipoDeDato == 4) {
                printf("Tipo de dato   : Denuncia\n");
                mostrarDatosDenunciaAdicionalEnCausa(actual->datosCarpeta->datosDenuncia);
            }
            else
                printf("Tipo de dato   : Desconocido\n");
        }
        actual = actual->siguiente;
    }

    if (contador == 0)
    {
        if (tipoDeDato == 1)
            printf("No existen declaraciones en la carpeta investigativa de esta causa.\n");
        else if (tipoDeDato == 2)
            printf("No existen pruebas generales en la carpeta investigativa de esta causa.\n");
        else if (tipoDeDato == 3)
            printf("No existen diligencias en la carpeta investigativa de esta causa.\n");
        else if (tipoDeDato == 4)
            printf("No existen denuncias adicionales en la carpeta investigativa de esta causa.\n");
        else
            printf("No existen datos del tipo solicitado en la carpeta investigativa de esta causa.\n");
    }
}

void mostrarTodosDatosCarpetaCausa(struct causa *causa)
{
    struct nodoDatosCarpetas *actual;
    struct datosCarpeta *carpeta;
    int contador;

    if (causa == NULL) {
        printf("No se encontro la causa seleccionada.\n");
        return;
    }
    if (causa->datosCarpetas == NULL) {
        printf("Esta causa no contiene datos investigativos registrados.\n");
        return;
    }

    actual = causa->datosCarpetas;
    contador = 0;

    while (actual != NULL)
    {
        carpeta = actual->datosCarpeta;
        if (carpeta != NULL)
        {
            contador++;
            printf("\n========================================\n");
            printf("DATO DE CARPETA #%d\n", contador);
            printf("========================================\n");

            if (carpeta->datosPersona != NULL)
            {
                printf("Persona asociada:\n");
                printf("  Nombre       : %s\n", carpeta->datosPersona->nombre);
                printf("  Apellido     : %s\n", carpeta->datosPersona->apellido);
                printf("  Rut          : %s\n", carpeta->datosPersona->rut);
            }

            printf("Fecha          : %s\n", carpeta->fecha);
            printf("Descripcion    : %s\n", carpeta->descripcion);

            if (carpeta->tipoDeDato == 1)
                printf("Tipo de dato   : Declaracion\n");
            else if (carpeta->tipoDeDato == 2)
                printf("Tipo de dato   : Prueba general (Fotos, videos, etc)\n");
            else if (carpeta->tipoDeDato == 3)
            {
                printf("Tipo de dato   : Diligencia\n");
                mostrarDatosDiligencia(carpeta->datosDiligencias);
            }
            else if (carpeta->tipoDeDato == 4) {
                printf("Tipo de dato   : Denuncia\n");
                mostrarDatosDenunciaAdicionalEnCausa(carpeta->datosDenuncia);
            }
            else
                printf("Tipo de dato   : Desconocido\n");

        }
        actual = actual->siguiente;
    }

    if (contador == 0)
        printf("No existen datos en la carpeta investigativa de esta causa.\n");
}
