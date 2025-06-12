void modificarPersonaPorRUT(struct ministerio *ministerio) { // Agregue cambiar rut
    char rut[20];
    char palabra[300];
    int opcion = -1;
    struct persona *persona = NULL;
    char *nuevaCadena = NULL;
    int nuevo_rol;

    printf("Ingrese RUT de la persona a modificar: ");
    scanf(" %[^\n]", rut);
    getchar(); // Limpia el salto de línea

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
        getchar(); // Limpiar '\n'
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
                    getchar();

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
