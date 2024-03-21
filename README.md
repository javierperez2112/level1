# EDA #level1: Orbital simulation

## Integrantes del grupo y contribución al trabajo de cada integrante

* **Camila Agustina Castro:** modelo, bonus points.
* **Ignacio Joaquin Rojana Marcello:** vista, bonus points.
* **Javier Baltasar Pérez Losada:** optimización de modelo y vista, estructura del trabajo.

## Verificación del timestep

Se comprobó empíricamente que los timestep por debajo de 100 días por segundo a 60 FPS (timestep < 1.67 días) generan resultados casi idénticos después de 200 años de simulación. Para asegurar mayor precisión y por razones estéticas y de visualización, se decidió dejar el timestep en 60 días por segundo de simulación. Esto deja exactamente un día por fotograma cuando se visualiza a 60 FPS.

## Verificación del tipo de datos float

El tipo de datos `float` puede representar números con 17 cifras significativas, hasta alrededor de $3.4\cdot10^{+38}$.
Las componentes de las variables vectoriales no exceden $10^{13}$, y las variables escalares son menores que $2\cdot10^{30}$ (masa del Sol). Entonces, el valor máximo de `float` es varios órdenes de magnitud mayor a lo que se almacena, incluso para el ejemplo del agujero negro (varios miles de masas solares).

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

### Júpiter
<!-- En el caso que Jupiter fuera 1000 veces más grande el sistema solar se vería atraído por su fuerza gravitatoria, por lo que se observaría un movimiento alrederor del Sol y a su vez alrededor de Jupiter. Asímismo, luego de determinado tiempo, los planetas y asteroides se saldrían de sus orbitas y viajarían sin rumbo por el espacio. -->
Si Júpiter fuera 1000 veces más masivo, el Sistema Solar sería un sistema binario, ya que el Sol y Júpiter tendrían masas similares. En la simulación se puede observar como, al cambiar la masa del gigante gaseoso, varios planetas salen catapultados hacia órbitas más lejanas al Sol. En el caso de la Tierra, supera la velocidad de escape y sale despedida hacia el espacio profundo, haciendo imposible la vida como la conocemos.
| ![GIF_bonus](/images/jupiter.gif) |
| --- |

Para hacer este cambio, hay que incluir `#define BONUS_JUPITER` en _*ephemerides.h*_.

### Agujero negro
Si hubiera un agujero negro pasando cerca de o por nuestro Sistema Solar lo que sucederia sería que el sistema se vería atraído hacia el agujero negro y luego sería expulsado muy fuertemente fuera de su orbita.
| ![GIF_bonus](/images/agujero-negro.gif) |
| --- |

Para hacer este cambio, hay que incluir `#define BONUS_BLACK_HOLE` en _*ephemerides.h*_.

### Alpha Centauri
Visualización de Alpha Centauri:
| ![FOTO_bonus](/images/alpha-centauri.png) |
| --- |

Para hacer este cambio, hay que incluir `#define BONUS_ALPHA_CENTAURI` en _*OrbitalSim.h*_.

### Easter egg
Dentro de la función `configureAsteroid` hay una línea comentada que hace que el ángulo de la posición de todos los asteroides generados sea 0° en lugar de un número aleatorio, dejando todos los asteroides alineados. Con el paso del tiempo, estos asteroides van a acupar una distribución similar a la que tendrían sin esta línea.

| Primer instante | Pasados 20 años de simulación |
| :---: | :---: |
| ![easter-egg-1](/images/easter-egg-1.png) | ![easter-egg-2](/images/easter-egg-2.png) |

Para hacer este cambio, hay que incluir `#define BONUS_EASTER_EGG` en _*OrbitalSim.h*_.
