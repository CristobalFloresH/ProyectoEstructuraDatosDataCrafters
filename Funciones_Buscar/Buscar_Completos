struct nodoDatosCarpetas *buscarDatosCarpetaPorTipo(struct causa *causa, int tipoDeDato){
    
    struct nodoDatosCarpetas *listaResultado = NULL;
    struct nodoDatosCarpetas *nodoActualCarpeta;
    struct nodoDatosCarpetas *nuevoNodoResultado;
    struct nodoDatosCarpetas *nodoFinal;

    
    if (causa == NULL || causa->datosCarpetas == NULL)
    {
        return NULL;
    }

    nodoActualCarpeta = causa->datosCarpetas;

    while (nodoActualCarpeta != NULL)
    {
        if (nodoActualCarpeta->datosCarpeta != NULL &&
            nodoActualCarpeta->datosCarpeta->tipoDeDato == tipoDeDato)
        {
            nuevoNodoResultado = (struct nodoDatosCarpetas *)malloc(sizeof(struct nodoDatosCarpetas));
            if (nuevoNodoResultado == NULL)
            {
                return NULL;
            }
            // Apunta al mismo datosCarpeta original (NO se hace copia profunda)
            nuevoNodoResultado->datosCarpeta = nodoActualCarpeta->datosCarpeta;
            nuevoNodoResultado->siguiente = NULL;
            nuevoNodoResultado->anterior = NULL;

            // Si la lista de resultados está vacía, este es el primer nodo
            if (listaResultado == NULL)
            {
                listaResultado = nuevoNodoResultado;
            }
            else
            {
                // Si no, recorre la lista resultado hasta el último nodo
                nodoFinal = listaResultado;
                while (nodoFinal->siguiente != NULL)
                {
                    nodoFinal = nodoFinal->siguiente;
                }
                // Enlaza el nuevo nodo al final
                nodoFinal->siguiente = nuevoNodoResultado;
                nuevoNodoResultado->anterior = nodoFinal;
            }
        }
        nodoActualCarpeta = nodoActualCarpeta->siguiente;
    }
    return listaResultado;
}

struct denuncia *buscarDenunciaPorRuc(struct nodoDenuncias *listaDenuncias, char *rucBuscado){
    struct nodoDenuncias *actual;

    //se recorre la lista mientras queden nodos por revisar
    //y pregunta si el ruc actual es igual al buscado

    actual = listaDenuncias;
    
    while(actual != NULL){

        if(strcmp(actual->datosDenuncia->ruc, rucBuscado) == 0){
            return actual->datosDenuncia;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

struct involucrados* buscarInvolucradoPorRut(struct involucrados **involucrados, int tam, char *rut) {
    int i;
    
    if (involucrados == NULL) return NULL;
    
    for (i = 0; i < tam; i++) {
        if (involucrados[i] != NULL && involucrados[i]->persona != NULL) {
            if (strcmp(involucrados[i]->persona->rut, rut) == 0) {
                return involucrados[i];
            }
        }
    }
    return NULL;
}

void menuBuscar(struct ministerio *ministerio) {
    int opcion = -1;
    char rut[32];
    char ruc[32];
    int tipoDato;
    struct causa *causaActual;
    struct nodoDatosCarpetas *listaResultados;
    struct denuncia *denunciaEncontrada;
    struct persona *personaEncontrada;
    struct involucrados *involucradoEncontrado;

    while (opcion != 0) {
        printf("\n=========== MENU BUSCAR ===========\n");
        printf("1. Buscar persona por RUT\n");
        printf("2. Buscar denuncia por RUC (en denuncias de una persona)\n");
        printf("3. Buscar causa por RUC\n");
        printf("4. Buscar involucrado por RUT (en una causa)\n");
        printf("5. Buscar datos de carpeta por tipo (en una causa)\n");
        printf("0. Volver.\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: // Persona
                printf("Ingrese RUT de la persona: ");
                scanf("%s", rut);
                personaEncontrada = buscarPersonaPorRut(ministerio->personas, rut);
                if (personaEncontrada != NULL)
                    printf("Persona encontrada: %s %s\n", personaEncontrada->nombre, personaEncontrada->apellido);
                else
                    printf("No se encontro persona con ese RUT.\n");
                break;

            case 2: // Denuncia por RUC en denuncias de persona
                printf("Ingrese RUT de la persona: ");
                scanf("%s", rut);
                personaEncontrada = buscarPersonaPorRut(ministerio->personas, rut);
                if (personaEncontrada == NULL || personaEncontrada->denuncias == NULL) {
                    printf("No se encontro la persona o no tiene denuncias.\n");
                    break;
                }
                printf("Ingrese RUC de la denuncia: ");
                scanf("%s", ruc);
                denunciaEncontrada = buscarDenunciaPorRuc(personaEncontrada->denuncias, ruc);
                if (denunciaEncontrada != NULL)
                    printf("Denuncia encontrada: %s\n", denunciaEncontrada->descripcion);
                else
                    printf("No se encontro la denuncia con ese RUC para esa persona.\n");
                break;

            case 3: // Causa por RUC
                printf("Ingrese RUC de la causa: ");
                scanf("%s", ruc);
                causaActual = buscarCausaPorRuc(ministerio->causas, ruc);
                if (causaActual != NULL)
                    printf("Causa encontrada: %s\n", causaActual->ruc);
                else
                    printf("No se encontro la causa con ese RUC.\n");
                break;

            case 4: // Involucrado por RUT (en una causa)
                printf("Ingrese RUC de la causa: ");
                scanf("%s", ruc);
                causaActual = buscarCausaPorRuc(ministerio->causas, ruc);
                if (causaActual == NULL || causaActual->involucrados == NULL) {
                    printf("No se encontro la causa o no tiene involucrados.\n");
                    break;
                }
                printf("Ingrese RUT del involucrado: ");
                scanf("%s", rut);
                involucradoEncontrado = buscarInvolucradoPorRut(causaActual->involucrados, causaActual->tamInvolucrados, rut);
                if (involucradoEncontrado != NULL)
                    printf("Involucrado encontrado: %s %s\n", involucradoEncontrado->persona->nombre, involucradoEncontrado->persona->apellido);
                else
                    printf("No se encontro involucrado con ese RUT en esa causa.\n");
                break;

            case 5: // Buscar datos carpeta por tipo en una causa
                printf("Ingrese RUC de la causa: ");
                scanf("%s", ruc);
                causaActual = buscarCausaPorRuc(ministerio->causas, ruc);
                if (causaActual == NULL || causaActual->datosCarpetas == NULL) {
                    printf("No se encontro la causa o no tiene datos de carpeta.\n");
                    break;
                }
                printf("Ingrese tipo de dato (1=Declaracion, 2=Prueba, 3=Diligencia, 4=Denuncia): ");
                scanf("%d", &tipoDato);
                listaResultados = buscarDatosCarpetaPorTipo(causaActual, tipoDato);
                if (listaResultados == NULL)
                    printf("No se encontraron datos de ese tipo en la causa.\n");
                else
                    printf("Se encontraron datos de ese tipo en la causa.\n");
                break;

            case 0:
                //volvemos al menu anterior
                break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }
    }
}

struct nodoCausas *buscarNodoCausa(struct nodoCausas *causas, char *rucBuscado) {
    struct nodoCausas *actual;
    
    if (causas == NULL || rucBuscado == NULL) return NULL;

    actual = causas;

    do {
        if (strcmp(actual->datosCausa->ruc, rucBuscado) == 0) {
            return actual;
        }
        actual = actual->siguiente;
    } while (actual != causas);

    return NULL;
}

struct persona *buscarPersonaPorRut(struct nodoPersonasABB *personas, char *rutBuscado){
    /** esto es para que retorne NULL si no encuentra la persona, ya que al ser recursivo
    Esto sera NULL cuando personas apunte a NULL y eso significa que llego a la hoja del arbol
    por lo cual no hay donde mas buscar**/

    if (personas == NULL || rutBuscado == NULL)
    {
        return NULL;
    }

    //compara datos del arbol con el buscado
    int comparacionActual = strcmp(personas->datosPersona->rut, rutBuscado);

    /** comparacionActual == 0 se encontro
    comparacionActual > 0 vamos a la izquierda (menores), ya que el numero en el que estamos es mayor al buscado
    comparacionActual < 0 (o else) vamos a la derecha (mayores), ya que el numero en el que estamos es menor al buscado
    **/

    if (comparacionActual == 0)
    {
        return personas->datosPersona;
    }
    else if (comparacionActual > 0)
    {
        return buscarPersonaPorRut(personas->izquierda, rutBuscado);
    }
    else
    {
        return buscarPersonaPorRut(personas->derecha, rutBuscado);
    }
}

struct causa *buscarCausaPorRuc(struct nodoCausas *causas, char *rucBuscado) {
    struct nodoCausas *actual;
    //si la lista de causas o el ruc buscado es null, retorna null ya que no hay nada que buscar
    if (causas == NULL || rucBuscado == NULL) return NULL;

    actual = causas;

    //se recorre lista circular hasta encontrar el ruc igual, si no se encuentra retorna null
    do {
        if (strcmp(actual->datosCausa->ruc, rucBuscado) == 0)
        {
            return actual->datosCausa;
        }

        actual = actual->siguiente;
    } while (actual != causas);

    return NULL;
}

struct datosDiligencias* buscarDiligencia(struct ministerio *ministerio, char *ruc, char *fechaInicio, char *tipoDiligencia) {
    struct causa *c;
    struct datosCarpeta *carpeta;
    struct datosDiligencias *d;
    
    if (ministerio == NULL || ruc == NULL || fechaInicio == NULL || tipoDiligencia == NULL) {
        printf("Parámetros inválidos.\n");
        return NULL;
    }

    // Buscar causa por RUC
    c = buscarCausaPorRuc(ministerio->causas, ruc);
    if (c == NULL) {
        printf("No se encontró la causa con RUC: %s\n", ruc);
        return NULL;
    }

    // Acceder a la carpeta única de la causa
    if (c->datosCarpetas == NULL || c->datosCarpetas->datosCarpeta == NULL) {
        printf("La causa no tiene carpeta válida.\n");
        return NULL;
    }

    carpeta = c->datosCarpetas->datosCarpeta;

    if (carpeta->tipoDeDato == 3 && carpeta->datosDiligencias != NULL) {
        d = carpeta->datosDiligencias;
        if (strcmp(d->fechaInicio, fechaInicio) == 0 && strcmp(d->tipoDiligencia, tipoDiligencia) == 0) {
            return d;
        }
    }

    printf("No se encontró una diligencia que coincida con fecha de inicio '%s' y tipo '%s'.\n", fechaInicio, tipoDiligencia);
    return NULL;
}

struct involucrados* buscarImputadoEnCausa(struct causa *c, char *rutImputado) {
    int i;
    struct involucrados *inv;
    
    if (c == NULL || rutImputado == NULL) {
        printf("Error: causa o RUT inválido.\n");
        return NULL;
    }
    for (i = 0; i < c->tamInvolucrados; i++) {
        inv = c->involucrados[i];
        if (inv != NULL &&
            inv->tipoInvolucrado == 2 && // Tipo imputado
            inv->persona != NULL &&
            strcmp(inv->persona->rut, rutImputado) == 0) {
            return inv;
            }
    }
    return NULL;
}

