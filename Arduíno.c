#include <Servo.h>
#include <math.h>

Servo servo1;
Servo servo2;

int pos1 = 0;
int pos2 = 0;

float d1 = 10;  // Distâncias
float d2 = 20;  
float d3 = 10;  

void pontoP(float theta1, float theta2, float d1, float d2, float d3);

void setup() {
    Serial.begin(9600); // Inicia a comunicação serial
    servo1.attach(9);   // Conecta o primeiro servo ao pino 9
    servo2.attach(10);  // Conecta o segundo servo ao pino 10
}

void loop() {
    // Move os servos simultaneamente
    for (pos1 = 1, pos2 = 1; pos1 < 90; pos1 += 1, pos2 += 2) {
        servo1.write(pos1);
        servo2.write(pos2);
        delay(15);
        pontoP(pos1, pos2, d1, d2, d3); // Calcula e imprime o ponto P
    }
    

    delay(1000); // Espera 1 segundo

    // Retorna os servos simultaneamente
    for (pos1 = 89, pos2 = 179; pos1 > 0; pos1 -= 1, pos2 -= 2) {
        servo1.write(pos1);
        servo2.write(pos2);
        delay(15);
        pontoP(pos1, pos2, d1, d2, d3); // Calcule e imprima o ponto P
    }

    delay(1000); // Espera 1 segundo
}
void pontoP(float theta1, float theta2, float d1, float d2, float d3) {
    // Conversão de graus para radianos
    theta1 = theta1 * (M_PI / 180);
    theta2 = theta2 * (M_PI / 180);

    // Matriz 1
    float matriz1[3][3] = {
        {cos(theta1), -sin(theta1), 10},
        {sin(theta1), cos(theta1), 0},
        {0, 0, 1}
    };

    // Matriz 2
    float matriz2[3][3] = {
        {cos(theta2), -sin(theta2), 20},
        {sin(theta2), cos(theta2), 0},
        {0, 0, 1}
    };

    // Matriz 3
    float matriz3[3][3] = {
        {1, 0, d1},
        {0, 1, 0},
        {0, 0, 1}
    };

    float matriz_transformacao[3][3];

    // Multiplica as matrizes na ordem correta: matriz1 * matriz2 * matriz3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matriz_transformacao[i][j] = matriz1[i][0] * matriz2[0][j] + matriz1[i][1] * matriz2[1][j] + matriz1[i][2] * matriz2[2][j];
        }
    }

    // Multiplica a matriz resultante pelo matriz3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matriz_transformacao[i][j] = matriz_transformacao[i][0] * matriz3[0][j] + matriz_transformacao[i][1] * matriz3[1][j] + matriz_transformacao[i][2] * matriz3[2][j];
        }
    }

    float vetor[3][1] = {
        {0},
        {0},
        {1}
    };

    float ponto_resultado[3][1];

    // Calcula o ponto P
    for (int i = 0; i < 3; i++) {
        ponto_resultado[i][0] = matriz_transformacao[i][0] * vetor[0][0] + matriz_transformacao[i][1] * vetor[1][0] + matriz_transformacao[i][2] * vetor[2][0];
    }

    // Exibe o ponto P resultante
    Serial.println("\nPonto P:");
    for (int i = 0; i < 3; i++) {
        Serial.print(ponto_resultado[i][0], 4);
        Serial.print("\n");
    }

    // Exibe os ângulos theta1 e theta2
    Serial.print("\nTheta1: ");
    Serial.print(theta1 * (180 / M_PI), 4); // Converte de radianos para graus
    Serial.print("\tTheta2: ");
    Serial.println(theta2 * (180 / M_PI), 4); // Converte de radianos para graus
}
