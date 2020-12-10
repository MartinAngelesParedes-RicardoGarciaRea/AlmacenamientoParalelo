//si usas esp8266
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
// Incluímos la librería para poder controlar el servo
#include <Servo.h>

// Declaramos la variable para controlar el servo
Servo servoMotor;

const char* ssid = "ricardo";
const char* password =  "Ricardo1+!?|";

const int inputPin1 = 16;
const int inputPin2 = 5;
const int inputPin3 = 4;

int* list;
size_t count;
size_t capacity;
 
int valor1 = 0;
int valor2 = 0;
int valor4 = 0;
int valor5 = 0;

String btn1 = "ON";
String btn2 = "ON";
String cliente = "";

void CreateList(size_t _capacity)
{
  list = new int[_capacity];
  capacity = _capacity;
  count = 0;
}
 
// Añadir elemento al final de la lista
void AddItem(int item)
{
  ++count;
    
  if (count > capacity)
  {
    size_t newSize = capacity * 2;
    resize(newSize);
  } 
 
  list[count - 1] = item;
}
 
// Eliminar ultimo elemento de la lista
void RemoveTail()
{
  --count;
}
 
// Reducir capacidad de la lista al numero de elementos
void Trim()
{
  resize(count);
}
 
// Reescalar lista
void resize(size_t newCapacity)
{
  int* newList = new int[newCapacity];
  memmove(newList, list, count  * sizeof(int));
  delete[] list;
  capacity = newCapacity;
  list = newList;
}
 
// Muestra la lista por Serial para debug
void printList()
{
  Serial.print("Capacity:");
  Serial.print(capacity);
 
  Serial.print("  Count:");
  Serial.print(count);
 
  Serial.print("  Items:");
  for (size_t index = 0; index < count; index++)
  {
    Serial.print(list[index]);
    Serial.print(' ');
  }
  Serial.println();
}

void setup() {
  Serial.begin(9600);

    // Iniciamos el servo para que empiece a trabajar con el pin 9
  servoMotor.attach(02);

  // Inicializamos al ángulo 0 el servomotor
  servoMotor.write(0);

  servoMotor.read();

  pinMode(inputPin1, INPUT);
  pinMode(inputPin2, INPUT);

  WiFi.begin(ssid, password);

  Serial.print("Conectando...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }

  Serial.print("Conectado con éxito, mi IP es: ");
  Serial.println(WiFi.localIP());
  cliente =  WiFi.localIP().toString();
}

void loop() {

  valor1 = digitalRead(inputPin1);  //lectura digital de pin
  valor2 = digitalRead(inputPin2);  //lectura digital de pin
   
  Serial.println(valor1);
  Serial.println(valor2);

   
  Serial.println("Lista con 3 elementos");
  CreateList(2);
 
  Serial.println();
  //Serial.println("Introducir 1 y 2 elementos");
  AddItem(valor1);
  AddItem(valor2);
  //printList();
  
  btn1 =valor1;

  valor4 = digitalRead(inputPin1);  //lectura digital de pin
  valor5 = digitalRead(inputPin2);  //lectura digital de pin
     
  Serial.println(valor4);
  Serial.println(valor5);

if (valor4 == 1 && valor5 == 0) {
    // Vamos a tener dos bucles uno para mover en sentido positivo y otro en sentido negativo
    // Para el sentido positivo
    for (int i = 0; i <= 90; i++)
    {
      valor4 = digitalRead(inputPin1);  //lectura digital de pin
      valor5 = digitalRead(inputPin2);  //lectura digital de pin
      // Desplazamos al ángulo correspondiente
      servoMotor.write(i);
      // Hacemos una pausa de 25ms
      delay(25);
      int grados = servoMotor.read();
      btn1 = grados;
      Serial.println(grados);
      if (valor4 == valor5) {
        if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;
    String datos_a_enviar = "grad=" + btn1 + "&client="+cliente;

    http.begin("http://144.202.34.148:4003");        //Indicamos el destino
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Preparamos el header text/plain si solo vamos a enviar texto plano sin un paradigma llave:valor.

    int codigo_respuesta = http.POST(datos_a_enviar);   //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)

    if(codigo_respuesta>0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));   //Print return code

      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);

      }

    }else{

     Serial.print("Error enviando POST, código: ");
     Serial.println(codigo_respuesta);

    }

    http.end();  //libero recursos

  }else{

     Serial.println("Error en la conexión WIFI");

  }
        break;
      }
      }
    }

  if (valor5 == 1 && valor4 == 0) {
    // Para el sentido negativo
    for (int i = 89; i > 0; i--)
    {
      valor4 = digitalRead(inputPin1);  //lectura digital de pin
      valor5 = digitalRead(inputPin2);  //lectura digital de pin
      // Desplazamos al ángulo correspondiente
      servoMotor.write(i);
      // Hacemos una pausa de 25ms
      delay(25);
      int grados = servoMotor.read();
      btn1 = grados;
      Serial.println(grados);
      if (valor4 == valor5) {
        if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;
    String datos_a_enviar = "grad=" + btn1 + "&client="+cliente;

    http.begin("http://144.202.34.148:4003");        //Indicamos el destino
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Preparamos el header text/plain si solo vamos a enviar texto plano sin un paradigma llave:valor.

    int codigo_respuesta = http.POST(datos_a_enviar);   //Enviamos el post pasándole, los datos que queremos enviar. (esta función nos devuelve un código que guardamos en un int)

    if(codigo_respuesta>0){
      Serial.println("Código HTTP ► " + String(codigo_respuesta));   //Print return code

      if(codigo_respuesta == 200){
        String cuerpo_respuesta = http.getString();
        Serial.println("El servidor respondió ▼ ");
        Serial.println(cuerpo_respuesta);

      }

    }else{

     Serial.print("Error enviando POST, código: ");
     Serial.println(codigo_respuesta);

    }

    http.end();  //libero recursos

  }else{

     Serial.println("Error en la conexión WIFI");

  }
          break;
      }
    }
  }

 


  else{
    Serial.println("no hubo cambios");        
  }
 
  Serial.println();
  Serial.println("Ajustar tamaño");
  Trim();
  printList();
 
}
