







void menuAgregar(struct ministerio *ministerio){
    int opcion;

    while(1){
        printf("\n=========== MENU AGREGAR ===========\n");
        printf("Opcion 1: Agregar persona\n");
        printf("Opcion 2: Agregar denuncia\n");
        printf("Opcion 3: Agregar carpeta investigativa\n");
        printf("Opcion 4: Agregar causa\n");
        printf("Opcion 5: Agregar involucrados\n");
        printf("Opcion 0: Volver.\n");
        printf("Ingrese una opcion:");
        scanf("%d", &opcion);
        /*El fiscal tendra que elegir la opcion a agregar, ya sea una persona, denuncia, carpeta investigativa*/

        if(opcion == 0){
            //menuPrincipal(struct ministerio *ministerio);
            break;
        }
        else if (opcion == 1) {
        /*Opcion 1 agregar persona*/
            struct pesona *nuevaPersona;
            char palabra[100];
            int rol;
            char contrasenaIngresada[100];
            
            nuevaPersona = (struct persona *)malloc(sizeof(struct persona));
            /*Se crea el struct persona y se le asigna memoria de inmediato, si el asignar memoria falla finaliza el programa*/

            if(nuevaPersona == NULL){
                printf("Error al asignar memora");
                return;
            }

            printf("Ingrese su rut: \n");
            scanf(" %[^\n]", palabra);
            getchar();
            nuevaPersona->rut = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaPersona->rut, palabra);

            printf("Ingrese su nombre \n");
            scanf(" %[^\n]", palabra);
            getchar();
            nuevaPersona->nombre = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaPersona->nombre, palabra);

            printf("Ingrese su apellido \n");
            scanf(" %[^\n]", palabra);
            getchar();
            nuevaPersona->apellido = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaPersona->apellido, palabra);

            printf("Ingrese su rol (1= usuario comun, 2= fiscal o 3= juez): \n");
            scanf("%d", &rol);
            getchar();

            if (rol == 2 || rol == 3) {
                printf("Ingrese la contraseña del sistema: \n");
                scanf(" %s", &contrasenaIngresada);
                getchar();

                if (strcmp(contrasenaIngresada, CONTRASENAFISCALJUEZ) != 0) {
                    printf("Contraseña incorrecta, se ingresara como Usuario Comun\n");
                    nuevaPersona->rol = 1;
                    nuevaPersona->contrasena = NULL;
                } else {
                    nuevaPersona->rol = rol;

                    nuevaPersona->contrasena = (char *)malloc(strlen(contrasenaIngresada) + 1);
                    strcpy(nuevaPersona->contrasena, contrasenaIngresada);
                }
            } else {
                /* Para roles distintos a 2 y 3 */
                nuevaPersona->rol = rol;
                nuevaPersona->contrasena = NULL;
            }

            nuevaPersona->denuncias = NULL;

            agregarPersonas(&(ministerio), nuevaPersona);
            break;
            /*Funcion agregarPersonas recorre la lista de personas que se encuentra en ministerio para asi agregar a la nueva persona al final de la lista*/
        }

        else if(opcion == 2){
        /*Opcion 2 agregar denuncia */

            char rutDenunciante[20];
            char rutDenunciado[20];
            char palabra[100];
            struct persona *nuevoDenunciante;
            struct persona *nuevoDenunciado;
            struct denuncia *nuevaDenuncia;
            
            printf("Ingrese RUT del denunciante\n");
            scanf(" %[^\n]", rutDenunciante);
            getchar();

            printf("Ingrese RUT del denunciado\n");
            scanf(" %[^\n]", rutDenunciado);
            getchar();

            nuevoDenunciante = buscarPersonaPorRut(ministerio->personas, rutDenunciante);
            nuevoDenunciado = buscarPersonaPorRut(ministerio->personas, rutDenunciado);
            /*Se pregunta y lee los ruts de denunciante y denunciado para asi copiar esta informacion en 2 strcut personas */

            if(nuevoDenunciante == NULL || nuevoDenunciado == NULL){
                printf("Denunciante y denunciado no encontrados, intente con un RUT valido\n");
                return;
            }

            nuevaDenuncia = (struct denuncia *)malloc(sizeof(struct denuncia));

            if(nuevaDenuncia == NULL){
                printf("Error al asignar memoria");
                return;
            }
            /*Se corrobora que exita denunciante y denunciado para luego asignar memoria a la nueva denuncia (tambien se corrobora que se asigne correctamente la memoria)*/

            nuevaDenuncia->denunciante = nuevoDenunciante;
            nuevaDenuncia->denunciado = nuevoDenunciado;

            printf("Ingrese la fecha actual: \n");
            scanf(" %[^\n]", palabra);
            nuevaDenuncia->fecha = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaDenuncia->fecha, palabra);

            printf("Ingrese descripcion de la denuncia: \n");
            scanf(" %[^\n]", palabra);
            nuevaDenuncia->descripcion = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaDenuncia->descripcion, palabra);

            printf("Ingrese RUC de la denuncia: \n");
            scanf(" %[^\n]", palabra);
            nuevaDenuncia->ruc = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaDenuncia->ruc, palabra);

            printf("Ingrese el tipo de denuncia: \n");
            scanf(" %[^\n]", palabra);
            nuevaDenuncia->tipoDeDenuncia = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaDenuncia->tipoDeDenuncia, palabra);
            /*Se le asigna la informacion a la denuncia como la fecha, quien es el denunciante y el denunciado entre otros*/

            agregarDenunciaAPersona(rutDenunciante, ministerio->personas, nuevaDenuncia);
            agregarDenunciaAPersona(rutDenunciado, ministerio->personas, nuevaDenuncia);
            printf("Denuncia agregada correctamente. \n");
            break;
            /* recorrer ministerio->personas y validar que el rut sea el del denunciante o denunciado (en cada caso) si es el rut, agregar a la lista de denuncias  */
            /*buscar el rut y recorrer la lista de denuncias que tiene, agregar */
        }

        else if(opcion == 3){
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
            getchar();
            nuevaCarpeta->fecha = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaCarpeta->fecha, palabra);

            printf("Ingrese el tipo de dato, ya sea \n 1 = Declaraciones \n 2 = Pruebas Generales  \n 3 = Diligencias \n 4 = Denuncia\n");
            printf("Ingrese tipo de dato:\n");
            scanf("%d", &tipoDato);
            getchar();
            nuevaCarpeta->tipoDeDato = tipoDato;

            switch (tipoDato) {
                case 1:{
                    printf("Ingrese RUT de persona que declara.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();

                    struct persona *declarante = buscarPersonaPorRut(ministerio->personas, palabra);
                    nuevaCarpeta->datosPersona = declarante;

                    printf("Ingrese declaracion.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();

                    nuevaCarpeta->descripcion = (char *)malloc(strlen(palabra) + 1);
                    strcpy(nuevaCarpeta->descripcion, palabra);
                    printf("Declaracion agregada correctamente.\n");
                    break;
            }

                case 2:
                    printf("Ingrese prueba.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
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
                    getchar();
                    nuevaCarpeta->datosDiligencias->prioridad = tipoDato;
                    printf("Ingrese fecha inicio.(YYY-MM-DD)\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                    nuevaCarpeta->datosDiligencias->fechaInicio = (char *)malloc(strlen(palabra) + 1);
                    strcpy(nuevaCarpeta->datosDiligencias->fechaInicio, palabra);
                    printf("Ingrese fecha fin.(YYY-MM-DD)\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                    nuevaCarpeta->datosDiligencias->fechaFin = (char *)malloc(strlen(palabra) + 1);
                    strcpy(nuevaCarpeta->datosDiligencias->fechaFin, palabra);
                    printf("Ingrese descripcion de la diligencia.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                    nuevaCarpeta->datosDiligencias->descripcion = (char *)malloc(strlen(palabra) + 1);
                    strcpy(nuevaCarpeta->datosDiligencias->descripcion, palabra);
                    printf("Ingrese estado diligencia.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                    nuevaCarpeta->datosDiligencias->estado = (char *)malloc(strlen(palabra) + 1);
                    strcpy(nuevaCarpeta->datosDiligencias->estado, palabra);
                    printf("Ingrese tipo de diligencia.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                    nuevaCarpeta->datosDiligencias->tipoDiligencia = (char *)malloc(strlen(palabra) + 1);
                    strcpy(nuevaCarpeta->datosDiligencias->tipoDiligencia, palabra);
                    printf("Diligencia agregada correctamente.\n");
                    break;

                case 4:
                    printf("Ingrese RUT del denunciado.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                    struct persona *buscado = buscarPersonaPorRut(ministerio->personas, palabra);
                    if (buscado == NULL) {
                        printf("Persona no encontrada.\n");
                        break;
                    }
                    printf("Ingrese RUC de la denuncia.\n");
                    scanf(" %[^\n]", palabra);
                    getchar();
                    struct denuncia * denunciaAgregar = buscarDenunciaPorRuc(buscado->denuncias, palabra);
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
            scanf(" %s", palabra);
            getchar();

            if (ministerio == NULL || ministerio->causas == NULL) {
                printf("no existe informacion sobre causas en el sistema.\n");
                break;
            }

            struct nodoCausas *actual = buscarNodoCausa((ministerio->causas), palabra);

            agregarCarpetaInvestigativa(&actual->datosCausa->datosCarpetas, nuevaCarpeta);

            break;
        }
        else if (opcion == 4) {
            char ruc[30];
            char rut[30];
            int numero =0;
            struct persona *personaBuscada;
            struct denuncia *denuncia;
            printf("Ingrese RUT del denunciado para crear la causa:\n");
            scanf("%s", rut);
            getchar(); // limpiar buffer
            printf("Ingrese RUC de la denuncia para crear la causa:\n");
            scanf("%s", ruc);
            getchar(); // limpiar buffer
            printf("Ingrese el estado de la causa (1 = Archivada 2 = Investigacion en progreso 3 = Cerrada 4 = En juicio): \n");
            scanf("%d", &numero);
            getchar();
            personaBuscada = buscarPersonaPorRut(ministerio->personas, rut);

            if (personaBuscada == NULL || personaBuscada->denuncias == NULL) {
                printf("Persona o sus denuncias fueron  no encontradas.\n");
                return;
            }

            denuncia = buscarDenunciaPorRuc(personaBuscada->denuncias, ruc);
            if (denuncia == NULL) {
                printf("No se encontro una denuncia con ese ruc que pertenezca al usuario entregado.\n");
            }

            else {
                crearYagregarCausaNueva(ministerio, denuncia, numero);
            }
            break;
        }

        else if(opcion == 5){

            char palabra[100];
            int involucradosNuevos = 1;
            int i;
            int tipo;
            struct causa *causaDestinada;
            struct involucrados *nuevoInvolucrado;
            struct persona *personaEncontrada;
            struct datosImputados *datosImp;

            printf("Ingrese el RUC de la causa a la que desea agregar el o los involucrados\n");
            scanf("%s", palabra);
            getchar();

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
                break;
            }
        }
        else{
            printf("Opcion invalida, intente nuevamente.\n");
        }
    }
}
