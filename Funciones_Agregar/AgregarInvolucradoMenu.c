void agregarInvolucradoMenu(struct ministerio ministerio){
    char palabra[100];
    int involucradosNuevos = 1;
    int i;
    int tipo;
    struct causa *causaDestinada;
    struct involucrados *nuevoInvolucrado;
    struct persona *personaEncontrada;
    struct datosImputados *datosImp;

    printf("Ingrese el RUC de la causa a la que desea agregar el o los involucrados\n");
    scanf(" %[^\n]", palabra);

    causaDestinada = buscarCausaPorRuc(ministerio->causas, palabra);
    if(causaDestinada == NULL){
        printf("No se encontro una causa con ese RUC\n");
        return;
    }

    for(i = 0; i < involucradosNuevos; i++){
        nuevoInvolucrado = (struct involucrados *)malloc(sizeof(struct involucrados));
        if(nuevoInvolucrado == NULL){
            printf("Error al asignar memoria");
            return;
        }

        printf("Ingrese el RUT del %d° involucrado:\n", involucradosNuevos + 1);
        scanf(" %[^\n]", palabra);

        personaEncontrada = buscarPersonaPorRut(ministerio->personas, palabra);
        if(personaEncontrada == NULL){
            printf("Persona no encontrada, saltando...\n");
            free(nuevoInvolucrado);
            continue;
        }

        nuevoInvolucrado->persona = personaEncontrada;

        printf("Seleccione el tipo de involucrado:\n");
        printf("1 = victima, 2 = imputado, 3 = fiscal, 4 = juez\n");
        scanf("%i",&tipo);
        nuevoInvolucrado->tipoInvolucrado = tipo;

        if(tipo == 2){
            datosImp = (struct datosImputados *)malloc(sizeof(struct datosImputados));
            if(datosImp == NULL){
                printf("Error al asignar memoria");
                return;
            }
            printf("Ingrese la declaracion del imputado:\n");
            scanf(" %[^\n]", palabra);

            datosImp->declaracion = (char *)malloc(strlen(palabra) + 1);
            strcpy(datosImp->declaracion, palabra);

            printf("Ingrese la medida cautelar (1 = Prision Preventiva, 2 = Arraigo nacional, 3 = Firma periodica, 4 = Orden de alejamiento, 5 = Arresto domiciliario, 6 = Libertad bajo fianza, 7 = Ninguna):\n");
            scanf("%d", &datosImp->medidasCautelar);

            printf("Ingrese la fecha de inicio de la medida (formato: DD/MM/AAAA):\n");
            scanf(" %[^\n]", palabra);

            datosImp->fechaInicioMedida = (char *)malloc(strlen(palabra) + 1);
            strcpy(datosImp->fechaInicioMedida, palabra);

            printf("Ingrese la fecha de fin de la medida (formato: DD/MM/AAAA):\n");
            scanf(" %[^\n]", palabra);

            datosImp->fechaFinMedida = (char *)malloc(strlen(palabra) + 1);
            strcpy(datosImp->fechaFinMedida, palabra);

            printf("Ingrese el estado procesal (1 = Medida cautelar, 2 = Formalizado, 3 = Sobreseido):\n");
            scanf("%d", &datosImp->estadoProcesal);

            nuevoInvolucrado->datosImputados = datosImp;
        } else{
            nuevoInvolucrado->datosImputados = NULL;
        }

        agregarInvolucrado(causaDestinada, nuevoInvolucrado);
        printf("Involucrado agregado correctamente\n");    
    
}
