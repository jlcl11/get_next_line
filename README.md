*Este proyecto ha sido creado como parte del currículo de 42 por jocorral.*

# get_next_line

## Descripción

`get_next_line` es una función en C que devuelve, en cada llamada, la siguiente línea
leída de un descriptor de archivo (file descriptor). Llamándola en bucle se puede recorrer
un archivo, la entrada estándar o cualquier otro descriptor línea a línea, hasta el final.

```c
char	*get_next_line(int fd);
```

- **Devuelve** la línea leída, incluyendo el `\n` final (salvo que sea la última línea
  del archivo y este no termine en `\n`).
- **Devuelve `NULL`** cuando no queda nada por leer o si se produce un error
  (descriptor inválido, fallo de `read` o fallo de `malloc`).
- La línea devuelta se reserva con `malloc`; quien llama es responsable de liberarla
  con `free`.

El objetivo principal del proyecto es aprender a usar **variables estáticas** en C para
conservar información entre llamadas a una función.

Solo se usan las funciones autorizadas por el enunciado: `read`, `malloc` y `free`.

### Archivos

| Archivo                 | Contenido                                                        |
|-------------------------|------------------------------------------------------------------|
| `get_next_line.c`       | `get_next_line` y `split_stash` (separa la línea del resto)      |
| `get_next_line_utils.c` | Funciones auxiliares: `ft_strlen`, `ft_strchr`, `ft_strjoin_free`, `ft_extract`, `read_to_stash` |
| `get_next_line.h`       | Prototipos, includes y valor por defecto de `BUFFER_SIZE`        |

## Instrucciones

El proyecto no genera un ejecutable por sí solo: hay que compilarlo junto a un `main`
propio que llame a `get_next_line`.

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("archivo.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Compilación (el tamaño de buffer se elige con `-D BUFFER_SIZE=n`):

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
./a.out
```

Si no se indica `BUFFER_SIZE`, se usa el valor por defecto **42**, definido en
`get_next_line.h`. Si `BUFFER_SIZE <= 0`, la función devuelve siempre `NULL`.

Para leer de la entrada estándar basta con pasar `0` como descriptor:

```sh
echo -e "hola\nmundo" | ./a.out
```

Comprobación de fugas de memoria:

```sh
valgrind --leak-check=full ./a.out
```

## Algoritmo

### Idea general

`read` no sabe nada de líneas: lee bloques de `BUFFER_SIZE` bytes, que pueden contener
media línea, una línea o varias. Por eso hace falta guardar lo que sobra de una lectura
para la siguiente llamada. Para eso se usa una **variable estática**, `stash`, que
conserva su valor entre llamadas a `get_next_line`.

En cada llamada se hacen tres pasos:

1. **Leer hasta tener una línea completa** (`read_to_stash`).
   Mientras la `stash` no contenga un `\n` y `read` siga devolviendo datos, se lee un
   bloque de `BUFFER_SIZE` bytes en un buffer temporal y se concatena al final de la
   `stash` con `ft_strjoin_free`, que además libera la `stash` antigua.
   El bucle se detiene en cuanto aparece un `\n`, o cuando `read` devuelve `0` (fin de
   archivo) o `-1` (error).

2. **Comprobar si hay algo que devolver.**
   Si la `stash` es `NULL` (error) o está vacía (fin de archivo sin datos pendientes),
   se libera, se pone a `NULL` y se devuelve `NULL`.

3. **Separar la línea del resto** (`split_stash`).
   - Se calcula la longitud de la línea: hasta el primer `\n` incluido o, si no hay
     ninguno, toda la `stash` (última línea sin salto de línea).
   - Se copia esa parte en `line`.
   - Si queda texto después, se copia en `rest`.
   - Se libera la `stash` antigua y `rest` pasa a ser la nueva `stash`.
   - Se devuelve `line`.

Ejemplo con `BUFFER_SIZE = 4` y el archivo `"ab\ncd\nef"`:

| Llamada | Lecturas (`read`)  | `stash` antes de separar | Devuelve  | `stash` después |
|---------|--------------------|--------------------------|-----------|-----------------|
| 1       | `"ab\nc"`          | `"ab\nc"`                | `"ab\n"`  | `"c"`           |
| 2       | `"d\nef"`          | `"cd\nef"`               | `"cd\n"`  | `"ef"`          |
| 3       | fin de archivo (0) | `"ef"`                   | `"ef"`    | `NULL`          |
| 4       | fin de archivo (0) | `NULL`                   | `NULL`    | `NULL`          |

### Justificación

- **Leer solo lo necesario.** No se lee el archivo entero: en cuanto la `stash` contiene
  un `\n` se deja de llamar a `read`. Si la línea ya estaba completa en la `stash` de una
  llamada anterior, no se lee nada. Así la función funciona también con la entrada
  estándar, tuberías u otros descriptores que no tienen un tamaño conocido.
- **Una sola variable estática.** Basta un `char *` para guardar el texto pendiente. No
  hay variables globales.
- **El buffer de lectura va en el heap.** Se reserva con `malloc(BUFFER_SIZE + 1)` en
  lugar de declararse como array local, para que valores grandes como
  `BUFFER_SIZE=10000000` no desborden la pila. Se libera al terminar cada lectura.
- **Funciona con cualquier `BUFFER_SIZE`.** Con `BUFFER_SIZE=1` se hacen muchas lecturas
  pequeñas; con uno muy grande, pocas lecturas que pueden traer varias líneas de golpe.
  En ambos casos el sobrante queda en la `stash` para las siguientes llamadas.
- **Gestión de memoria y errores.**
  - `ft_strjoin_free` libera siempre la `stash` anterior, tanto si la reserva va bien
    como si falla.
  - Si `read` devuelve `-1`, se libera la `stash` y se devuelve `NULL`.
  - Si falla cualquier `malloc` al separar la línea del resto, se libera todo, la `stash`
    queda a `NULL` y se devuelve `NULL`, de modo que no hay fugas ni datos a medias.
  - Al llegar al final del archivo, la `stash` queda a `NULL`.

### Limitaciones

- La parte obligatoria gestiona **un único descriptor** a la vez: si se alterna entre
  varios descriptores, la `stash` se mezcla.
- Según el enunciado, el comportamiento es indefinido si el archivo cambia entre
  llamadas antes de llegar al final, o si se leen archivos binarios.
- Si se deja de llamar a la función antes de llegar al final, la `stash` conserva el
  texto pendiente hasta la siguiente llamada con ese descriptor.

## Recursos

- `man 2 read`, `man 3 malloc`, `man 3 free`
- [Variables estáticas en C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptor — Wikipedia](https://en.wikipedia.org/wiki/File_descriptor)
- [Valgrind — Quick Start Guide](https://valgrind.org/docs/manual/quick-start.html)
- [Norminette — 42 School](https://github.com/42School/norminette)
