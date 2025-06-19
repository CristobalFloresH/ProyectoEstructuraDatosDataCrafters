void agregarPersonaMenu(struct ministerio *ministerio){
    nuevaPersona = (struct persona *)malloc(sizeof(struct persona));
    /*Se crea el struct persona y se le asigna memoria de inmediato, si el asignar memoria falla finaliza el programa*/

    if(nuevaPersona == NULL){
        printf("Error al asignar memora");
        return;
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

    agregarPersonas(&(ministerio), nuevaPersona);   
}
