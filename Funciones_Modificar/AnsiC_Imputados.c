void modificarImputado(struct ministerio *ministerio, char *rucCausa, char *rutImputado) {
    struct causa *c = NULL;
    struct involucrados *imp = NULL;
    struct datosImputados *datos = NULL;
    int opcion = -1;
    char palabras[300];
    char *nuevaCadena = NULL;
    int nueva_medida = 0;
    int nuevo_estado = 0;

    if (ministerio == NULL || rucCausa == NULL || rutImputado == NULL) {
        return;
    }

    c = buscarCausaPorRuc(ministerio->causas, rucCausa);
    if (c == NULL) {
        printf("Causa con RUC %s no encontrada.\n", rucCausa);
        return;
    }

    imp = buscarImputadoEnCausa(c, rutImputado);
    if (imp == NULL || imp->tipoInvolucrado != 2) {
        printf("Imputado con RUT %s no encontrado en la causa.\n", rutImputado);
        return;
    }

    if (imp->datosImputados == NULL) {
        imp->datosImputados = (struct datosImputados *) malloc(sizeof(struct datosImputados));
        if (imp->datosImputados != NULL) {
            memset(imp->datosImputados, 0, sizeof(struct datosImputados));
        } else {
            printf("Error al crear datos del imputado.\n");
            return;
        }
    }

    datos = imp->datosImputados;

    while (opcion != 0) {
        printf("\n--- Modificar Imputado ---\n");
        printf("1. Declaracion\n");
        printf("2. Medida Cautelar\n");
        printf("3. Fecha Inicio Medida\n");
        printf("4. Fecha Fin Medida\n");
        printf("5. Estado Procesal\n");
        printf("0. Volver.\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese nueva declaracion: ");
                if (fgets(palabras, sizeof(palabras), stdin)) {
                    palabras[strcspn(palabras, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabras);
                    if (nuevaCadena != NULL) {
                        if (datos->declaracion != NULL) {
                            free(datos->declaracion);
                        }
                        datos->declaracion = nuevaCadena;
                    }
                }
                break;

            case 2:
                do {
                    printf("Ingrese nueva medida cautelar (1 = Prision Preventiva, 2 = Arraigo Nacional, 3 = Firma Periodica, "
                           "4 = Orden de Alejamiento, 5 = Arresto Domiciliario, 6 = Libertad bajo Fianza, 7 = Ninguna): ");
                    scanf("%d", &nueva_medida);
                    getchar();
                    if (nueva_medida < 1 || nueva_medida > 7) {
                        printf("Medida cautelar no valida. Intente nuevamente.\n");
                    }
                } while (nueva_medida < 1 || nueva_medida > 7);

                datos->medidasCautelar = nueva_medida;
                printf("Medida cautelar actualizada correctamente.\n");
                break;

            case 3:
                printf("Ingrese nueva fecha de inicio (YYYY-MM-DD): ");
                if (fgets(palabras, sizeof(palabras), stdin)) {
                    palabras[strcspn(palabras, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabras);
                    if (nuevaCadena != NULL) {
                        if (datos->fechaInicioMedida != NULL) {
                            free(datos->fechaInicioMedida);
                        }
                        datos->fechaInicioMedida = nuevaCadena;
                    }
                }
                break;

            case 4:
                printf("Ingrese nueva fecha de fin (YYYY-MM-DD): ");
                if (fgets(palabras, sizeof(palabras), stdin)) {
                    palabras[strcspn(palabras, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabras);
                    if (nuevaCadena != NULL) {
                        if (datos->fechaFinMedida != NULL) {
                            free(datos->fechaFinMedida);
                        }
                        datos->fechaFinMedida = nuevaCadena;
                    }
                }
                break;

            case 5:
                do {
                    printf("Ingrese nuevo estado procesal (1: Cautelar, 2: Formalizado, 3: Sobreseido): ");
                    sca

