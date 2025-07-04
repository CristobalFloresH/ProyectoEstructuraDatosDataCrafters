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
