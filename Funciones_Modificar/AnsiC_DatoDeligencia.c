void modificarDatosDiligencia(struct ministerio *ministerio) {
    if (ministerio == NULL) {
        printf("Ministerio no válido.\n");
        return;
    }

    char ruc[20], fechaInicio[50], tipoDiligencia[50];
    char buffer[300];
    char *nuevaCadena;
    int opcion = -1;

    printf("Ingrese el RUC de la causa: ");
    scanf("%s", ruc);
    getchar(); // limpiar '\n'
    printf("Ingrese la fecha de inicio de la diligencia (YYYY-MM-DD): ");
    scanf("%s", fechaInicio);
    getchar();
    printf("Ingrese el tipo de diligencia: ");
    scanf("%s", tipoDiligencia);
    getchar();

    struct datosDiligencias *diligencia = buscarDiligencia(ministerio, ruc, fechaInicio, tipoDiligencia);
    if (diligencia == NULL) {
        printf("No se encontró la diligencia con esos datos.\n");
        return;
    }

    while (opcion != 0) {
        printf("\n--- Modificar Datos de Diligencia ---\n");
        printf("1. Modificar prioridad (Actual: %d)\n", diligencia->prioridad);
        printf("2. Modificar fecha inicio (Actual: %s)\n", diligencia->fechaInicio);
        printf("3. Modificar fecha fin (Actual: %s)\n", diligencia->fechaFin);
        printf("4. Modificar descripción (Actual: %s)\n", diligencia->descripcion);
        printf("5. Modificar estado (Actual: %s)\n", diligencia->estado);
        printf("6. Modificar tipo de diligencia (Actual: %s)\n", diligencia->tipoDiligencia);
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch (opcion) {
            case 1: {
                int nueva_prioridad;
                do {
                    printf("Ingrese nueva prioridad (1 = muy baja, ..., 5 = muy alta): ");
                    scanf("%d", &nueva_prioridad);
                    getchar();
                    if (nueva_prioridad < 1 || nueva_prioridad > 5)
                        printf("Prioridad inválida. Intente nuevamente.\n");
                } while (nueva_prioridad < 1 || nueva_prioridad > 5);
                diligencia->prioridad = nueva_prioridad;
                printf("Prioridad actualizada correctamente.\n");
                break;
            }

            case 2:
                printf("Ingrese nueva fecha inicio (YYYY-MM-DD): ");
                scanf("%s", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->fechaInicio);
                    diligencia->fechaInicio = nuevaCadena;
                    printf("Fecha inicio actualizada correctamente.\n");
                }
                break;

            case 3:
                printf("Ingrese nueva fecha fin (YYYY-MM-DD): ");
                scanf("%s", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->fechaFin);
                    diligencia->fechaFin = nuevaCadena;
                    printf("Fecha fin actualizada correctamente.\n");
                }
                break;

            case 4:
                printf("Ingrese nueva descripción: ");
                scanf(" %[^\n]", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->descripcion);
                    diligencia->descripcion = nuevaCadena;
                    printf("Descripción actualizada correctamente.\n");
                }
                break;

            case 5:
                printf("Ingrese nuevo estado: ");
                scanf(" %[^\n]", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->estado);
                    diligencia->estado = nuevaCadena;
                    printf("Estado actualizado correctamente.\n");
                }
                break;

            case 6:
                printf("Ingrese nuevo tipo de diligencia: ");
                scanf(" %[^\n]", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->tipoDiligencia);
                    diligencia->tipoDiligencia = nuevaCadena;
                    printf("Tipo de diligencia actualizado correctamente.\n");
                }
                break;

            case 0:
                printf("Saliendo del menú de modificación.\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    }
}
