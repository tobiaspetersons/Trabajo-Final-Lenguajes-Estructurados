# Trabajo-Final-Lenguajes-Estructurados

Este sistema es un control de stock para un emprendimiento de ropa, desarrollado en C. Permite gestionar usuarios y prendas, controlar el inventario, realizar consultas y reportes, y mantener la información organizada en archivos de texto.

---

## Reglas de negocio

- **Prenda:**  
  - **Campos:** código, nombre, color, talle, costo, precio, stock, bajaLogica (estado: 1=activo, 0=inactivo).
  - El campo **costo** representa el costo de adquisición o fabricación, y **precio** el valor de venta.
- **Usuario:**  
  - **Campos:** nombreUsuario, contraseña, estado (1=activo, 0=inactivo).

---

## Funcionalidades principales

### Gestión de usuarios

- Registrar nuevos usuarios (no permite duplicados).
- Inhabilitar usuarios (baja lógica).
- Listar usuarios activos e inactivos (la contraseña se muestra oculta).
- Login seguro (usuario y contraseña).
- Usuario "admin" creado automáticamente en la primera ejecución.

### Gestión de prendas

- Agregar nuevas prendas al stock (no permite códigos repetidos).
- Modificar stock, costo o precio de una prenda.
- Dar de baja (inhabilitar) o volver a habilitar prendas.
- Listar prendas activas e inactivas.
- Validación de datos: no se permiten valores negativos ni precios menores al costo.

### Consulta y reportes

- Consultar stock disponible de una prenda por código.
- Buscar prenda por código y ver todos sus datos.
- Filtrar prendas por talle, color, o ambos.
- Reporte de inventario: muestra el total de prendas activas y el costo total de mercadería.
- Todos los listados muestran: código, nombre, color, talle, costo, precio, stock.

---

## Detalles técnicos

- Toda la información se almacena en archivos de texto dentro de la carpeta `data/`.
- Si los archivos no existen, se crean automáticamente al iniciar el programa.
- El sistema es modular y fácil de mantener.
- El menú es claro y permite navegar entre gestión de usuarios, prendas y consultas.

---
