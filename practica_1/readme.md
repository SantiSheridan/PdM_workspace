# Pratica Nro 1

## Objetivo 
Familiarizarse con el entorno de trabajo STM32CubeIDE + NUCLEO-F446RE + firmware. 

## Punto 1
Implementar un programa que haga parpadear el led de la placa NUCLEO-F446RE LD2.

El led debe permanecer encendido 200 ms con duty cycle 50%.


## Punto 2
Utilizar el pulsador (B1) para controlar el tiempo de encendido.  Cada vez que se presiona el pulsador el tiempo de encendido debe alternar entre 200 ms y 500 ms.

## Preguntas para pensar en el ejercicio:
- ¿De qué serviría usar un array de “tiempos” en el programa? ¿Qué pasa con nuestro programa si nos piden agregar/sacar/cambiar un tiempo de encendido? 
- ¿Cómo responde el programa a las pulsaciones, hay falsos positivos o pulsaciones no detectadas? 
- ¿Cuál es el mejor momento para leer el pulsador, luego de un ciclo completo de la secuencia o después de encender y apagar el led? ¿Qué diferencia hay entre estas alternativas?
- ¿Cambiaría las respuestas a las preguntas anteriores si el tiempo de encendido del led fuera sensiblemente más grande, 2 segundos por ejemplo? ¿Y si fuera  sensiblemente más chico, 50 ms por ejemplo?
