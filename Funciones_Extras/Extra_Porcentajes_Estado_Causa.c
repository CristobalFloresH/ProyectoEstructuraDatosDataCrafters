void mostrarPorcentajesEstadoCausa(struct ministerio *ministerio){
    float totalCausas, totalArchivada, totalInvestigacion, totalCerrado, totalJuicio;
    float promedioArchivada, promedioInvestigacion, promedioCerrado, promedioJuicio;
    struct nodoCausas *actual;

    if(ministerio == NULL || ministerio->causas == NULL){
        printf("No se encontraron causas en el sistema.\n");
        return;
    }

    totalCausas = totalArchivada = totalInvestigacion = totalCerrado = totalJuicio = 0;

    actual = ministerio->causas;

    do {
        totalCausas++;
        switch(actual->datosCausa->estadoCausa) {
            case 1: totalArchivada++; break;
            case 2: totalInvestigacion++; break;
            case 3: totalCerrado++; break;
            case 4: totalJuicio++; break;
            default: break;
        }
        actual = actual->siguiente;
    } while(actual != ministerio->causas);

    if (totalCausas == 0) {
        printf("No se encontraron causas en el sistema.\n");
        return;
    }

    promedioArchivada = (totalArchivada / totalCausas) * 100;
    promedioInvestigacion = (totalInvestigacion / totalCausas) * 100;
    promedioCerrado = (totalCerrado / totalCausas) * 100;
    promedioJuicio = (totalJuicio / totalCausas) * 100;

    printf("--- Porcentaje estado causa ---\n");
    printf("El %.2f%% de las causas están en estado 'archivada'\n", promedioArchivada);
    printf("El %.2f%% de las causas están en estado 'investigación en progreso'\n", promedioInvestigacion);
    printf("El %.2f%% de las causas están en estado 'cerrada'\n", promedioCerrado);
    printf("El %.2f%% de las causas están en estado 'en juicio'\n", promedioJuicio);
}
