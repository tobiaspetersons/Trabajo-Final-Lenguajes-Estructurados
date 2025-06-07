# Trabajo Final - Lenguajes Estructurados

Este sistema es un control de stock para un emprendimiento de ropa, desarrollado en C. Permite gestionar usuarios y prendas, controlar el inventario, registrar movimientos, realizar consultas y reportes, y mantener la información organizada en archivos de texto.

---

## Tabla de Contenidos

- [Reglas de negocio](#reglas-de-negocio)
- [Estructura de datos](#estructura-de-datos)
- [Funcionalidades principales](#funcionalidades-principales)
  - [Gestión de usuarios](#gestión-de-usuarios)
  - [Gestión de prendas](#gestión-de-prendas)
  - [Consultas y reportes](#consultas-y-reportes)
- [Validaciones y seguridad](#validaciones-y-seguridad)
- [Detalles técnicos](#detalles-técnicos)
- [Ejecución](#ejecución)
- [Estructura de archivos](#estructura-de-archivos)

---

## Reglas de negocio

- **Prenda:**  
  - **Campos:** código, nombre, color, talle, costo, precio, stock, estado (1=activo, 0=inactivo), foto.
  - El campo **costo** representa el costo de adquisición o fabricación, y **precio** el valor de venta.
  - El campo **estado** permite baja lógica (inhabilitar sin borrar).
- **Usuario:**  
  - **Campos:** nombreUsuario, contraseña, estado (1=activo, 0=inactivo), rol (0=usuario, 1=admin).
  - El usuario "admin" se crea automáticamente en la primera ejecución.

---

## Estructura de datos

- **Archivos de texto** en la carpeta `data/`:
  - `usuarios.txt`: usuarios registrados.
  - `prendas.txt`: prendas en stock.
- **Estructuras en C**:
  - `Prenda`: todos los campos de la prenda.
  - `Usuario`: todos los campos del usuario.
---

## Funcionalidades principales

### Gestión de usuarios

- Registrar nuevos usuarios (no permite duplicados).
- Inhabilitar usuarios (baja lógica, no se pueden auto-inhabilitar).
- Listar usuarios activos e inactivos (la contraseña se muestra oculta).
- Login seguro (usuario y contraseña, hasta 3 intentos).
- Usuario "admin" creado automáticamente en la primera ejecución.
- Roles: solo admin puede gestionar usuarios.

### Gestión de prendas

- Agregar nuevas prendas al stock (código autoincremental, no permite repetidos).
- Modificar nombre, color, talle, stock, costo, precio o foto de una prenda.
- Dar de baja (inhabilitar) o eliminar definitivamente prendas.
- Habilitar prendas inhabilitadas.
- Listar prendas activas e inactivas, con columnas alineadas.
- Validación de datos: no se permiten valores negativos ni precios menores al costo.
- No permite operar si no hay prendas activas/inactivas según corresponda.

### Consultas y reportes

- Consultar stock disponible de una prenda por código.
- Buscar prenda por código y ver todos sus datos.
- Filtrar prendas por talle, color, o ambos.
- Reporte de inventario: muestra el total de prendas activas y el costo total de mercadería.
- Todos los listados muestran: código, nombre, color, talle, costo, precio, stock, foto.
- Columnas alineadas para mejor visualización.

---

## Validaciones y seguridad

- Contraseña segura: mínimo 8 caracteres, una mayúscula, una minúscula y un número.
- No se permite registrar usuarios duplicados.
- No se permite inhabilitar el usuario propio.
- No se permite operar sobre prendas inexistentes o inactivas.
- Validación de entradas numéricas y de texto.
- Limpieza de buffer y consola para evitar errores de entrada y mejorar la experiencia.

---

## Detalles técnicos

- Toda la información se almacena en archivos de texto dentro de la carpeta `data/`.
- Si los archivos no existen, se crean automáticamente al iniciar el programa.
- El sistema es modular y fácil de mantener.
- El menú es claro y permite navegar entre gestión de usuarios, prendas y consultas.
- Uso de defines para tamaños de buffer y manejo seguro de cadenas.
- Compatible con sistemas Unix (Mac/Linux) y Windows (limpieza de consola adaptada).

---

## Ejecución

1. **Compilar:**

   ```sh
   gcc -Wall src/*.c -o stock
   ```

2. **Ejecutar:**

   ```sh
   ./stock
   ```

3. **Primer uso:**  
   Se crea el usuario admin con contraseña admin automáticamente.

---

## Estructura de archivos

/src
    main.c
    menu.c/h
    prendas.c/h
    usuarios.c/h
    auth.c/h
    utils.c/h
    ...
/data
    usuarios.txt
    prendas.txt

---
