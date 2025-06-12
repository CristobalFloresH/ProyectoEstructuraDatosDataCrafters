void menuExtra(struct ministerio *ministerio) {
    int opcion = -1;
    char rutBuscado[100];
    while(opcion != 0) {
        // Imprime el menu principal de opciones
        printf("\n=========== MENU EXTRA ===========\n");
        printf("1. Mostrar ruc de causas en un estado\n");
        printf("2. Mostrar ruc de todas las causas donde este una persona\n");
        printf("3. Mostrar porcentaje de una urgencia de diligencias\n");
        printf("4. Mostrar porcentaje de causas en un estado\n");
        printf("0. Volver.\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpia el salto de linea despues de scanf

        switch(opcion) {
            case 1:
                // mostrar el ruc de las causas en un estado
                    if (ministerio->causas == NULL) {
                        printf("No hay causas en el sistema.\n");
                        break;
                    }
                    mostrarCausasEstado(ministerio);
                    break;

            case 2:
                // mostrar ruc de todas las causas donde este una persona
                    printf("Ingrese el rut de la persona a buscar: \n");
                    scanf("%s", rutBuscado);
                    getchar();
                    mostrarRucDePersonaBuscada(ministerio, rutBuscado);
                    break;

            case 3:
                // porcentaje de diligencias con una urgencia en una causa
                    mostrarPorcentajeDiligencias(ministerio);
                    break;

            case 4:
                // mostrar porcentaje de causas de un estado
                    mostrarPorcentajesEstadoCausa(ministerio);
                    break;
            case 0:
                //Volver. al menu anterior
                    break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    }
}
