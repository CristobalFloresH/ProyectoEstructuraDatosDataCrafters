int agregarPersonas(struct ministerio *ministerio, struct persona *nuevaPersona) {
    struct nodoPersonasABB *nuevoNodo;
    struct nodoPersonasABB *actual;
    struct nodoPersonasABB *padre;
    int cmp;

    if (ministerio == NULL || nuevaPersona == NULL) {
        return -1;
    }

    // Si el árbol está vacío, se inicializa
    if (ministerio->personas == NULL) {
        nuevoNodo = (struct nodoPersonasABB *)malloc(sizeof(struct nodoPersonasABB));
        if (nuevoNodo == NULL) {
            return -2;
        }
        nuevoNodo->datosPersona = nuevaPersona;
        nuevoNodo->izquierda = NULL;
        nuevoNodo->derecha = NULL;
        ministerio->personas = nuevoNodo;
        return 1;
    }

    // Reutilizamos la lógica anterior de inserción en ABB
    actual = ministerio->personas;
    padre = NULL;
    cmp = 0;

    while (actual != NULL) {
        cmp = strcmp(nuevaPersona->rut, actual->datosPersona->rut);
        if (cmp == 0) {
            return 0;
        }
        padre = actual;
        if (cmp < 0) {
            if (actual->izquierda == NULL) break;
            actual = actual->izquierda;
        } else {
            if (actual->derecha == NULL) break;
            actual = actual->derecha;
        }
    }

    nuevoNodo = (struct nodoPersonasABB *)malloc(sizeof(struct nodoPersonasABB));
    if (nuevoNodo == NULL) {
        return -2;
    }
    nuevoNodo->datosPersona = nuevaPersona;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;

    if (cmp < 0) {
        padre->izquierda = nuevoNodo;
    } else {
        padre->derecha = nuevoNodo;
    }
    return 1;
}

void agregarDenunciaAPersona(char *rut, struct nodoPersonasABB *nodoPersonasABB, struct denuncia *nuevaDenuncia){
    struct persona *personaEncontrada;
    struct nodoDenuncias *nuevoNodo;
    struct nodoDenuncias *actual;

    // se busca a la persona usando su rut
    personaEncontrada = buscarPersonaPorRut(nodoPersonasABB, rut);

    // si no se encuentra la persona, se informa al usuario
    if(personaEncontrada == NULL){
        return -3;
    }

    // se asigna memoria y se verifica que haya sido exitoso
    nuevoNodo = (struct nodoDenuncias*)malloc(sizeof(struct nodoDenuncias));
    if(nuevoNodo == NULL){
        printf("Error al asignar memoria");
        return -2;
    }

    // se asignan valores a nuevo nodo
    nuevoNodo->datosDenuncia = nuevaDenuncia;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    actual = personaEncontrada->denuncias;
    if(actual == NULL){
        // denuncias vacía, se agrega de primero
        personaEncontrada->denuncias = nuevoNodo;
    } else {
        // se recorre hasta el final la lista de denuncias
        while(actual->siguiente != NULL){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
        nuevoNodo->anterior = actual;
    }
}

void agregarCausa(struct nodoCausas **listaCausas, struct causa *nuevaCausa){
    struct nodoCausas *nuevoNodo;
    struct nodoCausas *ultimo;

    // Se crea el nuevo Nodo al que se le asignará la nueva causa
    nuevoNodo = (struct nodoCausas *)malloc(sizeof(struct nodoCausas));
    if(nuevoNodo == NULL){
        printf("Error al asignar memoria");
        return;
    }

    // Se le asigna al nuevo nodo la nueva causa
    nuevoNodo->datosCausa = nuevaCausa;

    if(*listaCausas == NULL){
        // Lista vacía, se agrega al inicio
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
        *listaCausas = nuevoNodo;
    } else {
        // Si la lista no está vacía se reenlazan los nodos
        ultimo = (*listaCausas)->anterior;

        nuevoNodo->siguiente = *listaCausas;
        nuevoNodo->anterior = ultimo;

        ultimo->siguiente = nuevoNodo;
        (*listaCausas)->anterior = nuevoNodo;
    }
}

void agregarCarpetaInvestigativa(struct nodoDatosCarpetas **carpetas, struct datosCarpeta *nuevaCarpeta) {
    struct nodoDatosCarpetas *nuevoNodo;
    struct nodoDatosCarpetas *actual;

    // Revisamos que la nueva carpeta exista
    if(nuevaCarpeta == NULL){
        printf("Nueva carpeta no existe\n");
        return;
    }

    // Definimos nuevo nodo para asignarle nuevaCarpeta y corroboramos que se asigne memoria
    nuevoNodo = (struct nodoDatosCarpetas *)malloc(sizeof(struct nodoDatosCarpetas));
    if(nuevoNodo == NULL){
        printf("Error al asignar memoria para el nuevo nodo\n");
        return;
    }

    // Se asignan los campos al nuevo nodo
    nuevoNodo->datosCarpeta = nuevaCarpeta;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    // Si está vacía, asignar al inicio
    if(*carpetas == NULL){
        *carpetas = nuevoNodo;
    } else {
        // Recorre hasta el final de la lista
        actual = *carpetas;
        while(actual->siguiente != NULL) {
            actual = actual->siguiente;
        }

        // Asigna los punteros al nuevo nodo
        actual->siguiente = nuevoNodo;
        nuevoNodo->anterior = actual;
    }
    printf("Carpeta agregada exitosamente.\n");
}

void crearYagregarCausaNueva(struct ministerio *ministerio, struct denuncia *denunciaAsociada, int estadoCausa) {
    struct causa *nuevaCausa;

    if (ministerio == NULL || denunciaAsociada == NULL) {
        printf("Ministerio o denuncia inválida.\n");
        return;
    }

    nuevaCausa = (struct causa *)malloc(sizeof(struct causa));
    if (nuevaCausa == NULL) {
        printf("Error al asignar memoria para la causa.\n");
        return;
    }
    nuevaCausa->ruc = duplicarCadena(denunciaAsociada->ruc);
    if (nuevaCausa->ruc == NULL) {
        printf("Error al duplicar el RUC.\n");
        return;
    }


    nuevaCausa->denuncia = denunciaAsociada;
    nuevaCausa->datosCarpetas = NULL;
    nuevaCausa->involucrados = NULL;
    nuevaCausa->tamInvolucrados = 0;
    nuevaCausa->estadoCausa = estadoCausa;
    nuevaCausa->sentencia = NULL;

    agregarCausa(&ministerio->causas, nuevaCausa);
    printf("Causa agregada correctamente\n");

}

void agregarCarpetaMenu(struct ministerio *ministerio){
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
            nuevaCarpeta->datosDiligencias = (struct datosDiligencias *)malloc(sizeof(struct datosDiligencias));
            if (nuevaCarpeta->datosDiligencias == NULL) {
                printf("Error al asignar memoria para diligencia.\n");
                break;
            }

            printf("Ingrese prioridad digligencia. (1 = muy baja, 2 = baja, 3 = media, 4 = alta, 5 = muy alta)\n");
            scanf(" %d", &tipoDato);
            (void)getchar();
            nuevaCarpeta->datosDiligencias->prioridad = tipoDato;
            printf("Ingrese fecha inicio.(YYYY-MM-DD)\n");
            scanf(" %[^\n]", palabra);

            nuevaCarpeta->datosDiligencias->fechaInicio = (char *)malloc(strlen(palabra) + 1);
            strcpy(nuevaCarpeta->datosDiligencias->fechaInicio, palabra);
            printf("Ingrese fecha fin.(YYYY-MM-DD)\n");
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
        return;
    }

    actual = buscarNodoCausa((ministerio->causas), palabra);
    agregarCarpetaInvestigativa(&actual->datosCausa->datosCarpetas, nuevaCarpeta);
}

void agregarInvolucrado(struct causa *causaDestinada, struct involucrados *nuevoInvolucrado){
    int i;
    int nuevoTam;
    struct involucrados **nuevoArreglo;

    nuevoTam = 0;  // Inicialización por seguridad en TurboC

    // Revisamos que causaDestinada y nuevoInvolucrado tengan datos
    if (causaDestinada == NULL || nuevoInvolucrado == NULL) {
        printf("Error: la causa o el involucrado están vacíos.\n");
        return;
    }

    nuevoTam = causaDestinada->tamInvolucrados + 1;

    // Asignamos memoria y validamos que esta sea correcta
    nuevoArreglo = (struct involucrados **) malloc(sizeof(struct involucrados *) * nuevoTam);
    if (nuevoArreglo == NULL) {
        printf("Error al asignar memoria.\n");
        return;
    }

    // Recorre el array hasta el último dato
    for(i = 0; i < causaDestinada->tamInvolucrados; i++){
        nuevoArreglo[i] = causaDestinada->involucrados[i];
    }

    // Se añade al final el nuevo involucrado
    nuevoArreglo[causaDestinada->tamInvolucrados] = nuevoInvolucrado;

    // Se libera memoria del array anterior
    if(causaDestinada->involucrados != NULL){
        free(causaDestinada->involucrados);
    }

    causaDestinada->involucrados = nuevoArreglo;
    causaDestinada->tamInvolucrados = nuevoTam;
}

void agregarPersonaMenu(struct ministerio *ministerio){
    struct persona *nuevaPersona;
    char palabra[100];
    int rol;
    char contrasenaIngresada[100];
    nuevaPersona = (struct persona *)malloc(sizeof(struct persona));
    /*Se crea el struct persona y se le asigna memoria de inmediato, si el asignar memoria falla finaliza el programa*/

    if(nuevaPersona == NULL){
        return -2;
    }

    printf("Ingrese su rut: \n");
    scanf(" %[^\n]", palabra);

    nuevaPersona->rut = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaPersona->rut, palabra);

    printf("Ingrese su nombre \n");
    scanf(" %[^\n]", palabra);

    nuevaPersona->nombre = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaPersona->nombre, palabra);

    printf("Ingrese su apellido \n");
    scanf(" %[^\n]", palabra);

    nuevaPersona->apellido = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaPersona->apellido, palabra);

    printf("Ingrese su rol (1= usuario comun, 2= fiscal o 3= juez): \n");
    scanf("%d", &rol);
    (void)getchar();

    if (rol == 2 || rol == 3) {
        printf("Ingrese la contraseña del sistema: \n");
        scanf(" %[^\n]", contrasenaIngresada);

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

    return agregarPersonas(ministerio, nuevaPersona);
}

void agregarDenunciaMenu(struct ministerio *ministerio){
    char rutDenunciante[20];
    char rutDenunciado[20];
    char palabra[100];
    struct persona *nuevoDenunciante;
    struct persona *nuevoDenunciado;
    struct denuncia *nuevaDenuncia;

    printf("Ingrese RUT del denunciante\n");
    scanf(" %[^\n]", rutDenunciante);

    printf("Ingrese RUT del denunciado\n");
    scanf(" %[^\n]", rutDenunciado);


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
}

void agregarCausaMenu(struct ministerio *ministerio){
    char ruc[30];
    char rut[30];
    int numero =0;
    struct persona *personaBuscada;
    struct denuncia *denuncia;
    printf("Ingrese RUT del denunciado para crear la causa:\n");
    scanf(" %[^\n]", rut);

    printf("Ingrese RUC de la denuncia para crear la causa:\n");
    scanf(" %[^\n]", ruc);

    printf("Ingrese el estado de la causa (1 = Archivada 2 = Investigacion en progreso 3 = Cerrada 4 = En juicio): \n");
    scanf("%d", &numero);
    (void)getchar();
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
}

void agregarInvolucradoMenu(struct ministerio *ministerio){
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

        printf("Ingrese el RUT del involucrado:\n");
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

            printf("Ingrese la fecha de inicio de la medida (formato: YYYY-MM-DD):\n");
            scanf(" %[^\n]", palabra);

            datosImp->fechaInicioMedida = (char *)malloc(strlen(palabra) + 1);
            strcpy(datosImp->fechaInicioMedida, palabra);

            printf("Ingrese la fecha de fin de la medida (formato: YYYY-MM-DD):\n");
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
}

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
            agregarPersonaMenu(ministerio);
            break;
        }

        else if(opcion == 2){
        /*Opcion 2 agregar denuncia */
            agregarDenunciaMenu(ministerio);
            break;
        }

        else if(opcion == 3){
        /*Opcion 3 agregar carpeta*/
            agregarCarpetaMenu(ministerio);
            break;
        }
        else if (opcion == 4) {
        /*Opcion 4 agregar causa*/
            agregarCausaMenu(ministerio);
            break;
        }
        else if(opcion == 5){
        /*Opcion 5 agregar involucrado*/
            agregarInvolucradoMenu(ministerio);
            break;
        }
        else{
            printf("Opcion invalida, intente nuevamente.\n");
        }
    }
}
