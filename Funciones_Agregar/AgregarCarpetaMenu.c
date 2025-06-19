void agregarCarpeta(struct ministerio *ministerio){

    char palabra[300];
    int tipoDato;
    struct datosCarpeta *nuevaCarpeta;
    struct persona *declarante;
    struct persona *buscado;
    struct denuncia *denunciaAgregar;
    struct nodoCausas *actual;
    nuevaCarpeta = (struct datosCarpeta *)malloc(sizeof(struct datosCarpeta));

    nuevaCarpeta->descripcion = NULL;
    nuevaCarpeta->fecha = NULL;
    nuevaCarpeta->datosDenuncia = NULL;
    nuevaCarpeta->datosDiligencias = NULL;
    nuevaCarpeta->datosPersona = NULL;

    if(nuevaCarpeta == NULL){
        printf("Error al asignar memoria");
        return;
    }
    /*Se le asigna memoria a la nueva caprtea, si esta falla termina el programa*/

    printf("Ingrese fecha de la carpeta\n");
    scanf(" %[^\n]", palabra);

    nuevaCarpeta->fecha = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaCarpeta->fecha, palabra);

    printf("Ingrese el tipo de dato, ya sea \n 1 = Declaraciones \n 2 = Pruebas Generales  \n 3 = Diligencias \n 4 = Denuncia\n");
    printf("Ingrese tipo de dato:\n");
    scanf("%d", &tipoDato);
    (void)getchar();
    nuevaCarpeta->tipoDeDato = tipoDato;

    switch (tipoDato) {
        case 1:{
            printf("Ingrese RUT de persona que declara.\n");
            scanf(" %[^\n]", palabra);
            
            declarante = buscarPersonaPorRut(ministerio->personas, palabra);
            nuevaCarpeta->datosPersona = declarante;

            printf("Ingrese declaracion.\n");
            scanf(" %[^\n]", palabra);

            nuevaCarpeta->descripcion = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaCarpeta->descripcion, palabra);
            printf("Declaracion agregada correctamente.\n");
            break;
            }

        case 2:
            printf("Ingrese prueba.\n");
            scanf(" %[^\n]", palabra);
            nuevaCarpeta->descripcion = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaCarpeta->descripcion, palabra);
            printf("Prueba agregada correctamente.\n");
            break;

        case 3:
            nuevaCarpeta->datosDiligencias = malloc(sizeof(struct datosDiligencias));
            if (nuevaCarpeta->datosDiligencias == NULL) {
                printf("Error al asignar memoria para diligencia.\n");
                break;
            }

            printf("Ingrese prioridad digligencia. (1 = muy baja, 2 = baja, 3 = media, 4 = alta, 5 = muy alta)\n");
            scanf(" %d", &tipoDato);
            (void)getchar();
            nuevaCarpeta->datosDiligencias->prioridad = tipoDato;
            printf("Ingrese fecha inicio.(YYY-MM-DD)\n");
            scanf(" %[^\n]", palabra);

            nuevaCarpeta->datosDiligencias->fechaInicio = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaCarpeta->datosDiligencias->fechaInicio, palabra);
            printf("Ingrese fecha fin.(YYY-MM-DD)\n");
            scanf(" %[^\n]", palabra);

            nuevaCarpeta->datosDiligencias->fechaFin = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaCarpeta->datosDiligencias->fechaFin, palabra);
            printf("Ingrese descripcion de la diligencia.\n");
            scanf(" %[^\n]", palabra);

            nuevaCarpeta->datosDiligencias->descripcion = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaCarpeta->datosDiligencias->descripcion, palabra);
            printf("Ingrese estado diligencia.\n");
            scanf(" %[^\n]", palabra);

            nuevaCarpeta->datosDiligencias->estado = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaCarpeta->datosDiligencias->estado, palabra);
            printf("Ingrese tipo de diligencia.\n");
            scanf(" %[^\n]", palabra);

            nuevaCarpeta->datosDiligencias->tipoDiligencia = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaCarpeta->datosDiligencias->tipoDiligencia, palabra);
            printf("Diligencia agregada correctamente.\n");
            break;

            case 4:
            printf("Ingrese RUT del denunciado.\n");
            scanf(" %[^\n]", palabra);

            buscado = buscarPersonaPorRut(ministerio->personas, palabra);
            if (buscado == NULL) {
                printf("Persona no encontrada.\n");
                break;
            }
            printf("Ingrese RUC de la denuncia.\n");
            scanf(" %[^\n]", palabra);

            denunciaAgregar = buscarDenunciaPorRuc(buscado->denuncias, palabra);
            if (denunciaAgregar == NULL) {
                printf("Denuncia no encontrada.\n");
                break;
            }
            nuevaCarpeta->datosDenuncia = denunciaAgregar;
            printf("Denuncia agregada correctamente.\n");
            break;
        default:
                break;
    }
    printf("Ingrese RUC de la causa a la que desea asociar esta carpeta:\n");
    scanf(" %[^\n]", palabra);

    if (ministerio == NULL || ministerio->causas == NULL) {
        printf("no existe informacion sobre causas en el sistema.\n");
        break;
    }

    actual = buscarNodoCausa((ministerio->causas), palabra);
    agregarCarpetaInvestigativa(&actual->datosCausa->datosCarpetas, nuevaCarpeta);
}
