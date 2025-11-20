# README Proyecto Final

El proyecto ha sido desarrollado en el entorno de Visual Studio 2022, en C++ y con OpenGL.

# Como usarlo

Si abres el archivo *Graphics\_1.sln* dentro de la carpeta de *visual\_studio* y tienes el Visual Studio 2022 instalado se te abrirá la carpeta del proyecto. En la parte de arriba hallarás dos menús, debes clicar donde pone *Depurador local de Windows*.

Se abrirán dos pantallas, una de color negro, que es el *simbolo del sistema*, en este, al abrir el archivo, se mostrarán unas cuantas líneas. La primera tiene que ver con el *Polygon smoothing* que muestra el número de muestras habilitadas con esta técnica. La segunda línea tiene la información sobre si el *Multisample* está o no activado. El resto de líneas muestran información sobre si los objetos que se han de dibujar en la escena se han cargado bien o no.

La segunda pantalla es la encargada de mostrar la escena. Para moverse con la cámara de primera persona se deben usar las teclas *WASD* y para mover la cámara se ha de clicar el mouse antes de mover el ratón.

***

# Explicación de la escena

La escena tiene un fondo del tipo *SkyBox* de una pequeña aldea navideña nevada. En la escena se dibujan 10 objetos con 10 texturas diferentes y cada uno con su VAO. Los diez objetos son: el **Árbol de navidad**, la **Tierra**, la **Luna**, los **Anillos de Saturno** (que contienen la técnica de *Alpha Blending*), un *Goomba*, una caja de *Barbie*, un **Droide de\_Star Wars\_**, un **Coche**, una ***Taylor Swift*** y una ***Pokeball***.

Entre todos estos objetos, algunos llevan a cabo ciertos movimientos que ahora explicaré:

* **Árbol de navidad y la\_Pokeball\_:** El **Árbol de navidad** y la ***Pokeball*** rotan en bucle mediante el aumento de el ángulo en cada nueva actualización de la pantalla. Estos rotan gracias a la función *glm::rotate*.
* **Luna:** La **Luna** orbita al rededor de un punto fijo, el punto en el cual se halla la **Tierra**. Esta rota también en bucle y aumenta su ángulo en cada nueva actualización de la pantalla, también rotan gracias a la función *glm::rotate*.
* **Coche:** El **Coche** traza ochos continuamente moviéndose en cada actualización de pantalla. A la vez que va trazando los ochos también va modificando su posición en el eje Y, es decir, el Z en un sistema cartesiano, para simular una escena de *drifting*.
* ***Goomba*:** El ***Goomba*** salta cuando se clica la tecla del espacio en el teclado. Modifica su posición en Y y utiliza el tiempo para modificarla de manera gradual y hacerlo más suave. Si clicas por segunda vez mientras está saltando modifica su altura límite aumentándola y saltando más alto.
* **Droide,*Taylor* y la caja de *Barbie*:** Este movimiento es un movimiento encadenado. En primer lugar ***Taylor*** saltará hacia arriba en un tiempo *random* entre 1 y 5 segundos, una vez caiga el **Droide** lanzará una ofensiva hacia la caja de ***Barbie*** y esta empezará a saltar dando volteretas cuando llegue el droide. Para el salto de ***Taylor*** modificamos la posición en Y de ***Taylor*** y lo hacemos también en función del tiempo para que quede un movimiento más suave, utilizamos la formula de la caída libre para calcular el movimiento. Para el movimiento del **Droide** hacemos que este se desplace, también en función del tiempo, hacia la posición de la caja de ***Barbie***, no apunta a su posición actual sino al objeto. Por último la caja de ***Barbie*** se mueve modificando su posición en Y y el ángulo con la función de la parábola, también en función del tiempo.

***

# Función avanzada

En el apartado de la función avanzada no explicada en clase hemos decidido implementar el suavizado. Para ello hemos usado dos técnicas de suavizado:

* **Suavizado de contorno de polígonos:** La primera técnica de suavizado que hemos implementado ha sido la del suavizado del contorno de los polígonos. Hemos activado esta función mediante el uso de la línea *glEnable(GL\_POLYGON\_SMOOTH)* en el *draw*. Esta función suaviza y hace más bonitos los contornos de un objeto. Hemos aplicado esta técnica a 8 objetos.
* **Multimuestreo:** La segunda técnica de suavizado aplicada ha sido la del multimuestreo que se encarga de minimizar o reducir la cantidad de calculos realizados por el *fragment shader* a la hora de calcular sus valores.

***

# Rúbrica de evaluación

En cuanto a la rúbrica de evaluación, hemos intentado implementar lo siguiente de cada uno de los puntos:

* **Carga de modelos 3D:** Al menos 10 modelos cargados en la pantalla y 3 tipos distintos de VAO.
* **Texturas simples:** Al menos 10 texturas distintas.
* ***Skybox*:** Aparece un *Skybox*, sigue a la cámara, la imagen es clara, uso adecuado de *Culling* y prueba de profundidad.
* **Cámara:** Se implementó correctamente la cámara en primera persona.
* **Iluminación:** Usa *Blinn-Phong* y la luz viene de la dirección correcta y utiliza matriz normal.
* **Multitextura:** Tiene mapas de relieve y mapas especulares omapas nocturnos/diurnos.
* **Estructuras de datos y calidad del software:** El programa está bien estructurado utilizando funciones y un uso adecuado de los tipos de datos como estructuras, matrices o clases. Bien comentado y legible. Los nombres de las variables son descriptivos.
* **Animación:** Trayectoria de movimiento complicada con movimiento relativo para al menos 5 modelos.
* **Función avanzada:** Suavizado.