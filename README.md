# EDA #level1: Orbital simulation

## Integrantes del grupo y contribución al trabajo de cada integrante

* Camila Agustina Castro:
* Ignacio Joaquin Rojana Marcello:
* Javier Baltasar Pérez Losada:

## Verificación del timestep

Se comprobó empíricamente que los timestep por debajo de 100 días por segundo generan resultados casi idénticos después de 500 años de simulación. Para asegurar mayor precisión y por razones estéticas y de visualización, se decidió dejar el timestep en 60 días por segundo. Esto deja exactamente un día de simulación por fotograma cuando se visualiza a 60 FPS.

## Verificación del tipo de datos float

El tipo de datos `float` puede representar números con 17 cifras significativas, hasta alrededor de $`3.4\cdot10^{+38}`$.
Las componentes de las variables vectoriales no exceden $`10^{13}`$, y las masas y radios son menores que $`2\cdot10^{30}`$ (masa del Sol). Entonces, el valor máximo de `float` es varios órdenes de magnitud mayor a lo que se almacena, incluso para el ejemplo del agujero negro (varios miles de masas solares).

## Complejidad computacional con asteroides

### Simulación: **O(n<sup>2</sup>)**
El algoritmo original consiste en calcular las fuerzas entre cada par de cuerpos, ejecutándose en tiempo cuadrático. 
### Gráficos: **O(n)**
Se renderiza una esfera por cada cuerpo en la simulación, ejecutándose en tiempo lineal.

## Mejora de la complejidad computacional

### Simulación: **O(n)**
Como las masas de los asteroides son despreciables respecto a las de los demás cuerpos, se pueden ignorar las fuerzas que ejercen sobre los demás objetos. Esta solución se ejecuta en tiempo lineal respecto a la cantidad de asteroides.
### Gráficos: **O(n) optimizado**
Al representar a los asteroides como puntos en lugar de esferas, se ahorra mucho procesamiento sin comprometer la calidad de los gráficos. 

## Bonus points

### Alpha Centauri

### Easter egg
Dentro de la función `configureAsteroid` hay una línea comentada que hace que el ángulo de la posición de todos los asteroides generados sea 0° en lugar de un número aleatorio, dejando todos los asteroides alineados. Con el paso del tiempo, estos asteroides van a acupar una distribución similar a la que tendrían sin esta línea.
| Primer instante | Pasados 20 años de simulación |
| --------------- | ---------------- |
| ![easter-egg-1](/images/easter-egg-1.png) | ![easter-egg-2](/images/easter-egg-2.png) |
