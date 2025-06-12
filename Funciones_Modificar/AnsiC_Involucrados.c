void cambiarTipoInvolucrado(struct ministerio *ministerio) {
    if (ministerio == NULL) {
        printf("Ministerio no válido.\n");
        return;
    }

    char ruc[100];
    char rut[100];
    int nuevoTipo;

    printf("Ingrese el RUC de la causa: ");
    fgets(ruc, sizeof(ruc), stdin); // fgets
    removerSaltoLinea(ruc);

    struct causa *c = buscarCausaPorRuc(ministerio->causas, ruc);
    if (c == NULL || c->involucrados == NULL) {
        printf("No se encontró la causa o no tiene involucrados.\n");
        return;
    }

    printf("Ingrese el RUT del involucrado: ");
    fgets(rut, sizeof(rut), stdin);
    removerSaltoLinea(rut);

    do {
        printf("Ingrese nuevo tipo de involucrado (1=Víctima, 2=Imputado, 3=Testigo, 4=Otro): ");
        scanf("%d", &nuevoTipo);
        getchar(); // Limpia buffer para evitar problemas con fgets si se usa después
        if (nuevoTipo < 1 || nuevoTipo > 4) {
            printf("Tipo inválido. Intente nuevamente.\n");
        }
    } while (nuevoTipo < 1 || nuevoTipo > 4);

    int encontrado = 0, i;
    for (i = 0; i < c->tamInvolucrados; i++) {
        struct involucrados *inv = c->involucrados[i];

        if (inv != NULL && inv->persona != NULL && strcmp(inv->persona->rut, rut) == 0) {
            encontrado = 1;

            if (inv->tipoInvolucrado == 2 && nuevoTipo != 2 && inv->datosImputados != NULL) {
                free(inv->datosImputados);
                inv->datosImputados = NULL;
            }

            inv->tipoInvolucrado = nuevoTipo;

            if (nuevoTipo == 2 && inv->datosImputados == NULL) {
                inv->datosImputados = malloc(sizeof(struct datosImputados));
                if (inv->datosImputados == NULL) {
                    printf("Error al asignar memoria para datosImputados.\n");
                    return;
                }

                inv->datosImputados->declaracion = NULL;
                inv->datosImputados->medidasCautelar = 7;
                inv->datosImputados->fechaInicioMedida = NULL;
                inv->datosImputados->fechaFinMedida = NULL;
                inv->datosImputados->estadoProcesal = 1;
            }

            printf("Tipo de involucrado cambiado exitosamente para RUT: %s\n", rut);
            break;
        }
    }

    if (!encontrado) {
        printf("Involucrado con RUT %s no encontrado en la causa.\n", rut);
    }
}
