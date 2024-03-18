# EDA #level1: Orbital simulation

## Integrantes del grupo y contribución al trabajo de cada integrante

* Camila Agustina Castro:
* Ignacio Joaquin Rojana Marcello:
* Javier Baltasar Pérez Losada:

## Verificación del timestep

[completar]

## Verificación del tipo de datos float

El tipo de datos `float` puede representar números con 17 cifras significativas, hasta alrededor de $`3.4\cdot10^{+38}`$.
Las distancias, velocidades y aceleraciones no excederán $`10^{+13}`$, así que

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

[completar]
