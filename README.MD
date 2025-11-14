# 🕹️ Proyecto de Aprendizaje con SGDK

Este repositorio contiene un conjunto de experimentos y ejemplos creados para **aprender el uso de SGDK (Sega Genesis Development Kit)**.  
El objetivo es familiarizarse con el desarrollo para la **Sega Mega Drive / Genesis**, entendiendo cómo manejar gráficos, sonido, entrada de usuario y lógica básica de juego en C.

---

## 📘 Acerca de SGDK

**SGDK** es un kit de desarrollo gratuito para crear juegos en C para la consola **Sega Mega Drive / Genesis**.  
Proporciona herramientas y librerías que permiten compilar código moderno en un formato ejecutable compatible con la consola real o con emuladores.

- 📦 Repositorio oficial: [https://github.com/Stephane-D/SGDK](https://github.com/Stephane-D/SGDK)
- 🧰 Documentación: [https://sgdk.readthedocs.io](https://sgdk.readthedocs.io)

---

## 🧑‍💻 Objetivos del Proyecto

- Comprender la estructura básica de un proyecto SGDK.
- Aprender a compilar y ejecutar en emuladores (Gens, Kega Fusion, BlastEm...).
- Explorar gráficos, sprites y tiles.
- Implementar sonido y música.
- Gestionar la entrada del mando.
- Construir un prototipo de juego simple.

---

## ⚙️ Requisitos

- [SGDK instalado](https://github.com/Stephane-D/SGDK)
- [Java JDK 8+](https://adoptium.net/)
- [Emulador de Mega Drive](https://blastem.io/)
- [Visual Studio Code](https://code.visualstudio.com/) o tu editor preferido

Asegúrate de tener configuradas las variables de entorno de SGDK (`GDK` o `SGDK`) correctamente.

---

## 🏗️ Compilación y Ejecución

Desde la terminal, en la raíz del proyecto:

```bash
# Compila el proyecto
make

# Limpia los binarios anteriores
make clean
