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
