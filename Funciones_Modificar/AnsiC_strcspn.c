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
