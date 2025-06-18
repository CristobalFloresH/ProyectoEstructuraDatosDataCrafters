void ingresarAlSistema(struct ministerio *ministerio) {
    char palabra[100];
    int rol;
    struct persona *nuevaPersona;

    nuevaPersona = (struct persona *)malloc(sizeof(struct persona));

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
            strcpy(nuevaPersona->contrasen
