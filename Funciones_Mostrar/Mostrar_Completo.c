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

    struct nodoDatosCarpetas *actual = causa->datosCarpetas;
    int contador = 0;

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

void mostrarTodoDatoDeCausaPorRuc(struct nodoCausas *causas, char *rucBuscado) {
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
