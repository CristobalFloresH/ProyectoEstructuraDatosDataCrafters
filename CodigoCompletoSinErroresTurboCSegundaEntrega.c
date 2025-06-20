#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *CONTRASENAFISCALJUEZ = "12064";


struct denuncia { //Datos denuncia singular.
    struct persona *denunciante; //persona que envio la denuncia
    struct persona *denunciado; //persona que recibio la denuncia
    char *fecha;
    char *descripcion;
    char *ruc;
    char *tipoDeDenuncia;
};

struct nodoDenuncias { //Lista simple Doblemente Enlazada De Denuncias
    struct denuncia *datosDenuncia;
    struct nodoDenuncias *siguiente;
    struct nodoDenuncias *anterior;
};

struct persona { //Datos persona singular
    char *nombre;
    char *apellido;
    char *rut;
    int rol;
    /** 1 = usuario comun, 2 = fiscal, 3 = juez**/

    char *contrasena;

    struct nodoDenuncias *denuncias;
};

struct nodoPersonasABB { //arbol (ABB)
    struct persona *datosPersona;
    struct nodoPersonasABB *izquierda;
    struct nodoPersonasABB *derecha;
};

struct datosImputados {
    char *declaracion;
    int medidasCautelar; /**1 = Prision Preventiva, 2 = Arraígo nacional, 3 = firma periódica,
    4 = orden de alejamiento, 5 = arresto domicilario, 6 = libertad bajo fianza, 7 = ninguna**/
    char *fechaInicioMedida;
    char *fechaFinMedida;

    int estadoProcesal; /**1 = medida cautelar, 2 = formalizado (arrestado), 3 = sobreseido**/
};

struct involucrados {
    int tipoInvolucrado; //1 = victima, 2 = imputado, 3 = fiscal, 4 = juez
    struct datosImputados *datosImputados;
    struct persona *persona;
};

struct causa { //Datos causa singular
    char *ruc; //Rol unico de causa (identificador unico)
    struct denuncia *denuncia; //LA denuncia de esta causa
    struct nodoDatosCarpetas *datosCarpetas; //datos investigativos de la carpeta
    struct involucrados **involucrados; //array de involucrados
    int tamInvolucrados; //tamaño array involucrados

    int estadoCausa; //1 = archivada, 2 = investigacion en progreso, 3 = cerrada, 4 = en juicio

    char *sentencia;
};

struct nodoCausas { //Lista Circular doblemente enlazada
    struct causa *datosCausa;
    struct nodoCausas *siguiente;
    struct nodoCausas *anterior;
};

struct nodoDatosCarpetas { //lista doblemente enlazada
    struct datosCarpeta *datosCarpeta;
    struct nodoDatosCarpetas *siguiente;
    struct nodoDatosCarpetas *anterior;
};

struct datosDiligencias {
    int prioridad; //1 = muy baja, 2 = baja, 3 = media, 4 = alta, 5 = muy alta
    char *fechaInicio;
    char *fechaFin;
    char *descripcion;
    char *estado;
    char *tipoDiligencia;
};

struct datosCarpeta { //datos investigativos (NO PERSONAS) singular de 1 tipo de dato
    char *fecha; //fecha
    char *descripcion; //descripción generica
    struct persona *datosPersona;

    int tipoDeDato; //tipo de dato
    /** 1 = declaraciones, 2 = pruebas generales (Fotos, videos, etc), 3 = diligencias, 4 = denuncia**/

    struct datosDiligencias *datosDiligencias;
    struct denuncia *datosDenuncia;
};

struct ministerio { //el mismisimo ministerio
    struct nodoPersonasABB *personas;
    struct nodoCausas *causas;
};

/**=========================================================
	            SECCION BUSCAR (TODOS)
=========================================================**/

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
  	int comparacionActual;
    /** esto es para que retorne NULL si no encuentra la persona, ya que al ser recursivo
    Esto sera NULL cuando personas apunte a NULL y eso significa que llego a la hoja del arbol
    por lo cual no hay donde mas buscar**/

    if (personas == NULL || rutBuscado == NULL)
    {
        return NULL;
    }

    //compara datos del arbol con el buscado
    comparacionActual = strcmp(personas->datosPersona->rut, rutBuscado);

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
        if (inv != NULL && inv->tipoInvolucrado == 2 && inv->persona != NULL && strcmp(inv->persona->rut, rutImputado) == 0) {
            return inv;
            }
    }
    return NULL;
}

char* duplicarCadena(char* origen) {
    char* destino;
    int longitud;
    int i;

    if (origen == NULL) {
        return NULL;
    }

    /* Calcular longitud de la cadena */
    longitud = 0;
    while (origen[longitud] != '\0') {
        longitud++;
    }

    /* Asignar memoria */
    destino = (char*)malloc((longitud + 1) * sizeof(char));
    if (destino == NULL) {
        return NULL;
    }

    /* Copiar cadena */
    for (i = 0; i <= longitud; i++) {
        destino[i] = origen[i];
    }

    return destino;
}

/* Función auxiliar para encontrar el primer salto de línea */
int encontrarSaltoLinea(char* cadena) {
    int i = 0;
    while (cadena[i] != '\0') {
        if (cadena[i] == '\n') {
            return i;
        }
        i++;
    }
    return -1; /* No se encontró salto de línea */
}

/* Función auxiliar para remover el salto de línea */
void removerSaltoLinea(char* cadena) {
    int pos = encontrarSaltoLinea(cadena);
    if (pos != -1) {
        cadena[pos] = '\0';
    }
}

struct datosCarpeta* buscarCarpetaPorTipoYFecha(struct nodoDatosCarpetas *lista, int tipo, char *fechaBuscada) { // agregar
    while (lista != NULL) {
        if (lista->datosCarpeta != NULL && lista->datosCarpeta->tipoDeDato == tipo && strcmp(lista->datosCarpeta->fecha, fechaBuscada) == 0) {
            return lista->datosCarpeta;
        }
        lista = lista->siguiente;
    }
    return NULL;
}

/**=========================================================
	            SECCION AGREGAR (diego cortez)
=========================================================**/

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

int agregarDenunciaAPersona(char *rut, struct nodoPersonasABB *nodoPersonasABB, struct denuncia *nuevaDenuncia){
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
    return 1;
}

int agregarCausa(struct nodoCausas **listaCausas, struct causa *nuevaCausa){
    struct nodoCausas *nuevoNodo;
    struct nodoCausas *ultimo;

    // Se crea el nuevo Nodo al que se le asignará la nueva causa
    nuevoNodo = (struct nodoCausas *)malloc(sizeof(struct nodoCausas));
    if(nuevoNodo == NULL){
        printf("Error al asignar memoria");
        return -2;
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
    return 1;
}

int agregarCarpetaInvestigativa(struct nodoDatosCarpetas **carpetas, struct datosCarpeta *nuevaCarpeta) {
    struct nodoDatosCarpetas *nuevoNodo;
    struct nodoDatosCarpetas *actual;

    // Revisamos que la nueva carpeta exista
    if(nuevaCarpeta == NULL){
        return -1;
    }

    // Definimos nuevo nodo para asignarle nuevaCarpeta y corroboramos que se asigne memoria
    nuevoNodo = (struct nodoDatosCarpetas *)malloc(sizeof(struct nodoDatosCarpetas));
    if(nuevoNodo == NULL){
        return -2;
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
    return 1;
}

int crearYagregarCausaNueva(struct ministerio *ministerio, struct denuncia *denunciaAsociada, int estadoCausa) {
    struct causa *nuevaCausa;

    if (ministerio == NULL || denunciaAsociada == NULL) {
        return -4;
    }

    nuevaCausa = (struct causa *)malloc(sizeof(struct causa));
    if (nuevaCausa == NULL) {
        return -2;
    }
    nuevaCausa->ruc = duplicarCadena(denunciaAsociada->ruc);
    if (nuevaCausa->ruc == NULL) {
        return -5;
    }


    nuevaCausa->denuncia = denunciaAsociada;
    nuevaCausa->datosCarpetas = NULL;
    nuevaCausa->involucrados = NULL;
    nuevaCausa->tamInvolucrados = 0;
    nuevaCausa->estadoCausa = estadoCausa;
    nuevaCausa->sentencia = NULL;

    agregarCausa(&ministerio->causas, nuevaCausa);
    return 1;

}

int agregarCarpetaMenu(struct ministerio *ministerio){
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
        return -2;
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
        return 0;
    }

    actual = buscarNodoCausa((ministerio->causas), palabra);
    agregarCarpetaInvestigativa(&actual->datosCausa->datosCarpetas, nuevaCarpeta);
    return 1;
}

int agregarInvolucrado(struct causa *causaDestinada, struct involucrados *nuevoInvolucrado){
    int i;
    int nuevoTam;
    struct involucrados **nuevoArreglo;

    nuevoTam = 0;  // Inicialización por seguridad en TurboC

    // Revisamos que causaDestinada y nuevoInvolucrado tengan datos
    if (causaDestinada == NULL || nuevoInvolucrado == NULL) {
        return 0;
    }

    nuevoTam = causaDestinada->tamInvolucrados + 1;

    // Asignamos memoria y validamos que esta sea correcta
    nuevoArreglo = (struct involucrados **) malloc(sizeof(struct involucrados *) * nuevoTam);
    if (nuevoArreglo == NULL) {
        return -2;
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
    return 1;
}

int agregarPersonaMenu(struct ministerio *ministerio){
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

int agregarDenunciaMenu(struct ministerio *ministerio){
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
        return 0;
    }

    nuevaDenuncia = (struct denuncia *)malloc(sizeof(struct denuncia));

    if(nuevaDenuncia == NULL){
        return -2;
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
    return 1;
}

int agregarCausaMenu(struct ministerio *ministerio){
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
        return -1;
    }

    denuncia = buscarDenunciaPorRuc(personaBuscada->denuncias, ruc);
    if (denuncia == NULL) {
        return -3;
    }

    else {
        crearYagregarCausaNueva(ministerio, denuncia, numero);
        return 1;
    }
}

int agregarInvolucradoMenu(struct ministerio *ministerio){
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
        return -1;
    }

    for(i = 0; i < involucradosNuevos; i++){
        nuevoInvolucrado = (struct involucrados *)malloc(sizeof(struct involucrados));
        if(nuevoInvolucrado == NULL){
            return -2;
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
                return -2;
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
    }
    return 1;
}

/**=========================================================
	            SECCION ELIMINAR (Rafael Valdes)
=========================================================**/


void reenlazarCausas(struct nodoCausas **listaCausas, struct nodoCausas *nodoEliminar) {
    if (*listaCausas == NULL || nodoEliminar == NULL) return;

    // Si solo hay un nodo en la lista
    if (nodoEliminar->siguiente == nodoEliminar && nodoEliminar->anterior == nodoEliminar) {
        *listaCausas = NULL;
        return;
    }

    // Enlazamos
    nodoEliminar->anterior->siguiente = nodoEliminar->siguiente;
    nodoEliminar->siguiente->anterior = nodoEliminar->anterior;

    // Si el nodo a eliminar es el nodo apuntado por lista (inicio), movemos el puntero
    if (*listaCausas == nodoEliminar) {
        *listaCausas = nodoEliminar->siguiente;
    }
}
void reenlazarDenuncias(struct nodoDenuncias **listaDenuncias, struct nodoDenuncias *nodoEliminar) {
    if (*listaDenuncias == NULL || nodoEliminar == NULL) return;

    if (*listaDenuncias == nodoEliminar) {
        *listaDenuncias = nodoEliminar->siguiente;
        if (*listaDenuncias != NULL) {
            (*listaDenuncias)->anterior = NULL;
        }
    } else {
        if (nodoEliminar->anterior != NULL) {
            nodoEliminar->anterior->siguiente = nodoEliminar->siguiente;
        }
        if (nodoEliminar->siguiente != NULL) {
            nodoEliminar->siguiente->anterior = nodoEliminar->anterior;
        }
    }
}
void reenlazarDatosCarpeta(struct nodoDatosCarpetas **listaCarpetas, struct nodoDatosCarpetas *nodoEliminar) {
    if (*listaCarpetas == NULL || nodoEliminar == NULL) return;

    if (*listaCarpetas == nodoEliminar) {
        *listaCarpetas = nodoEliminar->siguiente;
        if (*listaCarpetas != NULL) {
            (*listaCarpetas)->anterior = NULL;
        }
    } else {
        if (nodoEliminar->anterior != NULL) {
            nodoEliminar->anterior->siguiente = nodoEliminar->siguiente;
        }
        if (nodoEliminar->siguiente != NULL) {
            nodoEliminar->siguiente->anterior = nodoEliminar->anterior;
        }
    }
}

void liberarPersona(struct persona *persona) {
    if (persona == NULL)
        return;

    free(persona->nombre);
    free(persona->apellido);
    free(persona->rut);
    free(persona->contrasena);

    free(persona);
}
void liberarDenuncia(struct denuncia *denuncia) {
    if (denuncia == NULL)
        return;

    free(denuncia->fecha);
    free(denuncia->descripcion);
    free(denuncia->ruc);
    free(denuncia->tipoDeDenuncia);

    free(denuncia);
}
void liberarDatosImputados(struct datosImputados *datos) {
    if (datos == NULL)
        return;

    free(datos->declaracion);
    free(datos->fechaInicioMedida);
    free(datos->fechaFinMedida);

    free(datos);
}
void liberarInvolucrados(struct involucrados **involucrados, int tam) {
    int i;

    if (involucrados == NULL)
        return;

    for (i = 0; i < tam; i++) {
        if (involucrados[i] != NULL) {
            if (involucrados[i]->datosImputados != NULL) {
                liberarDatosImputados(involucrados[i]->datosImputados);
                involucrados[i]->datosImputados = NULL;
            }
            // No liberamos persona, asumiendo que es compartida
            free(involucrados[i]);
            involucrados[i] = NULL;
        }
    }

    free(involucrados);
}
void liberarDatosDiligencias(struct datosDiligencias *degligencias) {
    if (degligencias == NULL)
        return;

    free(degligencias->fechaInicio);
    free(degligencias->fechaFin);
    free(degligencias->descripcion);
    free(degligencias->estado);
    free(degligencias->tipoDiligencia);

    free(degligencias);
}
void liberarDatosCarpeta(struct datosCarpeta *datosCarpeta) {
    if (datosCarpeta == NULL)
        return;

    free(datosCarpeta->fecha);
    free(datosCarpeta->descripcion);

    if (datosCarpeta->datosDiligencias != NULL) {
        liberarDatosDiligencias(datosCarpeta->datosDiligencias);
        datosCarpeta->datosDiligencias = NULL;
    }

    if (datosCarpeta->datosDenuncia != NULL) {
        liberarDenuncia(datosCarpeta->datosDenuncia);
        datosCarpeta->datosDenuncia = NULL;
    }

    if (datosCarpeta->datosPersona != NULL) {
        liberarPersona(datosCarpeta->datosPersona);
        datosCarpeta->datosPersona = NULL;
    }

    free(datosCarpeta);
}
void liberarCausa(struct causa *causa) {
    struct nodoDatosCarpetas *actual;
    struct nodoDatosCarpetas *sig;

    if (causa == NULL)
        return;

    free(causa->ruc);

    if (causa->sentencia != NULL)
        free(causa->sentencia);

    if (causa->denuncia != NULL) {
        liberarDenuncia(causa->denuncia);
        causa->denuncia = NULL;
    }

    actual = causa->datosCarpetas;
    if (actual != NULL) {
        while (actual != NULL) {
            sig = actual->siguiente;
            if (actual->datosCarpeta != NULL) {
                liberarDatosCarpeta(actual->datosCarpeta);
                actual->datosCarpeta = NULL;
            }
            free(actual);
            actual = sig;
        }
    }

    causa->datosCarpetas = NULL;

    if (causa->involucrados != NULL) {
        liberarInvolucrados(causa->involucrados, causa->tamInvolucrados);
        causa->involucrados = NULL;
    }

    free(causa);
}

void eliminarCausa(struct nodoCausas **listaCausa, char *ruc) {
    struct nodoCausas *aEliminar;

    if (listaCausa == NULL) {
        printf("No se han encontrado causas.\n");
        return;
    }

    aEliminar = buscarNodoCausa(*listaCausa, ruc);
    if (aEliminar == NULL) {
        printf("No se han encontrado causas.\n");
        return;
    }

    if (aEliminar != NULL) {
        reenlazarCausas(listaCausa, aEliminar);
        liberarCausa(aEliminar->datosCausa);
        free(aEliminar);
        aEliminar = NULL;
        printf("Causa eliminada correctamente.\n");
    } else {
        printf("No se encontró una causa con ese RUC.\n");
    }
}
void eliminarDenuncia(struct nodoDenuncias **listaDenuncia, char *ruc) {
    struct nodoDenuncias *actual;

    if (listaDenuncia == NULL) {
        printf("No se han encontrado denuncias");
        return;
    }

    actual = *listaDenuncia;

    while (actual != NULL) {
        if (strcmp(actual->datosDenuncia->ruc, ruc) == 0) {
            reenlazarDenuncias(listaDenuncia, actual);
            liberarDenuncia(actual->datosDenuncia);
            free(actual);
            printf("Denuncia eliminada correctamente.\n");
            return;
        }
        actual = actual->siguiente;
    }
}
struct nodoPersonasABB* minimo(struct nodoPersonasABB *arbol) {
    while (arbol != NULL && arbol->izquierda != NULL)
        arbol = arbol->izquierda;
    return arbol;
}
void eliminarPersona(struct nodoPersonasABB **personas, char *rut) {
    int comparar;
    struct nodoPersonasABB *nodoEliminar;
    struct nodoPersonasABB *minNodo;
    struct persona *aux;

    if (personas == NULL || *personas == NULL) {
        printf("No se encontraron personas\n");
        return;
    }

    comparar = strcmp(rut, (*personas)->datosPersona->rut);

    if (comparar < 0) {
        eliminarPersona(&((*personas)->izquierda), rut);
    } else if (comparar > 0) {
        eliminarPersona(&((*personas)->derecha), rut);
    } else {
        nodoEliminar = *personas;

        if (nodoEliminar->izquierda == NULL) {
            *personas = nodoEliminar->derecha;
            liberarPersona(nodoEliminar->datosPersona);
            free(nodoEliminar);
        } else if (nodoEliminar->derecha == NULL) {
            *personas = nodoEliminar->izquierda;
            liberarPersona(nodoEliminar->datosPersona);
            free(nodoEliminar);
        } else {
            minNodo = minimo(nodoEliminar->derecha);
            aux = nodoEliminar->datosPersona;
            nodoEliminar->datosPersona = minNodo->datosPersona;
            minNodo->datosPersona = aux;

            eliminarPersona(&(nodoEliminar->derecha), aux->rut);
        }
    }

    printf("Persona eliminada correctamente.");
}
void eliminarInvolucradoPorRut(struct involucrados **involucrados, int tam, char *rut) {
    struct involucrados *involucrado;
    int i;

    involucrado = buscarInvolucradoPorRut(involucrados, tam, rut);
    if (involucrado == NULL) {
        printf("No se encontró involucrado con RUT %s.\n", rut);
        return;
    }

    if (involucrado->tipoInvolucrado == 2 && involucrado->datosImputados != NULL) {
        liberarDatosImputados(involucrado->datosImputados);
        involucrado->datosImputados = NULL;
    }

    liberarPersona(involucrado->persona);
    involucrado->persona = NULL;

    for (i = 0; i < tam; i++) {
        if (involucrados[i] == involucrado) {
            free(involucrados[i]);
            involucrados[i] = NULL;
            break;
        }
    }

    printf("Involucrado con RUT %s eliminado correctamente.\n", rut);
}
void eliminarInvolucrado(struct nodoCausas **listaCausas, char *ruc, char *rut) {
    struct nodoCausas *actual;
    struct nodoCausas *inicio;

    if (listaCausas == NULL || *listaCausas == NULL) {
        printf("No hay causas registradas.\n");
        return;
    }

    actual = *listaCausas;
    inicio = *listaCausas;

    do {
        if (actual->datosCausa != NULL &&
            strcmp(actual->datosCausa->ruc, ruc) == 0 &&
            actual->datosCausa->involucrados != NULL) {
            eliminarInvolucradoPorRut(actual->datosCausa->involucrados,actual->datosCausa->tamInvolucrados,rut);
            return;
            }

        actual = actual->siguiente;
    } while (actual != inicio);

    printf("No se encontró la causa con RUC %s.\n", ruc);
}
void eliminarCarpetaDeCausa(struct nodoCausas **listaCausas, char *ruc) {
    struct nodoCausas *causa;
    struct nodoDatosCarpetas *actualCarpeta;
    struct nodoDatosCarpetas *sig;

    if (listaCausas == NULL) {
        printf("No hay causas registradas.\n");
        return;
    }

    causa = buscarNodoCausa(*listaCausas, ruc);
    if (causa == NULL) {
        printf("No se encontro una causas con ese RUC.\n");
        return;
    }

    actualCarpeta = causa->datosCausa->datosCarpetas;
    while (actualCarpeta != NULL) {
        sig = actualCarpeta->siguiente;
        liberarDatosCarpeta(actualCarpeta->datosCarpeta);
        free(actualCarpeta);
        actualCarpeta = sig;
    }

    causa->datosCausa->datosCarpetas = NULL;
    printf("Carpetas eliminadas correctamente.\n");
}
void eliminarDatoDeCarpetaPorTipo(struct nodoCausas **listaCausas, char *ruc, int tipoDeDato) {
    struct nodoCausas *causa;
    struct nodoDatosCarpetas *carpeta;
    struct nodoDatosCarpetas *aEliminar;
    char palabra[100];
    int coincide;

    // Verificar si la lista es válida
    if (listaCausas == NULL || *listaCausas == NULL) {
        printf("No hay causas registradas.\n");
        return;
    }

    causa = buscarNodoCausa(*listaCausas, ruc);
    if (causa == NULL) {
        printf("No se encontró una causa con ese RUC.\n");
        return;
    }

    carpeta = causa->datosCausa->datosCarpetas;

    while (carpeta != NULL) {
        if (carpeta->datosCarpeta != NULL && carpeta->datosCarpeta->tipoDeDato == tipoDeDato) {
            aEliminar = carpeta;
            carpeta = carpeta->siguiente; // Avanzar antes de modificar

            coincide = 0;

            switch (tipoDeDato) {
                case 1: // Declaraciones
                    printf("Ingrese RUT del que declara:\n");
                    scanf(" %[^\n]", palabra);
                    if (aEliminar->datosCarpeta->datosPersona != NULL &&
                        strcmp(aEliminar->datosCarpeta->datosPersona->rut, palabra) == 0) {
                        free(aEliminar->datosCarpeta->fecha);
                        aEliminar->datosCarpeta->fecha = NULL;

                        free(aEliminar->datosCarpeta->descripcion);
                        aEliminar->datosCarpeta->descripcion = NULL;

                        free(aEliminar->datosCarpeta->datosPersona);
                        aEliminar->datosCarpeta->datosPersona = NULL;

                        coincide = 1;
                    }
                    break;

                case 2: // Pruebas
                    printf("Ingrese descripción de la prueba a eliminar:\n");
                    scanf(" %[^\n]", palabra);
                    if (aEliminar->datosCarpeta->descripcion != NULL &&
                        strcmp(aEliminar->datosCarpeta->descripcion, palabra) == 0) {
                        free(aEliminar->datosCarpeta->descripcion);
                        aEliminar->datosCarpeta->descripcion = NULL;

                        free(aEliminar->datosCarpeta->fecha);
                        aEliminar->datosCarpeta->fecha = NULL;

                        coincide = 1;
                    }
                    break;

                case 3: // Diligencias
                    printf("Ingrese descripción de la diligencia a eliminar:\n");
                    scanf(" %[^\n]", palabra);
                    if (aEliminar->datosCarpeta->datosDiligencias != NULL &&
                        strcmp(aEliminar->datosCarpeta->datosDiligencias->descripcion, palabra) == 0) {
                        liberarDatosDiligencias(aEliminar->datosCarpeta->datosDiligencias);
                        aEliminar->datosCarpeta->datosDiligencias = NULL;
                        coincide = 1;
                    }
                    break;

                case 4: // Denuncia
                    printf("Ingrese RUC de la denuncia extra a eliminar:\n");
                    scanf(" %[^\n]", palabra);

                    if (aEliminar->datosCarpeta->datosDenuncia != NULL &&
                        strcmp(aEliminar->datosCarpeta->datosDenuncia->ruc, palabra) == 0) {
                        liberarDenuncia(aEliminar->datosCarpeta->datosDenuncia);
                        aEliminar->datosCarpeta->datosDenuncia = NULL;
                        coincide = 1;
                    }
                    break;

                default:
                    printf("Tipo de dato no válido.\n");
                    return;
            }

            if (coincide) {
                reenlazarDatosCarpeta(&(causa->datosCausa->datosCarpetas), aEliminar);
                free(aEliminar->datosCarpeta);
                aEliminar->datosCarpeta = NULL;
                free(aEliminar);
                aEliminar = NULL;

                printf("Dato eliminado correctamente.\n");
                return;
            } else {
                printf("No se encontró coincidencia con los datos ingresados.\n");
                return;
            }
        } else {
            carpeta = carpeta->siguiente;
        }
    }

    printf("No se encontraron datos del tipo especificado en carpetas.\n");
}
void menuEliminarCarpeta(struct ministerio *ministerio) {
    int opcion = -1;
    char ruc[30];

    while (opcion != 0) {
        printf("\n=========== MENU ELIMINAR DATOS CARPETA ===========\n");
        printf("1. Eliminar Carpeta Completa.\n");
        printf("2. Eliminar Declaraciones.\n");
        printf("3. Eliminar Pruebas.\n");
        printf("4. Eliminar Diligencias.\n");
        printf("5. Eliminar Denuncias.\n");
        printf("0  Volver.\n");
        printf("Ingrese opcion: ");
        scanf("%d", &opcion);
        (void)getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese RUC de carpeta a eliminar:\n");
            scanf(" %[^\n]", ruc);
            eliminarCarpetaDeCausa(&(ministerio->causas), ruc);
            break;

            case 2:
                printf("Ingrese RUC de declaracion a eliminar:\n");
            scanf(" %[^\n]", ruc);
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 1);
            break;

            case 3:
                printf("Ingrese RUC de prueba a eliminar:\n");
            scanf(" %[^\n]", ruc);
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 2);
            break;

            case 4:
                printf("Ingrese RUC de diligencia a eliminar:\n");
            scanf(" %[^\n]", ruc);
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 3);
            break;

            case 5:
                printf("Ingrese RUC de denuncia a eliminar:\n");
            scanf(" %[^\n]", ruc);
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 4);
            break;

            case 0:
                return;

            default:
                printf("Opcion no valida\n");
            break;
        }
    }
}
void menuEliminarCausa(struct ministerio *ministerio) {
    int opcion = -1;
    char rut[30];
    char ruc[30];
    struct nodoCausas *encontrado;

    if (ministerio == NULL) {
        printf("Ministerio no inicializado.\n");
        return;
    }

    while (opcion != 0) {
        printf("\n=========== MENU ELIMINAR CAUSA ===========\n");
        printf("1. Eliminar Causa\n");
        printf("2. Eliminar Carpeta\n");
        printf("3. Eliminar Involucrado\n");
        printf("4. Eliminar Sentencia\n");
        printf("0. Volver.\n");
        printf("Ingrese opcion:");
        scanf("%d", &opcion);
        (void)getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese RUC de la causa a eliminar:\n");
                scanf(" %[^\n]", ruc);
                eliminarCausa(&(ministerio->causas), ruc);
                break;

            case 2:
                menuEliminarCarpeta(ministerio);
                break;

            case 3:
                printf("Ingrese RUC de la causa y RUT del involucrado a eliminar.\n");
                scanf(" %[^\n]", ruc);

                scanf(" %[^\n]", rut);

                eliminarInvolucrado(&(ministerio->causas), ruc, rut);
                break;

            case 4:
                printf("Ingrese RUC de la sentencia a eliminar:\n");
                scanf(" %[^\n]", ruc);

                encontrado = buscarNodoCausa(ministerio->causas, ruc);
                if (encontrado != NULL && encontrado->datosCausa != NULL && encontrado->datosCausa->sentencia != NULL) {
                    free(encontrado->datosCausa->sentencia);
                    encontrado->datosCausa->sentencia = NULL;
                    printf("Sentencia eliminada correctamente.\n");
                } else {
                    printf("No se encontro sentencia para eliminar.\n");
                }
                break;

            case 0:
                return;

            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
}

/**=========================================================
	            SECCION MODIFICAR (Mauricio Morales)
=========================================================**/

void modificarDatosDiligencia(struct ministerio *ministerio) {
    // Variables declaradas al principio
    char ruc[20], fechaInicio[50], tipoDiligencia[50];
    char buffer[300];
    char *nuevaCadena;
    int opcion = -1;
    int nueva_prioridad = 0;  // usado en case 1
    struct datosDiligencias *diligencia = NULL;

    if (ministerio == NULL) {
        printf("Ministerio no válido.\n");
        return;
    }

    printf("Ingrese el RUC de la causa: ");
    scanf(" %[^\n]", ruc);

    printf("Ingrese la fecha de inicio de la diligencia (YYYY-MM-DD): ");
    scanf(" %[^\n]", fechaInicio);

    printf("Ingrese el tipo de diligencia: ");
    scanf(" %[^\n]", tipoDiligencia);


    diligencia = buscarDiligencia(ministerio, ruc, fechaInicio, tipoDiligencia);
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
        (void)getchar(); // limpiar buffer

        switch (opcion) {
            case 1:
                do {
                    printf("Ingrese nueva prioridad (1 = muy baja, ..., 5 = muy alta): ");
                    scanf("%d", &nueva_prioridad);
                    (void)getchar();
                    if (nueva_prioridad < 1 || nueva_prioridad > 5)
                        printf("Prioridad inválida. Intente nuevamente.\n");
                } while (nueva_prioridad < 1 || nueva_prioridad > 5);
                diligencia->prioridad = nueva_prioridad;
                printf("Prioridad actualizada correctamente.\n");
                break;

            case 2:
                printf("Ingrese nueva fecha inicio (YYYY-MM-DD): ");
                scanf(" %[^\n]", buffer);
                nuevaCadena = duplicarCadena(buffer);
                if (nuevaCadena) {
                    free(diligencia->fechaInicio);
                    diligencia->fechaInicio = nuevaCadena;
                    printf("Fecha inicio actualizada correctamente.\n");
                }
                break;

            case 3:
                printf("Ingrese nueva fecha fin (YYYY-MM-DD): ");
                scanf(" %[^\n]", buffer);
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

void modificarDatosCarpeta(struct ministerio *ministerio) {
    // Declaraciones al inicio
    char ruc[100];
    struct causa* causa;
    char fecha[100];
    int tipo;
    struct datosCarpeta *carpeta;
    int opcion = -1;
    char buffer[300];
    char* nuevaCadena;
    int nuevo_tipo;

    if (ministerio == NULL) {
        printf("Ministerio no válido.\n");
        return;
    }

    printf("Ingrese el RUC de la causa: ");
    fgets(ruc, sizeof(ruc), stdin);
    removerSaltoLinea(ruc);

    causa = buscarCausaPorRuc(ministerio->causas, ruc);
    if (causa == NULL) {
        printf("No se encontró una causa con ese RUC.\n");
        return;
    }

    if (causa->datosCarpetas == NULL) {
        printf("No hay carpetas investigativas en esta causa.\n");
        return;
    }

    printf("Ingrese la fecha de la carpeta que desea modificar (YYYY-MM-DD): ");
    fgets(fecha, sizeof(fecha), stdin);
    removerSaltoLinea(fecha);

    do {
        printf("Ingrese el tipo de dato (1=declaraciones, 2=pruebas generales, 3=diligencias, 4=denuncia): ");
        scanf("%d", &tipo);
        (void)getchar();

        if (tipo < 1 || tipo > 4) {
            printf("Tipo inválido. Intente nuevamente.\n");
        }
    } while (tipo < 1 || tipo > 4);

    carpeta = buscarCarpetaPorTipoYFecha(causa->datosCarpetas, tipo, fecha);
    if (carpeta == NULL) {
        printf("No se encontró una carpeta con esa fecha y tipo.\n");
        return;
    }

    while (opcion != 0) {
        printf("\n--- Modificar Datos de Carpeta ---\n");
        printf("1. Modificar fecha (Actual: %s)\n", carpeta->fecha);
        printf("2. Modificar descripción (Actual: %s)\n", carpeta->descripcion);
        printf("3. Modificar tipo de dato (Actual: %d)\n", carpeta->tipoDeDato);
        printf("0. Salir\n");
        printf("Seleccione una opción: ");

        scanf("%d", &opcion);
        (void)getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese nueva fecha (YYYY-MM-DD): ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    removerSaltoLinea(buffer);
                    nuevaCadena = duplicarCadena(buffer);
                    if (nuevaCadena != NULL) {
                        free(carpeta->fecha);
                        carpeta->fecha = nuevaCadena;
                        printf("Fecha actualizada correctamente.\n");
                    } else {
                        printf("Error al asignar memoria.\n");
                    }
                }
                break;

            case 2:
                printf("Ingrese nueva descripción: ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    removerSaltoLinea(buffer);
                    nuevaCadena = duplicarCadena(buffer);
                    if (nuevaCadena != NULL) {
                        free(carpeta->descripcion);
                        carpeta->descripcion = nuevaCadena;
                        printf("Descripción actualizada correctamente.\n");
                    } else {
                        printf("Error al asignar memoria.\n");
                    }
                }
                break;

            case 3:
                do {
                    printf("Ingrese nuevo tipo de dato (1=declaraciones, 2=pruebas, 3=diligencias, 4=denuncia): ");
                    scanf("%d", &nuevo_tipo);
                    (void)getchar();

                    if (nuevo_tipo < 1 || nuevo_tipo > 4) {
                        printf("Tipo inválido. Intente nuevamente.\n");
                    }
                } while (nuevo_tipo < 1 || nuevo_tipo > 4);

                carpeta->tipoDeDato = nuevo_tipo;
                printf("Tipo de dato actualizado correctamente.\n");
                break;

            case 0:
                printf("Saliendo de modificación de carpeta.\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }
    }
}

void modificarDenunciaMenu(struct ministerio *ministerio) {
    char ruc[20];
    char rut[20];
    char buffer[300];
    int opcion;
    char *nuevaCadena;
    struct denuncia *denunciaMod;
    struct persona *personaBuscada;


    opcion = -1;
    nuevaCadena = NULL;
    denunciaMod = NULL;
    personaBuscada = NULL;

    printf("Ingrese el RUT de la persona a la cual le pertenezca la denuncia que desea modificar: ");
    if (fgets(rut, sizeof(rut), stdin)) {
        removerSaltoLinea(rut);
    } else {
        printf("Error al leer el RUT.\n");
        return;
    }

    personaBuscada = buscarPersonaPorRut(ministerio->personas, rut);
    if (personaBuscada == NULL) {
        printf("Persona con RUT %s no encontrada.\n", rut);
        return;
    }
    if (personaBuscada->denuncias == NULL) {
        printf("La persona no tiene denuncias.\n");
        return;
    }

    printf("Ingrese el RUC de la denuncia que desea modificar: ");
    if (fgets(ruc, sizeof(ruc), stdin)) {
        removerSaltoLinea(ruc);
    } else {
        printf("Error al leer el RUC.\n");
        return;
    }

    denunciaMod = buscarDenunciaPorRuc(personaBuscada->denuncias, ruc);
    if (denunciaMod == NULL) {
        printf("No se encontró una denuncia con el RUC ingresado.\n");
        return;
    }

    while (opcion != 4) {
        printf("\n--- MODIFICAR DENUNCIA ---\n");
        printf("1. Modificar Fecha (Actual: %s)\n", denunciaMod->fecha);
        printf("2. Modificar Descripcion (Actual: %s)\n", denunciaMod->descripcion);
        printf("3. Modificar Tipo de Denuncia (Actual: %s)\n", denunciaMod->tipoDeDenuncia);
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);
        (void)getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese nueva fecha (YYYY-MM-DD): ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    removerSaltoLinea(buffer);
                    nuevaCadena = duplicarCadena(buffer);
                    if (denunciaMod->fecha != NULL) {
                        free(denunciaMod->fecha);
                    }
                    denunciaMod->fecha = nuevaCadena;
                    printf("Fecha modificada correctamente.\n");
                }
                break;

            case 2:
                printf("Ingrese nueva descripcion: ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    removerSaltoLinea(buffer);
                    nuevaCadena = duplicarCadena(buffer);
                    if (denunciaMod->descripcion != NULL) {
                        free(denunciaMod->descripcion);
                    }
                    denunciaMod->descripcion = nuevaCadena;
                    printf("Descripcion modificada correctamente.\n");
                }
                break;

            case 3:
                printf("Ingrese nuevo tipo de denuncia: ");
                if (fgets(buffer, sizeof(buffer), stdin)) {
                    removerSaltoLinea(buffer);
                    nuevaCadena = duplicarCadena(buffer);
                    if (denunciaMod->tipoDeDenuncia != NULL) {
                        free(denunciaMod->tipoDeDenuncia);
                    }
                    denunciaMod->tipoDeDenuncia = nuevaCadena;
                    printf("Tipo de denuncia modificado correctamente.\n");
                }
                break;

            case 4:
                printf("Saliendo del menu de modificacion.\n");
                break;

            default:
                printf("Opcion invalida. Intente de nuevo.\n");
        }
    }
}

void cambiarEstadoCausa(struct ministerio *ministerio, char *rucCausa) {
    int nuevoEstado;
    struct nodoCausas *nodoActual;

    nuevoEstado = 0;
    nodoActual = NULL;

    printf("Ingrese el nuevo estado para la causa (1=Archivada, 2=En progreso, 3=Cerrada, 4=En juicio): ");
    scanf("%d", &nuevoEstado);

    if (nuevoEstado != 1) {
        printf("Entrada invalida.\n");
    }

    if (nuevoEstado < 1 || nuevoEstado > 4) {
        printf("Estado invalido. Los estados validos son del 1 al 4.\n");
        return;
    }

    nodoActual = ministerio->causas;
    if (nodoActual == NULL) {
        printf("No hay causas registradas.\n");
        return;
    }

    do {
        if (nodoActual->datosCausa != NULL && nodoActual->datosCausa->ruc != NULL &&
            strcmp(nodoActual->datosCausa->ruc, rucCausa) == 0) {

            nodoActual->datosCausa->estadoCausa = nuevoEstado;

            printf("Estado de la causa con RUC %s cambiado a %d.\n", rucCausa, nuevoEstado);
            return;
        }

        nodoActual = nodoActual->siguiente;
    } while (nodoActual != ministerio->causas);

    printf("Causa con RUC %s no encontrada.\n", rucCausa);
}


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
        (void)getchar();

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
                    (void)getchar();
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
                    scanf("%d", &nuevo_estado);
                    (void)getchar();
                    if (nuevo_estado < 1 || nuevo_estado > 3) {
                        printf("Estado procesal no valido. Intente nuevamente.\n");
                    }
                } while (nuevo_estado < 1 || nuevo_estado > 3);

                datos->estadoProcesal = nuevo_estado;
                printf("Estado procesal actualizado correctamente.\n");
                break;

            case 0:
                break;

            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
}

void cambiarTipoInvolucrado(struct ministerio *ministerio) {
    char ruc[100];
    char rut[100];
    int nuevoTipo;
    int encontrado;
    int i;
    struct causa *c = NULL;
    struct involucrados *inv = NULL;

    if (ministerio == NULL) {
        printf("Ministerio no válido.\n");
        return;
    }

    printf("Ingrese el RUC de la causa: ");
    fgets(ruc, sizeof(ruc), stdin);
    removerSaltoLinea(ruc);

    c = buscarCausaPorRuc(ministerio->causas, ruc);
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
        (void)getchar();
        if (nuevoTipo < 1 || nuevoTipo > 4) {
            printf("Tipo inválido. Intente nuevamente.\n");
        }
    } while (nuevoTipo < 1 || nuevoTipo > 4);

    encontrado = 0;

    for (i = 0; i < c->tamInvolucrados; i++) {
        inv = c->involucrados[i];

        if (inv != NULL && inv->persona != NULL && strcmp(inv->persona->rut, rut) == 0) {
            encontrado = 1;

            if (inv->tipoInvolucrado == 2 && nuevoTipo != 2 && inv->datosImputados != NULL) {
                free(inv->datosImputados);
                inv->datosImputados = NULL;
            }

            inv->tipoInvolucrado = nuevoTipo;

            if (nuevoTipo == 2 && inv->datosImputados == NULL) {
                inv->datosImputados = (struct datosImputados *)malloc(sizeof(struct datosImputados));
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

void modificarPersonaPorRUT(struct ministerio *ministerio) { // Agregue cambiar rut
    char rut[20];
    char palabra[300];
    int opcion = -1;
    struct persona *persona = NULL;
    char *nuevaCadena = NULL;
    int nuevo_rol;

    printf("Ingrese RUT de la persona a modificar: ");
    scanf(" %[^\n]", rut);

    persona = buscarPersonaPorRut(ministerio->personas, rut);
    if (persona == NULL) {
        printf("Persona con RUT %s no encontrada.\n", rut);
        return;
    }

    do {
        printf("\n--- Modificar Persona (%s %s) ---\n", persona->nombre, persona->apellido);
        printf("1. Cambiar nombre\n");
        printf("2. Cambiar apellido\n");
        printf("3. Cambiar contraseña\n");
        printf("4. Cambiar rol (actual: %d)\n", persona->rol);
        printf("5. Cambiar Rut\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");

        scanf("%d", &opcion);
        (void)getchar(); // Limpiar '\n'
        switch (opcion) {
            case 1:
                printf("Nuevo nombre: ");
                if (fgets(palabra, sizeof(palabra), stdin)) {
                    palabra[strcspn(palabra, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabra);
                    if (nuevaCadena != NULL) {
                        free(persona->nombre);
                        persona->nombre = nuevaCadena;
                        printf("Nombre actualizado correctamente.\n");
                    }
                }
                break;

            case 2:
                printf("Nuevo apellido: ");
                if (fgets(palabra, sizeof(palabra), stdin)) {
                    palabra[strcspn(palabra, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabra);
                    if (nuevaCadena != NULL) {
                        free(persona->apellido);
                        persona->apellido = nuevaCadena;
                        printf("Apellido actualizado correctamente.\n");
                    }
                }
                break;

            case 3:
                printf("Nueva contraseña: ");
                if (fgets(palabra, sizeof(palabra), stdin)) {
                    palabra[strcspn(palabra, "\n")] = '\0';
                    nuevaCadena = duplicarCadena(palabra);
                    if (nuevaCadena != NULL) {
                        free(persona->contrasena);
                        persona->contrasena = nuevaCadena;
                        printf("Contraseña actualizada correctamente.\n");
                    }
                }
                break;

            case 4:
                do {
                    printf("Nuevo rol (1 = usuario común, 2 = fiscal, 3 = juez): ");


                    scanf("%d", &nuevo_rol);
                    (void)getchar();

                    if (nuevo_rol < 1 || nuevo_rol > 3) {
                        printf("Rol inválido. Intente nuevamente.\n");
                    }

                } while (nuevo_rol < 1 || nuevo_rol > 3);

                persona->rol = nuevo_rol;
                printf("Rol actualizado correctamente.\n");

            case 5:
                printf("Nuevo rut: ");
            if (fgets(palabra, sizeof(palabra), stdin)) {
                palabra[strcspn(palabra, "\n")] = '\0';
                nuevaCadena = duplicarCadena(palabra);
                if (nuevaCadena != NULL) {
                    free(persona->rut);
                    persona->rut = nuevaCadena;
                    printf("Rut actualizada correctamente.\n");
                }
            }
            break;
            case 0:
                printf("Modificación finalizada.\n");
                break;

            default:
                printf("Opción inválida. Intente nuevamente.\n");
        }
    } while (opcion != 0);
}

void menuModificar(struct ministerio *ministerio) {
    int opcion;
    char ruc[30];
    char rut[30];

    opcion = -1;
    ruc[0] = '\0';
    rut[0] = '\0';

    do {
        printf("\n=========== MENU MODIFICAR ===========\n");
        printf("1. Modificar datos de diligencia\n");
        printf("2. Modificar datos de carpeta\n");
        printf("3. Modificar denuncia\n");
        printf("4. Cambiar estado de causa\n");
        printf("5. Modificar imputado en causa\n");
        printf("6. Cambiar tipo de involucrado\n");
        printf("7. Modificar persona por RUT\n");
        printf("0. Volver.\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);
        (void)getchar();

        switch (opcion) {
            case 1:
                modificarDatosDiligencia(ministerio);
                break;

            case 2:
                modificarDatosCarpeta(ministerio);
                break;

            case 3:
                modificarDenunciaMenu(ministerio);
                break;

            case 4:
                printf("Ingrese el RUC de la causa para cambiar su estado: \n");
                scanf(" %[^\n]", ruc);
                cambiarEstadoCausa(ministerio, ruc);
                break;

            case 5:
                printf("Ingrese el RUC de la causa: \n");
                scanf(" %[^\n]", ruc);


                printf("Ingrese el RUT del imputado: ");
                scanf(" %[^\n]", rut);


                modificarImputado(ministerio, ruc, rut);
                break;

            case 6:
                cambiarTipoInvolucrado(ministerio);
                break;

            case 7:
                modificarPersonaPorRUT(ministerio);
                break;

            case 0:
                // volver
                break;

            default:
                printf("Opcion invalida. Intente nuevamente.\n");
        }

    } while (opcion != 0);
}

/**=========================================================
	            SECCION MOSTRAR (Cristobal Flores)
=========================================================**/

void mostrarUsuarioPorRut(struct nodoPersonasABB *personas, char *rutBuscado) {
    struct persona *personaBuscada;
    //se busca a la persona indicada
    if (personas == NULL) {
        printf("No hay personas registradas en el sistema.\n");
        return;
    }
    if (rutBuscado == NULL) {
        printf("Por favor, ingrese un RUT valido para buscar.\n");
        return;
    }

    personaBuscada = buscarPersonaPorRut(personas, rutBuscado);

    //si no se encuentra o algun dato es invalido, retorna mensaje de error
    if (personaBuscada == NULL)
    {
        printf("No se encontro ningun usuario con el RUT ingresado.\n");
        return;
    }

    //si se encuentra y no es null (paso el if anterior), muestra los datos de la persona
    printf("\n--- INFORMACION DE PERSONA ---\n");
    printf("Nombre      : %s\n", personaBuscada->nombre);
    printf("Apellido    : %s\n", personaBuscada->apellido);
    printf("Rut         : %s\n", personaBuscada->rut);

    /** 1 = usuario comun, 2 = fiscal, 3 = juez**/
    if (personaBuscada->rol == 1)
        printf("Rol         : Usuario Comun\n");
    else if(personaBuscada->rol == 2)
        printf("Rol         : Fiscal\n");
    else if(personaBuscada->rol == 3)
        printf("Rol         : Juez\n");
}

void mostrarTodosLosUsuarios(struct nodoPersonasABB *arbolPersonas)
{
    if (arbolPersonas == NULL)
        return;
    mostrarTodosLosUsuarios(arbolPersonas->izquierda);
    mostrarUsuarioPorRut(arbolPersonas, arbolPersonas->datosPersona->rut); // Mostrar usuario actual
    printf("\n"); // Separador visual
    mostrarTodosLosUsuarios(arbolPersonas->derecha);
}

void mostrarDenunciaPorRut(struct nodoPersonasABB *personas, char *rutBuscado) {
    struct persona *personaBuscada;
    struct nodoDenuncias *actual;
    int contadorDenuncias;

    if (personas == NULL) {
        printf("No hay personas registradas en el sistema.\n");
        return;
    }
    if (rutBuscado == NULL) {
        printf("Por favor, ingrese un RUT valido para buscar denuncias.\n");
        return;
    }

    //se busca a la persona indicada
    personaBuscada = buscarPersonaPorRut(personas, rutBuscado);

    //si no se encuentra o algun dato es invalido, retorna mensaje de error
    if (personaBuscada == NULL)
    {
        printf("No se encontro ningun usuario con el RUT ingresado.\n\n");
        return;
    }

    if (personaBuscada->denuncias == NULL)
    {
        printf("Este usuario no tiene denuncias asociadas.\n");
        return;
    }
    actual = personaBuscada->denuncias;
    contadorDenuncias = 0;

    printf("\n========================================\n");
    printf("Denuncias de %s %s | Rut: %s\n", personaBuscada->nombre, personaBuscada->apellido, personaBuscada->rut);
    printf("========================================\n");

    while (actual != NULL)
    {
        if (actual->datosDenuncia != NULL)
        {
            contadorDenuncias++;
            printf("\n--------- DENUNCIA %d ---------\n", contadorDenuncias);
            printf("RUC           : %s\n", actual->datosDenuncia->ruc);
            printf("Fecha         : %s\n", actual->datosDenuncia->fecha);
            printf("Descripcion   : %s\n", actual->datosDenuncia->descripcion);
            printf("Tipo de delito: %s\n", actual->datosDenuncia->tipoDeDenuncia);

            //Si el rut del denunciante es el mismo de la persona buscada significa que la persona envio esta denuncia
            if (strcmp(actual->datosDenuncia->denunciante->rut, personaBuscada->rut) == 0) {
                printf("Denuncia Enviada a %s %s\n", actual->datosDenuncia->denunciado->nombre,
                    actual->datosDenuncia->denunciado->apellido);
            }
            //si el rut del denunciado es el mismo de la persona buscada significa que la persona recibio esta denuncia
            if (strcmp(actual->datosDenuncia->denunciado->rut, personaBuscada->rut) == 0) {
                printf("Denuncia Recibida por %s %s\n", actual->datosDenuncia->denunciante->nombre,
                    actual->datosDenuncia->denunciante->apellido);
            }
        }
        actual = actual->siguiente;
    }
}

void mostrarTodasLasDenunciasDePersonas(struct nodoPersonasABB *arbolPersonas)
{
    if (arbolPersonas == NULL)
    {
        return;
    }

    mostrarTodasLasDenunciasDePersonas(arbolPersonas->izquierda);
    mostrarDenunciaPorRut(arbolPersonas, arbolPersonas->datosPersona->rut); // Mostrar denuncias de este usuario
    printf("\n"); // Separador visual
    mostrarTodasLasDenunciasDePersonas(arbolPersonas->derecha);
}

void mostrarDatosImputados(struct datosImputados *datosImputados) {
    if (datosImputados == NULL)
    {
        printf("Este imputado no tiene datos especificos.\n");
        return;
    }
    /**1 = Prision Preventiva, 2 = Arraigo nacional, 3 = firma periodica,
    4 = orden de alejamiento, 5 = arresto domicilario, 6 = libertad bajo fianza, 7 = ninguna**/
    printf("\n--- Datos Imputado Asociados ---\n");
    printf("Declaracion: %s\n", datosImputados->declaracion);

    if (datosImputados->estadoProcesal == 1) {
        printf("Estado procesal: Medida cautelar\n");
        if (datosImputados->medidasCautelar == 1) {
            printf("Medida cautelar: Prision Preventiva\n");
        }
        else if (datosImputados->medidasCautelar == 2) {
            printf("Medida cautelar: Arraigo nacional\n");
        }
        else if (datosImputados->medidasCautelar == 3) {
            printf("Medida cautelar: Firma periodica\n");
        }
        else if (datosImputados->medidasCautelar == 4) {
            printf("Medida cautelar: Orden de alejamiento\n");
        }
        else if (datosImputados->medidasCautelar == 5) {
            printf("Medida cautelar: Arresto domiciliario\n");
        }
        else if (datosImputados->medidasCautelar == 6) {
            printf("Medida cautelar: Libertad bajo fianza\n");
        }
        else if (datosImputados->medidasCautelar == 7) {
            printf("Medida cautelar: Ninguna, Imputado aun no posee medida cautelar.\n");
            return;
        }

        printf("Fecha inicio medida: %s\n", datosImputados->fechaInicioMedida);
        printf("Fecha fin medida: %s\n", datosImputados->fechaFinMedida);
    }
    else if (datosImputados->estadoProcesal == 2) {
        printf("Estado procesal: Formalizado\n");
    }
    else if (datosImputados->estadoProcesal == 3) {
        printf("Estado procesal: Sobreseido\n");
    }
}

void mostrarDatosDiligencia(struct datosDiligencias *diligencia)
{
    printf("\n--- Diligencia Asociada ---\n");
    printf("Prioridad      : %d\n", diligencia->prioridad);
    printf("Fecha inicio   : %s\n", diligencia->fechaInicio);
    printf("Fecha fin      : %s\n", diligencia->fechaFin);
    printf("Estado         : %s\n", diligencia->estado);
    printf("Tipo           : %s\n", diligencia->tipoDiligencia);
    printf("Descripcion    : %s\n", diligencia->descripcion);
}

void mostrarDatosDenunciaAdicionalEnCausa(struct denuncia *denuncia)
{
    printf("\n--- Denuncia Asociada ---\n");
    printf("RUC            : %s\n", denuncia->ruc);
    printf("Fecha          : %s\n", denuncia->fecha);
    printf("Descripcion    : %s\n", denuncia->descripcion);
    printf("Delito         : %s\n", denuncia->tipoDeDenuncia);
    if (denuncia->denunciante != NULL)
        printf("Denunciante    : %s %s (RUT: %s)\n", denuncia->denunciante->nombre,
            denuncia->denunciante->apellido,
            denuncia->denunciante->rut);
    if (denuncia->denunciado != NULL)
        printf("Denunciado     : %s %s (RUT: %s)\n", denuncia->denunciado->nombre,
            denuncia->denunciado->apellido,
            denuncia->denunciado->rut);
}


void mostrarDatosCarpetaCausaPorTipo(struct causa *causa, int tipoDeDato)
{
  	struct nodoDatosCarpetas *actual;
    int contador;

    if (causa == NULL)
    {
        printf("No se encontro la causa seleccionada.\n");
        return;
    }
    if (causa->datosCarpetas == NULL)
    {
        printf("Esta causa no contiene datos investigativos registrados.\n");
        return;
    }

    actual = causa->datosCarpetas;
    contador = 0;

    while (actual != NULL)
    {
        if (actual->datosCarpeta != NULL && actual->datosCarpeta->tipoDeDato == tipoDeDato)
        {
            contador++;
            printf("\n========================================\n");
            printf("DATO DE CARPETA #%d\n", contador);
            printf("========================================\n");

            if (actual->datosCarpeta->datosPersona != NULL)
            {
                printf("Persona asociada:\n");
                printf("  Nombre       : %s\n", actual->datosCarpeta->datosPersona->nombre);
                printf("  Apellido     : %s\n", actual->datosCarpeta->datosPersona->apellido);
                printf("  Rut          : %s\n", actual->datosCarpeta->datosPersona->rut);
            }

            printf("Fecha          : %s\n", actual->datosCarpeta->fecha);
            printf("Descripcion    : %s\n", actual->datosCarpeta->descripcion);

            if (tipoDeDato == 1)
                printf("Tipo de dato   : Declaracion\n");
            else if (tipoDeDato == 2)
                printf("Tipo de dato   : Prueba general (Fotos, videos, etc)\n");
            else if (tipoDeDato == 3)
            {
                printf("Tipo de dato   : Diligencia\n");
                mostrarDatosDiligencia(actual->datosCarpeta->datosDiligencias);
            }
            else if (tipoDeDato == 4) {
                printf("Tipo de dato   : Denuncia\n");
                mostrarDatosDenunciaAdicionalEnCausa(actual->datosCarpeta->datosDenuncia);
            }
            else
                printf("Tipo de dato   : Desconocido\n");
        }
        actual = actual->siguiente;
    }

    if (contador == 0)
    {
        if (tipoDeDato == 1)
            printf("No existen declaraciones en la carpeta investigativa de esta causa.\n");
        else if (tipoDeDato == 2)
            printf("No existen pruebas generales en la carpeta investigativa de esta causa.\n");
        else if (tipoDeDato == 3)
            printf("No existen diligencias en la carpeta investigativa de esta causa.\n");
        else if (tipoDeDato == 4)
            printf("No existen denuncias adicionales en la carpeta investigativa de esta causa.\n");
        else
            printf("No existen datos del tipo solicitado en la carpeta investigativa de esta causa.\n");
    }
}

void mostrarTodosDatosCarpetaCausa(struct causa *causa)
{
    struct nodoDatosCarpetas *actual;
    struct datosCarpeta *carpeta;
    int contador;

    if (causa == NULL) {
        printf("No se encontro la causa seleccionada.\n");
        return;
    }
    if (causa->datosCarpetas == NULL) {
        printf("Esta causa no contiene datos investigativos registrados.\n");
        return;
    }

    actual = causa->datosCarpetas;
    contador = 0;

    while (actual != NULL)
    {
        carpeta = actual->datosCarpeta;
        if (carpeta != NULL)
        {
            contador++;
            printf("\n========================================\n");
            printf("DATO DE CARPETA #%d\n", contador);
            printf("========================================\n");

            if (carpeta->datosPersona != NULL)
            {
                printf("Persona asociada:\n");
                printf("  Nombre       : %s\n", carpeta->datosPersona->nombre);
                printf("  Apellido     : %s\n", carpeta->datosPersona->apellido);
                printf("  Rut          : %s\n", carpeta->datosPersona->rut);
            }

            printf("Fecha          : %s\n", carpeta->fecha);
            printf("Descripcion    : %s\n", carpeta->descripcion);

            if (carpeta->tipoDeDato == 1)
                printf("Tipo de dato   : Declaracion\n");
            else if (carpeta->tipoDeDato == 2)
                printf("Tipo de dato   : Prueba general (Fotos, videos, etc)\n");
            else if (carpeta->tipoDeDato == 3)
            {
                printf("Tipo de dato   : Diligencia\n");
                mostrarDatosDiligencia(carpeta->datosDiligencias);
            }
            else if (carpeta->tipoDeDato == 4) {
                printf("Tipo de dato   : Denuncia\n");
                mostrarDatosDenunciaAdicionalEnCausa(carpeta->datosDenuncia);
            }
            else
                printf("Tipo de dato   : Desconocido\n");

        }
        actual = actual->siguiente;
    }

    if (contador == 0)
        printf("No existen datos en la carpeta investigativa de esta causa.\n");
}

void mostrarDenunciaDeCausa(struct causa *causaActual) {
    struct denuncia *denuncia;
    struct causa *causaBuscada;

    if (causaActual == NULL) {
        printf("No se encontro la causa seleccionada.\n");
        return;
    }
    if (causaActual->denuncia == NULL) {
        printf("Esta causa no tiene denuncias asociadas.\n");
        return;
    }

    denuncia = causaActual->denuncia;

    printf("========================================\n");
    printf("DENUNCIA EN LA CAUSA RUC: %s\n", causaActual->ruc);
    printf("========================================\n");
    printf("RUC           : %s\n", denuncia->ruc);
    printf("Fecha         : %s\n", denuncia->fecha);
    printf("Descripcion   : %s\n", denuncia->descripcion);
    printf("Delito        : %s\n", denuncia->tipoDeDenuncia);

    if (denuncia->denunciante != NULL && denuncia->denunciado != NULL)
    {
        printf("Denunciante   : %s %s (RUT: %s)\n", denuncia->denunciante->nombre,
               denuncia->denunciante->apellido, denuncia->denunciante->rut);
        printf("Denunciado    : %s %s (RUT: %s)\n", denuncia->denunciado->nombre,
               denuncia->denunciado->apellido, denuncia->denunciado->rut);
    }
    else if (denuncia->denunciante == NULL && denuncia->denunciado != NULL)
    {
        printf("Denunciante   : Anonimo\n");
        printf("Denunciado    : %s %s (RUT: %s)\n", denuncia->denunciado->nombre,
                 denuncia->denunciado->apellido, denuncia->denunciado->rut);
    }
    else if (denuncia->denunciante != NULL && denuncia->denunciado == NULL)
    {
        printf("Denunciante   : %s %s (RUT: %s)\n", denuncia->denunciante->nombre,
                 denuncia->denunciante->apellido, denuncia->denunciante->rut);
        printf("Denunciado    : Contra los que resulten culpables\n");
    }
}

void mostrarTodosInvolucradosCausa(struct causa *causa) {
  	int i;

    if (causa == NULL) {
        printf("No se encontro la causa seleccionada.\n");
        return;
    }
    if (causa->involucrados == NULL) {
        printf("Esta causa no tiene involucrados registrados.\n");
        return;
    }

    for (i = 0; i < causa->tamInvolucrados; i++)
    {
        //1 = victima, 2 = imputado, 3 = fiscal, 4 = juez
        if (causa->involucrados[i] != NULL)
        {
            printf("\n========================================\n");
            printf("INVOLUCRADO #%d\n", i + 1);
            printf("========================================\n");
            printf("RUT           : %s\n", causa->involucrados[i]->persona->rut);
            printf("Nombre        : %s\n", causa->involucrados[i]->persona->nombre);
            printf("Apellido      : %s\n", causa->involucrados[i]->persona->apellido);
            if (causa->involucrados[i]->tipoInvolucrado == 1) {
                printf("Rol dentro de la causa: Victima\n");
            }
            else if (causa->involucrados[i]->tipoInvolucrado == 2) {
                printf("Rol dentro de la causa: Imputado\n");
                mostrarDatosImputados(causa->involucrados[i]->datosImputados);
            }
            else if (causa->involucrados[i]->tipoInvolucrado == 3) {
                printf("Rol dentro de la causa: Fiscal\n");
            }
            else if (causa->involucrados[i]->tipoInvolucrado == 4) {
                printf("Rol dentro de la causa: Juez\n");
            }
        }
    }

}

void mostrarInvolucradosCausaPorTipo(struct causa *causa, int tipoInvolucrado)
{
  	int i;
    int contador;

    if (causa == NULL) {
        printf("No se encontro la causa seleccionada.\n");
        return;
    }
    if (causa->involucrados == NULL || causa->tamInvolucrados == 0) {
        printf("Esta causa no tiene involucrados registrados.\n");
        return;
    }

    contador = 0;

    for (i = 0; i < causa->tamInvolucrados; i++)
    {
        if (causa->involucrados[i] != NULL && causa->involucrados[i]->tipoInvolucrado == tipoInvolucrado)
        {
            contador++;
            printf("\n========================================\n");
            printf("INVOLUCRADO #%d\n", contador);
            printf("========================================\n");
            printf("RUT           : %s\n", causa->involucrados[i]->persona->rut);
            printf("Nombre        : %s\n", causa->involucrados[i]->persona->nombre);
            printf("Apellido      : %s\n", causa->involucrados[i]->persona->apellido);

            // Imprime rol textual segun el tipo solicitado
            if (tipoInvolucrado == 1)
                printf("Rol dentro de la causa: Victima\n");
            else if (tipoInvolucrado == 2) {
                printf("Rol dentro de la causa: Imputado\n");
                mostrarDatosImputados(causa->involucrados[i]->datosImputados);
            }
            else if (tipoInvolucrado == 3)
                printf("Rol dentro de la causa: Fiscal\n");
            else if (tipoInvolucrado == 4)
                printf("Rol dentro de la causa: Juez\n");
            else
                printf("Rol dentro de la causa: Desconocido\n");
        }
    }

    if (contador == 0) {
        if (tipoInvolucrado == 1)
            printf("No hay victimas en esta causa.\n");
        else if (tipoInvolucrado == 2)
            printf("No hay imputados en esta causa.\n");
        else if (tipoInvolucrado == 3)
            printf("No hay fiscales en esta causa.\n");
        else if (tipoInvolucrado == 4)
            printf("No hay jueces en esta causa.\n");
        else
            printf("No hay involucrados de ese tipo en esta causa.\n");
    }
}

void mostrarTodoDatoDeCausaPorRuc(struct nodoCausas *causas, char *rucBuscado) {
    struct causa *causaBuscada;

  	if (causas == NULL)
    {
        printf("No hay causas registradas en el sistema.\n");
        return;
    }
    if (rucBuscado == NULL)
    {
        printf("Ruc ingresado invalido.\n");
        return;
    }

    //se busca a la carpeta indicada
    causaBuscada = buscarCausaPorRuc(causas, rucBuscado);

    //si no se encuentra o algun dato es invalido, retorna mensaje de error
    if (causaBuscada == NULL)
    {
        printf("Se genero un error al buscar la causa o esta no existe\n");
        return;
    }

    printf("\n========================================\n");
    printf("Causa con Ruc: %s\n", causaBuscada->ruc);
    printf("========================================\n");

    // Seccion de denuncias
    printf("\n>> DENUNCIA REGISTRADA:\n");
    mostrarDenunciaDeCausa(causaBuscada);

    // Seccion de involucrados
    printf("\n>> INVOLUCRADOS:\n");
    mostrarTodosInvolucradosCausa(causaBuscada);

    // Seccion de datos de la carpeta
    printf("\n>> DATOS CARPETA INVESTIGATIVA:\n");
    mostrarTodosDatosCarpetaCausa(causaBuscada);

    printf("========================================\n\n");
}

void mostrarTodasLasCausas(struct nodoCausas *causas)
{
    struct nodoCausas *actual;
    actual = causas;
    do
    {
        mostrarTodoDatoDeCausaPorRuc(causas, actual->datosCausa->ruc);
        printf("\n"); // Separador visual
        actual = actual->siguiente;
    } while (actual != causas);
}

/**=========================================================
	            SECCION EXTRA (TODOS)
=========================================================**/

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
    scanf(" %[^\n]", palabra);


    nuevaPersona->rut = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaPersona->rut, palabra);

    printf("Ingrese su nombre.\n\n");
    printf("Ingrese opcion:");
    scanf(" %[^\n]", palabra);


    nuevaPersona->nombre = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaPersona->nombre, palabra);

    printf("Ingrese su apellido.\n\n");
    printf("Ingrese opcion:");
    scanf(" %[^\n]", palabra);


    nuevaPersona->apellido = (char *)malloc(strlen(palabra) + 1);
    strcpy(nuevaPersona->apellido, palabra);

    printf("Ingrese su rol (1 = Usuario, 2 = Fiscal, 3 = Juez).\n\n");
    printf("Ingrese opcion:");
    scanf("%d", &rol);
    (void)getchar();

    if (rol == 1) {
        nuevaPersona->rol = rol;
        nuevaPersona->contrasena = NULL;
    } else if (rol == 2 || rol == 3) {
        printf("Ingrese contrasena del sistema.\n\n");
        printf("Ingrese opcion:");
        scanf(" %[^\n]", palabra);


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
    agregarPersonas(ministerio, nuevaPersona);
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
        (void)getchar(); // Limpiar buffer

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
                (void)getchar();

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

void mostrarPorcentajeDiligencias(struct ministerio *ministerio)
{
    int opcion = -1;
    int totalPrioridad = 0, muyBaja = 0, baja = 0, media = 0, alta = 0, muyAlta = 0;
    struct nodoCausas *actualCausa;
    struct nodoDatosCarpetas *actualCarpeta;
    char ruc[50];
    struct causa *causa;

    if (ministerio == NULL || ministerio->causas == NULL) {
        printf("No se encontraron causas en el sistema\n");
        return;
    }

    while (opcion != 0) {
        printf("\n--- Porcentaje de Diligencias ---\n");
        printf("1. Mostrar porcentaje de diligencias en TODAS las causas\n");
        printf("2. Mostrar porcentaje de diligencias en UNA causa\n");
        printf("0. Volver\n");
        printf("Seleccione una opcion: ");
        scanf(" %d", &opcion);
        (void)getchar();
        totalPrioridad = muyBaja = baja = media = alta = muyAlta = 0;
        switch (opcion)
        {
            case 1:
                actualCausa = ministerio->causas;
                do
                {
                    actualCarpeta = actualCausa->datosCausa->datosCarpetas;
                    while (actualCarpeta != NULL)
                    {
                        if (actualCarpeta->datosCarpeta != NULL &&
                            actualCarpeta->datosCarpeta->tipoDeDato == 3 &&
                            actualCarpeta->datosCarpeta->datosDiligencias != NULL)
                        {
                            int prioridad = actualCarpeta->datosCarpeta->datosDiligencias->prioridad;
                            totalPrioridad++;
                            if (prioridad == 1) muyBaja++;
                            else if (prioridad == 2) baja++;
                            else if (prioridad == 3) media++;
                            else if (prioridad == 4) alta++;
                            else if (prioridad == 5) muyAlta++;
                        }
                        actualCarpeta = actualCarpeta->siguiente;
                    }
                    actualCausa = actualCausa->siguiente;
                } while (actualCausa != ministerio->causas);
                if (totalPrioridad == 0)
                {
                    printf("No hay diligencias registradas en el sistema.\n");
                    break;
                }
                printf("\nPorcentaje de prioridades entre TODAS las causas:\n");
                printf("Muy baja: %.2f%%\n", (muyBaja * 100.0) / totalPrioridad);
                printf("Baja    : %.2f%%\n", (baja * 100.0) / totalPrioridad);
                printf("Media   : %.2f%%\n", (media * 100.0) / totalPrioridad);
                printf("Alta    : %.2f%%\n", (alta * 100.0) / totalPrioridad);
                printf("Muy alta: %.2f%%\n", (muyAlta * 100.0) / totalPrioridad);
                break;

            case 2:
                printf("Ingrese el RUC de la causa: ");
                scanf(" %[^\n]", ruc);
                causa = buscarCausaPorRuc(ministerio->causas, ruc);
                if (causa == NULL)
                {
                    printf("No se encontro la causa indicada.\n");
                    break;
                }

                actualCarpeta = causa->datosCarpetas;
                while (actualCarpeta != NULL)
                {
                    if (actualCarpeta->datosCarpeta != NULL &&
                        actualCarpeta->datosCarpeta->tipoDeDato == 3 &&
                        actualCarpeta->datosCarpeta->datosDiligencias != NULL)
                    {
                        int prioridad = actualCarpeta->datosCarpeta->datosDiligencias->prioridad;
                        totalPrioridad++;
                        if (prioridad == 1) muyBaja++;
                        else if (prioridad == 2) baja++;
                        else if (prioridad == 3) media++;
                        else if (prioridad == 4) alta++;
                        else if (prioridad == 5) muyAlta++;
                    }
                    actualCarpeta = actualCarpeta->siguiente;
                }
                if (totalPrioridad == 0)
                {
                    printf("No hay diligencias registradas en esta causa.\n");
                    break;
                }
                printf("\nPorcentaje de prioridades en la causa RUC %s:\n", ruc);
                printf("Muy baja: %.2f%%\n", (muyBaja * 100.0) / totalPrioridad);
                printf("Baja    : %.2f%%\n", (baja * 100.0) / totalPrioridad);
                printf("Media   : %.2f%%\n", (media * 100.0) / totalPrioridad);
                printf("Alta    : %.2f%%\n", (alta * 100.0) / totalPrioridad);
                printf("Muy alta: %.2f%%\n", (muyAlta * 100.0) / totalPrioridad);
                break;

            case 0:
                break;

            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
}

void mostrarPorcentajesEstadoCausa(struct ministerio *ministerio)
{
    float totalCausas = 0, totalArchivada = 0, totalInvestigacion = 0, totalCerrado = 0, totalJuicio = 0;
    float promedioArchivada, promedioInvestigacion, promedioCerrado, promedioJuicio;
    struct nodoCausas *actual;

    if (ministerio == NULL || ministerio->causas == NULL) {
        printf("No se encontraron casuas en el sistema.");
        return;
    }

    actual = ministerio->causas;

    do {
        if (actual->datosCausa->estadoCausa == 1) {
            totalCausas++;
            totalArchivada++;
        }
        else if (actual->datosCausa->estadoCausa == 2) {
            totalCausas++;
            totalInvestigacion++;
        }
        else if (actual->datosCausa->estadoCausa == 3) {
            totalCausas++;
            totalCerrado++;
        }
        else if (actual->datosCausa->estadoCausa == 4) {
            totalCausas++;
            totalJuicio++;
        }
        actual = actual->siguiente;
    } while (actual != ministerio->causas);

    if (totalCausas == 0) {
        printf("No se encontraron casuas en el sistema.");
        return;
    }

    promedioArchivada = (totalArchivada / totalCausas) * 100;
    promedioInvestigacion = (totalInvestigacion / totalCausas) * 100;
    promedioCerrado = (totalCerrado / totalCausas) * 100;
    promedioJuicio = (totalJuicio / totalCausas) * 100;

    printf("--- Porcentaje estado causa ---\n");
    printf("El %.2f%% de las causas estan en estado 'archivada'\n", promedioArchivada);
    printf("El %.2f%% de las causas estan en estado 'investigacion en progreso'\n", promedioInvestigacion);
    printf("El %.2f%% de las causas estan en estado 'cerrada'\n", promedioCerrado );
    printf("El %.2f%% de las causas estan en estado 'en juicio'\n", promedioJuicio);
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
        (void)getchar(); // Limpia el salto de linea despues de scanf

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
                scanf(" %[^\n]", rutBuscado);
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

/**=========================================================
	            SECCION MENU (TODOS)
=========================================================**/

void menuAgregar(struct ministerio *ministerio){
    int opcion;
    int resultado;
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
            resultado = agregarPersonaMenu(ministerio);
            if (resultado == -3)printf("No se encontraron personas\n");
            if (resultado == -2)printf("Error al asignar memoria.\n");
            if (resultado == -1)printf("Error: ministerio o persona inválidos.\n");
            if (resultado == 0)printf("Esta persona ya se registró.\n");
            if (resultado == 1)printf("La persona fue agregada con exito.\n");
            break;
        }

        else if(opcion == 2){
        /*Opcion 2 agregar denuncia */
            resultado = agregarDenunciaMenu(ministerio);
            if (resultado == -3)printf("Denunciante y denunciado no encontrados, intente con un RUT valido\n");
            if (resultado == -2)printf("Error al asignar memoria\n");
            if (resultado == 0)printf("Persona no encontrada\n");
            if (resultado == 1)printf("Denuncia agregada correctamente. \n");
            break;
        }

        else if(opcion == 3){
        /*Opcion 3 agregar carpeta*/
            resultado = agregarCarpetaMenu(ministerio);
            if (resultado == -2)printf("Error al asignar memoria");
            if (resultado == -1)printf("Nueva carpeta no existe\n");
            if (resultado == 0)printf("no existe informacion sobre causas en el sistema.\n");
            if (resultado == 1)printf("Carpeta agregada exitosamente.\n");
            break;
        }
        else if (opcion == 4) {
        /*Opcion 4 agregar causa*/
            resultado = agregarCausaMenu(ministerio);
            if (resultado == -5)printf("Error al duplicar el RUC.\n");
            if (resultado == -4)printf("Ministerio o denuncia inválida.\n");
            if (resultado == -3)printf("No se encontro una denuncia con ese ruc que pertenezca al usuario entregado.\n");
            if (resultado == -2)printf("Error al asignar memoria para la causa.\n");
            if (resultado == -1)printf("Persona o sus denuncias fueron  no encontradas.\n");
            if (resultado == 1)printf("Causa agregada correctamente\n");
            break;
        }
        else if(opcion == 5){
        /*Opcion 5 agregar involucrado*/
            resultado = agregarInvolucradoMenu(ministerio);
            if (resultado == -2)printf("Error al asignar memoria");
            if (resultado == -1)printf("No se encontro una causa con ese RUC\n");
            if (resultado == 0)printf("Error: la causa o el involucrado están vacíos.\n");
            if (resultado == 1)printf("Involucrado agregado correctamente\n");

            break;
        }
        else{
            printf("Opcion invalida, intente nuevamente.\n");
        }
    }
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
                scanf(" %[^\n]", rut);
                personaEncontrada = buscarPersonaPorRut(ministerio->personas, rut);
                if (personaEncontrada != NULL)
                    printf("Persona encontrada: %s %s\n", personaEncontrada->nombre, personaEncontrada->apellido);
                else
                    printf("No se encontro persona con ese RUT.\n");
                break;

            case 2: // Denuncia por RUC en denuncias de persona
                printf("Ingrese RUT de la persona: ");
                scanf(" %[^\n]", rut);
                personaEncontrada = buscarPersonaPorRut(ministerio->personas, rut);
                if (personaEncontrada == NULL || personaEncontrada->denuncias == NULL) {
                    printf("No se encontro la persona o no tiene denuncias.\n");
                    break;
                }
                printf("Ingrese RUC de la denuncia: ");
                scanf(" %[^\n]", ruc);
                denunciaEncontrada = buscarDenunciaPorRuc(personaEncontrada->denuncias, ruc);
                if (denunciaEncontrada != NULL)
                    printf("Denuncia encontrada: %s\n", denunciaEncontrada->descripcion);
                else
                    printf("No se encontro la denuncia con ese RUC para esa persona.\n");
                break;

            case 3: // Causa por RUC
                printf("Ingrese RUC de la causa: ");
                scanf(" %[^\n]", ruc);
                causaActual = buscarCausaPorRuc(ministerio->causas, ruc);
                if (causaActual != NULL)
                    printf("Causa encontrada: %s\n", causaActual->ruc);
                else
                    printf("No se encontro la causa con ese RUC.\n");
                break;

            case 4: // Involucrado por RUT (en una causa)
                printf("Ingrese RUC de la causa: ");
                scanf(" %[^\n]", ruc);
                causaActual = buscarCausaPorRuc(ministerio->causas, ruc);
                if (causaActual == NULL || causaActual->involucrados == NULL) {
                    printf("No se encontro la causa o no tiene involucrados.\n");
                    break;
                }
                printf("Ingrese RUT del involucrado: ");
                scanf(" %[^\n]", rut);
                involucradoEncontrado = buscarInvolucradoPorRut(causaActual->involucrados, causaActual->tamInvolucrados, rut);
                if (involucradoEncontrado != NULL)
                    printf("Involucrado encontrado: %s %s\n", involucradoEncontrado->persona->nombre, involucradoEncontrado->persona->apellido);
                else
                    printf("No se encontro involucrado con ese RUT en esa causa.\n");
                break;

            case 5: // Buscar datos carpeta por tipo en una causa
                printf("Ingrese RUC de la causa: ");
                scanf(" %[^\n]", ruc);
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

void menuEliminar(struct ministerio *ministerio) {
    int opcion = -1;
    char rut[30];
    char ruc[30];
    struct persona *persona;

    while (opcion != 0) {
        printf("\n=========== MENU ELIMINAR ===========\n");
        printf("1. Eliminar persona.\n");
        printf("2. Eliminar causa.\n");
        printf("3. Eliminar denuncia.\n");
        printf("4. Eliminar datos de carpeta.\n");
        printf("5. Eliminar Involucrados.\n");
        printf("0. Volver.\n");
        printf("Ingrese una opcion:");
        scanf("%d", &opcion);
        (void)getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese RUT de la persona a eliminar:\n");
                scanf(" %[^\n]", rut);

                eliminarPersona(&(ministerio->personas), rut);
                break;

            case 2:
                menuEliminarCausa(ministerio);
                break;

            case 3:
                printf("Ingrese RUT del denunciante:\n");
                scanf(" %[^\n]", rut);


                persona = buscarPersonaPorRut(ministerio->personas, rut);
                if (persona == NULL)
                    printf("Persona no encontrada.\n");
                else {
                    printf("Ingrese RUC de la denuncia a eliminar:\n");
                    scanf(" %[^\n]", ruc);

                    eliminarDenuncia(&(persona->denuncias), ruc);
                }
                break;

            case 4:
                menuEliminarCarpeta(ministerio);
                break;

            case 5:
                printf("Ingrese RUC de la causa y RUT del involucrado a eliminar.\n");
                scanf(" %[^\n]", ruc);

                scanf(" %[^\n]", rut);

                eliminarInvolucrado(&(ministerio->causas), ruc, rut);
                break;

            case 0:
                // Volver al menú anterior
                break;

            default:
                printf("Opcion no valida.\n");
                break;
        }
    }
}

void menuMostrar(struct ministerio *ministerio) {
    int opcion;
    int segundaOpcion;
    char rut[32];
    char ruc[32];
    int tipo;
    struct causa *causaActual;

    opcion = -1;
    segundaOpcion = -1;

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
                        scanf(" %[^\n]", rut);
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
                        scanf(" %[^\n]", rut);
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
                        scanf(" %[^\n]", ruc);
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
                scanf(" %[^\n]", ruc);
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
                scanf(" %[^\n]", ruc);
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

void menuPrincipal(struct ministerio *ministerio) {
    int opcion = -1;
    while(opcion != 0) {
        // Imprime el menu principal de opciones
        printf("\n=========== MENU PRINCIPAL ===========\n");
        printf("1. Agregar\n");
        printf("2. Eliminar\n");
        printf("3. Modificar\n");
        printf("4. Buscar\n");
        printf("5. Mostrar\n");
        printf("6. Otras Funciones\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        (void)getchar(); // Limpia el salto de linea despues de scanf

        switch(opcion) {
            case 1:
                // Llama al menu para agregar elementos
                    menuAgregar(ministerio);
                    break;
            case 2:
                // Llama al menu para eliminar elementos
                    menuEliminar(ministerio);
                    break;
            case 3:
                // Llama al menu para modificar elementos
                    menuModificar(ministerio);
                    break;
            case 4:
                // Llama al menu para buscar elementos
                    menuBuscar(ministerio);
                    break;
            case 5:
                // Llama al menu para mostrar elementos
                    menuMostrar(ministerio);
                    break;
            case 6:
                // Llama al menu para usar funciones extras
                    menuExtra(ministerio);
                    break;
            case 0:
                printf("\nSaliendo del sistema.\n");
                    break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                    break;
        }
    }
}

int main(){

    struct ministerio *ministerio = (struct ministerio *)malloc(sizeof(struct ministerio));
    ministerio->personas = NULL;
    ministerio->causas = NULL;

    ingresarAlSistema(ministerio);
    menuPrincipal(ministerio);

    return 0;
}
