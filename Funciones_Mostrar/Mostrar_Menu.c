void menuMostrar(struct ministerio *ministerio) {
    int opcion;
    opcion = -1;
    int segundaOpcion; 
    segundaOpcion = -1;
    char rut[32];
    char ruc[32];
    int tipo;
    struct causa *causaActual;

    while (opcion != 0) {
        // Imprime el menu principal de mostrar
        printf("\n=========== MENU MOSTRAR ===========\n");
        printf("1. Personas\n");
        printf("2. Denuncias de personas\n");
        printf("3. Causas\n");
        printf("4. Involucrados de una causa\n");
        printf("5. Datos de carpeta investigativa\n");
        printf("0. Volver.\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: // Mostrar personas
                printf("\n1. Mostrar TODAS las personas\n");
                printf("2. Mostrar persona por RUT\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &segundaOpcion);
                switch (segundaOpcion) {
                    case 1:
                        mostrarTodosLosUsuarios(ministerio->personas);
                        break;
                    case 2:
                        printf("Ingrese RUT: ");
                        scanf("%s", rut);
                        mostrarUsuarioPorRut(ministerio->personas, rut);
                        break;
                    default:
                        printf("Opcion invalida.\n");
                        break;
                }
                break;

            case 2: // Mostrar denuncias de personas
                printf("\n1. Mostrar TODAS las denuncias de todas las personas\n");
                printf("2. Mostrar denuncias de una persona por RUT\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &segundaOpcion);
                switch (segundaOpcion) {
                    case 1:
                        if (ministerio == NULL || ministerio->personas == NULL) {
                            printf("No hay personas registradas en el sistema.\n");
                            break;
                        }
                        mostrarTodasLasDenunciasDePersonas(ministerio->personas);
                        break;
                    case 2:
                        if (ministerio == NULL || ministerio->personas == NULL) {
                            printf("No hay personas registradas en el sistema.\n");
                            break;
                        }
                        printf("Ingrese RUT: ");
                        scanf("%s", rut);
                        mostrarDenunciaPorRut(ministerio->personas, rut);
                        break;
                    default:
                        printf("Opcion invalida.\n");
                        break;
                }
                break;

            case 3: // Mostrar causas
                printf("\n1. Mostrar TODAS las causas\n");
                printf("2. Mostrar una causa por RUC\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &segundaOpcion);
                switch (segundaOpcion) {
                    case 1:
                        if (ministerio == NULL || ministerio->causas == NULL) {
                            printf("No hay causas registradas en el sistema.\n");
                            return;
                        }
                        mostrarTodasLasCausas(ministerio->causas);
                        break;
                    case 2:
                        printf("Ingrese RUC de la causa: ");
                        scanf("%s", ruc);
                        mostrarTodoDatoDeCausaPorRuc(ministerio->causas, ruc);
                        break;
                    default:
                        printf("Opcion invalida.\n");
                        break;
                }
                break;

            case 4: // Mostrar involucrados de una causa
                printf("\n1. Mostrar TODOS los involucrados de una causa\n");
                printf("2. Mostrar involucrados de un TIPO en una causa\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &segundaOpcion);
                printf("Ingrese RUC de la causa: ");
                scanf("%s", ruc);
                causaActual = buscarCausaPorRuc(ministerio->causas, ruc);
                if (causaActual == NULL) {
                    printf("No se encontro la causa seleccionada.\n");
                    break;
                }
                switch (segundaOpcion) {
                    case 1:
                        mostrarTodosInvolucradosCausa(causaActual);
                        break;
                    case 2:
                        printf("Ingrese tipo de involucrado (1=Victima, 2=Imputado, 3=Fiscal, 4=Juez): ");
                        scanf("%d", &tipo);
                        mostrarInvolucradosCausaPorTipo(causaActual, tipo);
                        break;
                    default:
                        printf("Opcion invalida.\n");
                        break;
                }
                break;

            case 5: // Mostrar datos de carpeta investigativa
                printf("\n1. Mostrar TODOS los datos de carpeta de una causa\n");
                printf("2. Mostrar datos de carpeta por tipo en una causa\n");
                printf("Seleccione una opcion: ");
                scanf("%d", &segundaOpcion);
                printf("Ingrese RUC de la causa: ");
                scanf("%s", ruc);
                causaActual = buscarCausaPorRuc(ministerio->causas, ruc);
                if (causaActual == NULL) {
                    printf("No se encontro la causa seleccionada.\n");
                    break;
                }
                switch (segundaOpcion) {
                    case 1:
                        mostrarTodosDatosCarpetaCausa(causaActual);
                        break;
                    case 2:
                        printf("Ingrese tipo de dato (1=Declaracion, 2=Prueba, 3=Diligencia, 4=Denuncia): ");
                        scanf("%d", &tipo);
                        mostrarDatosCarpetaCausaPorTipo(causaActual, tipo);
                        break;
                    default:
                        printf("Opcion invalida.\n");
                        break;
                }
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
