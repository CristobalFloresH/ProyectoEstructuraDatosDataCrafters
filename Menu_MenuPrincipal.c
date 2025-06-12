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
        getchar(); // Limpia el salto de linea despues de scanf

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
