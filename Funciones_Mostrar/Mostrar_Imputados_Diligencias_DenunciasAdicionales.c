void mostrarDatosImputados(struct datosImputados *datosImputados) {
    if (datosImputados == NULL)
    {
        printf("Este imputado no tiene datos especificos.\n");
        return;
    }
    /**1 = Prision Preventiva, 2 = Arraigo nacional, 3 = firma periodica,
    4 = orden de alejamiento, 5 = arresto domicilario, 6 = libertad bajo fianza, 7 = ninguna**/
    printf("\n--- Datos Imputado Asociados ---\n");
    printf("Declaracion: %s\n", datosImputados->declaracion);

    if (datosImputados->estadoProcesal == 1) {
        printf("Estado procesal: Medida cautelar\n");
        if (datosImputados->medidasCautelar == 1) {
            printf("Medida cautelar: Prision Preventiva\n");
        }
        else if (datosImputados->medidasCautelar == 2) {
            printf("Medida cautelar: Arraigo nacional\n");
        }
        else if (datosImputados->medidasCautelar == 3) {
            printf("Medida cautelar: Firma periodica\n");
        }
        else if (datosImputados->medidasCautelar == 4) {
            printf("Medida cautelar: Orden de alejamiento\n");
        }
        else if (datosImputados->medidasCautelar == 5) {
            printf("Medida cautelar: Arresto domiciliario\n");
        }
        else if (datosImputados->medidasCautelar == 6) {
            printf("Medida cautelar: Libertad bajo fianza\n");
        }
        else if (datosImputados->medidasCautelar == 7) {
            printf("Medida cautelar: Ninguna, Imputado aun no posee medida cautelar.\n");
            return;
        }

        printf("Fecha inicio medida: %s\n", datosImputados->fechaInicioMedida);
        printf("Fecha fin medida: %s\n", datosImputados->fechaFinMedida);
    }
    else if (datosImputados->estadoProcesal == 2) {
        printf("Estado procesal: Formalizado\n");
    }
    else if (datosImputados->estadoProcesal == 3) {
        printf("Estado procesal: Sobreseido\n");
    }
}

void mostrarDatosDiligencia(struct datosDiligencias *diligencia)
{
    printf("\n--- Diligencia Asociada ---\n");
    printf("Prioridad      : %d\n", diligencia->prioridad);
    printf("Fecha inicio   : %s\n", diligencia->fechaInicio);
    printf("Fecha fin      : %s\n", diligencia->fechaFin);
    printf("Estado         : %s\n", diligencia->estado);
    printf("Tipo           : %s\n", diligencia->tipoDiligencia);
    printf("Descripcion    : %s\n", diligencia->descripcion);
}

void mostrarDatosDenunciaAdicionalEnCausa(struct denuncia *denuncia)
{
    printf("\n--- Denuncia Asociada ---\n");
    printf("RUC            : %s\n", denuncia->ruc);
    printf("Fecha          : %s\n", denuncia->fecha);
    printf("Descripcion    : %s\n", denuncia->descripcion);
    printf("Delito         : %s\n", denuncia->tipoDeDenuncia);
    if (denuncia->denunciante != NULL)
        printf("Denunciante    : %s %s (RUT: %s)\n", denuncia->denunciante->nombre,
            denuncia->denunciante->apellido,
            denuncia->denunciante->rut);
    if (denuncia->denunciado != NULL)
        printf("Denunciado     : %s %s (RUT: %s)\n", denuncia->denunciado->nombre,
            denuncia->denunciado->apellido,
            denuncia->denunciado->rut);
}


void mostrarDatosCarpetaCausaPorTipo(struct causa *causa, int tipoDeDato)
{
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

    struct nodoDatosCarpetas *actual = causa->datosCarpetas;
    int contador = 0;

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
