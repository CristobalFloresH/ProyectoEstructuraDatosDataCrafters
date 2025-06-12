void mostrarPorcentajesEstadoCausa(struct ministerio *ministerio){

    if(ministerio == NULL || ministerio->causas == NULL){
        printf("No se encontraron casuas en el sistema.");
        return;
    }

    float totalCausas = 0, totalArchivada = 0, totalInvestigacion = 0, totalCerrado = 0, totalJuicio = 0;

    struct nodoCausas *actual = ministerio->causas;


    do{

        if(actual->datosCausa->estadoCausa == 1){
            totalCausas++;
            totalArchivada++;
        }

        else if(actual->datosCausa->estadoCausa == 2){
            totalCausas++;
            totalInvestigacion++;
        }

        else if(actual->datosCausa->estadoCausa == 3){
            totalCausas++;
            totalCerrado++;
        }

        else if(actual->datosCausa->estadoCausa == 4){
            totalCausas++;
            totalJuicio++;
        }
        actual = actual->siguiente;

    }while(actual != ministerio->causas);

        float promedioArchivada, promedioInvestigacion, promedioCerrado, promedioJuicio;

    if (totalCausas == 0) {
        printf("No se encontraron casuas en el sistema.");
        return;
    }

    promedioArchivada = (totalArchivada / totalCausas) * 100;
    promedioInvestigacion = (totalInvestigacion / totalCausas) * 100;
    promedioCerrado = (totalCerrado / totalCausas) * 100;
    promedioJuicio = (totalJuicio / totalCausas) * 100;

    printf("--- Porcentaje estado causa ---\n");
    printf("El %.2f%% de las causas estan en estado 'archivada'\n", promedioArchivada);
    printf("El %.2f%% de las causas estan en estado 'investigacion en progreso'\n", promedioInvestigacion);
    printf("El %.2f%% de las causas estan en estado 'cerrada'\n", promedioCerrado );
    printf("El %.2f%% de las causas estan en estado 'en juicio'\n", promedioJuicio);

}
