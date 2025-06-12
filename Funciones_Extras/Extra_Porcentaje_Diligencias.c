void mostrarPorcentajeDiligencias(struct ministerio *ministerio){
    
    if(ministerio == NULL || ministerio->causas == NULL){
        printf("No se encontraron causas en el sistema");
    }
    
    struct nodoDatosCarpetas *actual = causa->datosCarpetas;
    int totalPrioridad = 0, muyBaja = 0, baja = 0, media = 0, alta = 0; muyAlta = 0;
    
    while (actual != NULL){
        //Solo se trabajara con diligencia.
        if (actual->datosCarpeta != NULL && actual->datosCarpeta->tipoDeDato == 3){
            
            if(actual->datosCarpeta->datosDiligencias->prioridad == 1){
                totalPrioridad++;
                muyBaja++;
            }
            if(actual->datosCarpeta->datosDiligencias->prioridad == 2){
                totalPrioridad++;
                baja++;
            }
            if(actual->datosCarpeta->datosDiligencias->prioridad == 3){
                totalPrioridad++;
                media++;
            }
            if(actual->datosCarpeta->datosDiligencias->prioridad == 4){
                totalPrioridad++;
                alta++;
            }
            if(actual->datosCarpeta->datosDiligencias->prioridad == 5){
                totalPrioridad++;
                muyAlta++;
            }
        }
        actual = actual->siguiente;
    }
    
    
    float promedioMuyBajaPrioridad, promedioBajaPrioridad, promedioMediaPrioridad, promedioAltaPrioridad, promedioMuyAltaPrioridad;
    
    promedioMuyBajaPrioridad = (muyBaja / totalPrioridad) * 100;
    promedioBajaPrioridad = (baja / totalPrioridad) * 100;
    promedioMediaPrioridad = (media / totalPrioridad) * 100;
    promedioAltaPrioridad = (alta / totalPrioridad) * 100;
    promedioMuyAltaPrioridad = (muyAlta / totalPrioridad) * 100;
    
    
    printf("\n========================================\n");
    printf("PORCENTAJE DE PRIORIDAD DE DILIGENCIA EN CAUSA RUC: %s",ministerio->causas->datosCausa->ruc);
    printf("\n========================================\n");
    printf("El %f%% de las diligencias son de muy baja prioridad", promedioMuyBajaPrioridad);
    printf("El %f%% de las diligencias son de baja prioridad", promedioBajaPrioridad);
    printf("El %f%% de las diligencias son de media prioridad", promedioMediaPrioridad);
    printf("El %f%% de las diligencias son de alta prioridad", promedioAltaPrioridad);
    printf("El %f%% de las diligencias son de muy alta prioridad", promedioMuyAltaPrioridad);
}





