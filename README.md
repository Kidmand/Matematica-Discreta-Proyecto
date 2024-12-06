# Proyecto de Matematica Discreta II

## Integrantes 🤝
- Ramiro Lugo Viola
- Garcia Daian
- Matias Viola

## Descipción del Proyecto 🚀
Hay que completar ...

## Instalación y Ejecución 🛠️
Asegúrate de tener `C` y `MAKE` instalado en tu máquina.

1. Clona este repositorio:
```bash
   git clone https://github.com/ramiro-l/Proyecto_Matematica_Discreta_II.git
```
2. Ingrear al codigo: 
```bash
   cd ./src
```

3. Compilar: 
```bash
   make
```

4. Ejecutar: 
```bash
   make run
```

5. LImpiar: 
```bash
   make clean
```

## Ejecutar TESTS 🧪

1. Elije el test que deseas ejecutar de la carpeta `/tests`.
2. Ejecuta el test con el comando `make test FILE=tests/example.test.c`
3. Asegurece de que exista el achivo del test que quiere ejecutar. En este caso es `tests/example.test.c`

## Crear nuevos TESTS 🧪🛠️
Lea las instucciones en `tests/COMO_CREAR_TESTS.md`

## Formato de los Commits 📝
Las convenciones de commit utilizadas en este proyecto son las siguientes:

- **Tipo de Commit**: El tipo de commit proporciona contexto sobre el cambio realizado. Algunos ejemplos comunes incluyen `feat` para nuevas características, `fix` para correcciones de errores y `docs` para cambios en la documentación.

- **Ámbito Opcional**: El ámbito proporciona información adicional sobre el alcance del cambio, como el módulo o componente afectado este se pone entre () luego del tipo de commit.

- **Descripción del Cambio**: La descripción del cambio debe ser breve pero descriptiva, proporcionando suficiente información para entender el propósito del commit.

Ejemplo de un commit siguiendo estas convenciones:

```bash
feat(grafo): Se agrego createGrafo()
```

> [!IMPORTANT]
> Este proyecto sigue los **Conventional Commits** para mantener un historial claro y consistente de cambios.

Para obtener más información sobre Commits Convencionales, consulta la [web oficial](https://www.conventionalcommits.org/es/v1.0.0/).  
Aquí tienes [Conventional Commits para VSCode](https://marketplace.visualstudio.com/items?itemName=vivaxy.vscode-conventional-commits).
