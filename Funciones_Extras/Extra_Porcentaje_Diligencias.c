void mostrarPorcentajeDiligencias(struct ministerio *ministerio){
    struct nodoCausas *causa;
    struct nodoDatosCarpetas *actual;
    int totalPrioridad, muyBaja, baja, media, alta, muyAlta;
    float promedioMuyBajaPrioridad, promedioBajaPrioridad, promedioMediaPrioridad, promedioAltaPrioridad, promedioMuyAltaPrioridad;

    if(ministerio == NULL || ministerio->causas == NULL){
        printf("No se encontraron causas en el sistema\n");
        return;
    }

    causa = ministerio->causas;
    actual = causa->datosCarpetas;

    totalPrioridad = 0;
    muyBaja = baja = media = alta = muyAlta = 0;

    while (actual != NULL){
        //Solo se trabajara con diligencia.
        if (actual->datosCarpeta != NULL && actual->datosCarpeta->tipoDeDato == 3){
            int prioridad = actual->datosCarpeta->datosDiligencias->prioridad;
            totalPrioridad++;
            switch(prioridad){
                case 1: muyBaja++; break;
                case 2: baja++; break;
                case 3: media++; break;
                case 4: alta++; break;
                case 5: muyAlta++; break;
            }
        }
        actual = actual->siguiente;
    }

    if (totalPrioridad == 0) {
        printf("No se encontraron diligencias para calcular porcentaje.\n");
        return;
    }

    promedioMuyBajaPrioridad = ((float)muyBaja / totalPrioridad) * 100;
    promedioBajaPrioridad = ((float)baja / totalPrioridad) * 100;
    promedioMediaPrioridad = ((float)media / totalPrioridad) * 100;
    promedioAltaPrioridad = ((float)alta / totalPrioridad) * 100;
    promedioMuyAltaPrioridad = ((float)muyAlta / totalPrioridad) * 100;

    printf("\n========================================\n");
    printf("PORCENTAJE DE PRIORIDAD DE DILIGENCIA EN CAUSA RUC: %s\n", causa->datosCausa->ruc);
    printf("========================================\n");
    printf("El %.2f%% de las diligencias son de muy baja prioridad\n", promedioMuyBajaPrioridad);
    printf("El %.2f%% de las diligencias son de baja prioridad\n", promedioBajaPrioridad);
    printf("El %.2f%% de las diligencias son de media prioridad\n", promedioMediaPrioridad);
    printf("El %.2f%% de las diligencias son de alta prioridad\n", promedioAltaPrioridad);
    printf("El %.2f%% de las diligencias son de muy alta prioridad\n", promedioMuyAltaPrioridad);
}





