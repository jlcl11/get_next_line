*Este proyecto ha sido creado como parte del currículo de 42 por jocorral.*

# get_next_line

## Descripción

`get_next_line` es una función en C que devuelve, en cada llamada, la siguiente línea
leída de un descriptor de archivo. El objetivo del proyecto es aprender a usar
**variables estáticas** para conservar información entre llamadas.

```c
char	*get_next_line(int fd);
```

Devuelve la línea leída (con su `\n`, si lo tiene) o `NULL` si no queda nada por leer
o hay un error. La línea se reserva con `malloc` y debe liberarse con `free`.

**Algoritmo.** `read` lee bloques de `BUFFER_SIZE` bytes que pueden contener media
línea o varias, así que lo que sobra se guarda en una variable estática (`stash`):

1. Se lee y se concatena a la `stash` hasta que contiene un `\n` o se llega al final.
2. Se extrae de la `stash` la línea (hasta el `\n` incluido) y se devuelve.
3. El resto queda en la `stash` para la siguiente llamada.

Así solo se lee lo necesario, funciona con cualquier `BUFFER_SIZE` y con descriptores
como la entrada estándar. La parte bonus usa una `stash` por descriptor para poder
alternar entre varios a la vez.

## Instrucciones

Los `main` de prueba están comentados al final de los `.c`: en `get_next_line.c`, el
main 1 lee de un fichero y el main 2 de la entrada estándar (stdin); en
`get_next_line_bonus.c`, el main 3 alterna líneas de dos ficheros. Descomenta el que
quieras usar y compila indicando el tamaño del buffer:

```sh
# Parte obligatoria
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c && ./a.out
# Bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c && ./a.out
```

## Recursos

- `man 2 read`, `man 3 malloc`, `man 3 free`
- [Variables estáticas en C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptors](https://www.geeksforgeeks.org/c/input-output-system-calls-c-create-open-close-read-write/)

**Uso de IA:** se ha usado como apoyo para redactar este README.
