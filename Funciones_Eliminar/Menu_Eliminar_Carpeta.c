`
void menuEliminarCarpeta(struct ministerio *ministerio) {
    int opcion = -1, exito;
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
            scanf("%s", ruc);
            (void)getchar();
            exito = eliminarCarpetaDeCausa(&(ministerio->causas), ruc);
            if (exito == 0)
                printf("No se pudo eliminar la carpeta.\n");
            else
                printf("Carpeta eliminada con exito. \n");
            break;

            case 2:
                printf("Ingrese RUC de declaracion a eliminar:\n");
            scanf("%s", ruc);
            (void)getchar();
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 1);
            break;

            case 3:
                printf("Ingrese RUC de prueba a eliminar:\n");
            scanf("%s", ruc);
            (void)getchar();
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 2);
            break;

            case 4:
                printf("Ingrese RUC de diligencia a eliminar:\n");
            scanf("%s", ruc);
            (void)getchar();
            eliminarDatoDeCarpetaPorTipo(&(ministerio->causas), ruc, 3);
            break;

            case 5:
                printf("Ingrese RUC de denuncia a eliminar:\n");
            scanf("%s", ruc);
            (void)getchar();
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
