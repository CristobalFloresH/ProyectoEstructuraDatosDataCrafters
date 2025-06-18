void ingresarAlSistema(struct ministerio *ministerio) {
    char palabra[100];
    int rol;
    struct persona *nuevaPersona;
    nuevaPersona = (struct persona *)malloc(sizeof(struct persona));

    // Validar si se pudo asignar memoria
    if (nuevaPersona == NULL) {
        printf("Error al asignar memoria para nueva persona.\n");
        return;
    }

    printf("\n=========== Bienvenido al sistema ===========\n");
    printf("Ingrese su RUT.\n\n");
    printf("Ingrese opcion:");
    scanf("%s", palabra);
    getchar();

    nuevaPersona->rut = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaPersona->rut, palabra);

    printf("Ingrese su nombre.\n\n");
    printf("Ingrese opcion:");
    scanf("%s", palabra);
    getchar();

    nuevaPersona->nombre = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaPersona->nombre, palabra);

    printf("Ingrese su apellido.\n\n");
    printf("Ingrese opcion:");
    scanf("%s", palabra);
    getchar();

    nuevaPersona->apellido = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaPersona->apellido, palabra);

    printf("Ingrese su rol (1 = Usuario, 2 = Fiscal, 3 = Juez).\n\n");
    printf("Ingrese opcion:");
    scanf("%d", &rol);
    getchar();

    if (rol == 1) {
        nuevaPersona->rol = rol;
        nuevaPersona->contrasena = NULL;
    } else if (rol == 2 || rol == 3) {
        printf("Ingrese contrasena del sistema.\n\n");
        printf("Ingrese opcion:");
        scanf("%s", palabra);
        getchar();

        if (strcmp(palabra, CONTRASENAFISCALJUEZ) == 0) {
            nuevaPersona->rol = rol;
            nuevaPersona->contrasena = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaPersona->contrasena, palabra);
        } else {
            printf("Contrasena incorrecta, ingresando como usuario.\n\n");
            nuevaPersona->rol = 1;
            nuevaPersona->contrasena = NULL;
        }
    } else {
        printf("Opcion no valida. Intente de nuevo.\n");
        return;
    }

    nuevaPersona->denuncias = NULL;
    agregarPersonas(&(ministerio), nuevaPersona);
    printf("Ingresando al menu...\n\n");
}

void mostrarCausasEstado(struct ministerio *ministerio) {
    int opcion = -1;
    int estadoFiltrado = 0;
    int contador = 0;
    struct nodoCausas *actual = NULL;

    if (ministerio == NULL || ministerio->causas == NULL) {
        printf("No hay causas registradas.\n");
        return;
    }

    while (opcion != 0) {
        printf("\n========== MENU ESTADO DE CAUSAS ==========\n");
        printf("1. Mostrar todas las causas con su estado\n");
        printf("2. Mostrar causas de un estado especifico\n");
        printf("0. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer

        switch (opcion) {
            case 1:
                actual = ministerio->causas;
                printf("\n========================================\n");
                printf("REPORTE DE TODAS LAS CAUSAS CON ESTADO ACTUAL\n");
                printf("========================================\n");
                do {
                    printf("Causa #%d: RUC: %s | Estado de causa: %d\n", contador, actual->datosCausa->ruc, actual->datosCausa->estadoCausa);
                    contador++;
                    actual = actual->siguiente;
                } while (actual != ministerio->causas);
                contador = 0;
                break;

            case 2:
                printf("Ingrese el estado de causa a mostrar (1=Archivada, 2=En progreso, 3=Cerrada, 4=En juicio): ");
                scanf("%d", &estadoFiltrado);
                getchar();

                actual = ministerio->causas;
                printf("\n========================================\n");
                printf("REPORTE DE CAUSAS CON ESTADO %d\n", estadoFiltrado);
                printf("========================================\n");
                do {
                    if (actual->datosCausa->estadoCausa == estadoFiltrado) {
                        printf("Causa N°%d: RUC: %s | Estado de causa: %d\n", contador, actual->datosCausa->ruc, actual->datosCausa->estadoCausa);
                        contador++;
                    }
                    actual = actual->siguiente;
                } while (actual != ministerio->causas);
                contador = 0;
                break;

            case 0:
                printf("Volviendo al menú anterior.\n");
                break;

            default:
                printf("Opcion invalida. Intente nuevamente.\n");
                break;
        }
    }
}

void mostrarRucDePersonaBuscada(struct ministerio *ministerio, char *rutBuscado)
{
    int minimoUnEncontrado = 0;
    int i = 0;
    struct nodoCausas *actual = NULL;
    struct nodoDatosCarpetas *actualCarpeta = NULL;
    int encontrado = 0;

    if (ministerio == NULL || ministerio->causas == NULL)
    {
        printf("No se encontraron causas en el sistema\n");
        return;
    }

    minimoUnEncontrado = 0;
    actual = ministerio->causas;

    do
    {
        encontrado = 0;

        // Buscar en involucrados
        for (i = 0; i < actual->datosCausa->tamInvolucrados; i++)
        {
            if (actual->datosCausa->involucrados[i] != NULL &&
                actual->datosCausa->involucrados[i]->persona != NULL &&
                actual->datosCausa->involucrados[i]->persona->rut != NULL &&
                strcmp(actual->datosCausa->involucrados[i]->persona->rut, rutBuscado) == 0)
            {
                encontrado = 1;
            }
        }

        // Buscar en denuncia (denunciante y denunciado)
        if (actual->datosCausa->denuncia != NULL)
        {
            if (actual->datosCausa->denuncia->denunciante != NULL &&
                actual->datosCausa->denuncia->denunciante->rut != NULL &&
                strcmp(actual->datosCausa->denuncia->denunciante->rut, rutBuscado) == 0)
            {
                encontrado = 1;
            }
            if (actual->datosCausa->denuncia->denunciado != NULL &&
                actual->datosCausa->denuncia->denunciado->rut != NULL &&
                strcmp(actual->datosCausa->denuncia->denunciado->rut, rutBuscado) == 0)
            {
                encontrado = 1;
            }
        }

        // Buscar en datosPersona de todas las carpetas investigativas de la causa
        actualCarpeta = actual->datosCausa->datosCarpetas;
        while (actualCarpeta != NULL)
        {
            if (actualCarpeta->datosCarpeta != NULL &&
                actualCarpeta->datosCarpeta->datosPersona != NULL &&
                actualCarpeta->datosCarpeta->datosPersona->rut != NULL &&
                strcmp(actualCarpeta->datosCarpeta->datosPersona->rut, rutBuscado) == 0)
            {
                encontrado = 1;
            }
            actualCarpeta = actualCarpeta->siguiente;
        }

        if (encontrado == 1)
        {
            printf("La persona con RUT %s esta en la causa con RUC: %s\n", rutBuscado, actual->datosCausa->ruc);
            minimoUnEncontrado = 1;
        }

        actual = actual->siguiente;
    } while (actual != ministerio->causas);

    if (minimoUnEncontrado == 0)
    {
        printf("La persona con RUT %s no fue encontrada en el sistema.\n", rutBuscado);
    }
}

void mostrarPorcentajeDiligencias(struct ministerio *ministerio) {
    struct nodoCausas *causa = NULL;
    struct nodoDatosCarpetas *actual = NULL;
    int totalPrioridad = 0;
    int muyBaja = 0;
    int baja = 0;
    int media = 0;
    int alta = 0;
    int muyAlta = 0;
    float promedioMuyBajaPrioridad = 0.0;
    float promedioBajaPrioridad = 0.0;
    float promedioMediaPrioridad = 0.0;
    float promedioAltaPrioridad = 0.0;
    float promedioMuyAltaPrioridad = 0.0;
    int prioridad = 0;

    if (ministerio == NULL || ministerio->causas == NULL) {
        printf("No se encontraron causas en el sistema\n");
        return;
    }

    causa = ministerio->causas;
    actual = causa->datosCarpetas;

    while (actual != NULL) {
        // Solo se trabajará con diligencia.
        if (actual->datosCarpeta != NULL && actual->datosCarpeta->tipoDeDato == 3 &&
            actual->datosCarpeta->datosDiligencias != NULL) {

            prioridad = actual->datosCarpeta->datosDiligencias->prioridad;
            totalPrioridad++;

            switch (prioridad) {
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

void mostrarPorcentajesEstadoCausa(struct ministerio *ministerio) {
    float totalCausas = 0.0;
    float totalArchivada = 0.0;
    float totalInvestigacion = 0.0;
    float totalCerrado = 0.0;
    float totalJuicio = 0.0;
    float promedioArchivada = 0.0;
    float promedioInvestigacion = 0.0;
    float promedioCerrado = 0.0;
    float promedioJuicio = 0.0;
    struct nodoCausas *actual = NULL;

    if (ministerio == NULL || ministerio->causas == NULL) {
        printf("No se encontraron causas en el sistema.\n");
        return;
    }

    actual = ministerio->causas;

    do {
        totalCausas++;
        switch (actual->datosCausa->estadoCausa) {
            case 1: totalArchivada++; break;
            case 2: totalInvestigacion++; break;
            case 3: totalCerrado++; break;
            case 4: totalJuicio++; break;
            default: break;
        }
        actual = actual->siguiente;
    } while (actual != ministerio->causas);

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

void menuExtra(struct ministerio *ministerio) {
    int opcion;
    char rutBuscado[100];

    opcion = -1;
    rutBuscado[0] = '\0';

    while (opcion != 0) {
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

        switch (opcion) {
            case 1:
                if (ministerio->causas == NULL) {
                    printf("No hay causas en el sistema.\n");
                    break;
                }
                mostrarCausasEstado(ministerio);
                break;

            case 2:
                printf("Ingrese el rut de la persona a buscar: \n");
                scanf("%s", rutBuscado);
                getchar();
                mostrarRucDePersonaBuscada(ministerio, rutBuscado);
                break;

            case 3:
                mostrarPorcentajeDiligencias(ministerio);
                break;

            case 4:
                mostrarPorcentajesEstadoCausa(ministerio);
                break;

            case 0:
                // Volver al menu anterior
                break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    }
}

