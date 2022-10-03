/*
  Botón de pánico por M&V TECHNOLOGIE
  Canal:
  Facebook:
  Whatssap:
*/


/*Incluimos las librerías*/
//#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <ESP_Mail_Client.h>


/*Insertamos las credenciales de red*/
#define WIFI_SSID "Linux" //Nombre de RED
#define WIFI_PASSWORD "Virus.exe" //Cont

/*Configuración del servidor SMTP Live o Hotmail*/
//Para las cuentas Live o Hotmail, estas son las configuraciones del servidor SMTP:
//
//Servidor SMTP: smtp.live.com
//Nombre de usuario SMTP: dirección de correo electrónico completa de Live/Hotmail
//Contraseña SMTP: Su contraseña de Windows Live Hotmail
//Puerto SMTP: 587



/*Configuración del servidor SMTP de Gmail*/
//Puerto SMTP (TLS): 587
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

/* Datos de acceso a cuenta. */
#define AUTHOR_EMAIL "mandvtechnologie@gmail.com"
#define AUTHOR_PASSWORD "ypcsgpsprfaerkwx"

/* Correo electrónico del recipiente*/
#define RECIPIENT_EMAIL "manuel.a.p.v@hotmail.com"

/* Objeto SMTP para enviar el correo electrónico */
SMTPSession smtp;


/*Pines ESP8266 - NodeMCU 1.0(ESP-12E Module)*/
#define LEDCONEX 16 //Led de conección Wifi
#define LEDMSJ 2 //Led para verificar mensaje enviado
#define Pulsador 13 // Pulsador "PULL_DOWN"
//#define RELAY 12 //SIRENA

/* Variables*/
int Estado1 = 0;

void setup(){
  Serial.begin(115200);
  
  pinMode(LEDCONEX, OUTPUT);  //Led de conección Wifi
  pinMode(LEDMSJ, OUTPUT);   //Led para verificar mensaje enviado
//  pinMode(RELAY, OUTPUT);   //SIRENA
  pinMode(Pulsador, INPUT);// Pulsador "PULL_DOWN"
  
  Serial.println();
  Serial.print("Conectando a punto de acceso");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("Conectado a WiFi.");
  Serial.println("Direccion IP: ");
  digitalWrite(LEDCONEX,HIGH);
  Serial.println(WiFi.localIP());
  Serial.println();
  
  /* Habilite la depuración a través del puerto serie
   * ninguno depurar o 0
   * depuración básica o 1
  */
  digitalWrite(LEDMSJ,HIGH);
  smtp.debug(1);

  /* Solicita resultados de envió */
  //smtp.callback(smtpCallback);

  /* Configurar datos de sesión */
  ESP_Mail_Session session;

  /* Configurar la sesión */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declara la clase del mensaje */
  SMTP_Message message;

  /* Configura cabecera del mensaje */
  message.sender.name = "Manuel Perea";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Alerta";
  message.addRecipient("M&V Technologie", RECIPIENT_EMAIL);
 
  //Manda texto
  String textMsg = "Se a iniciado el sistema correctamente";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  /* Configura cabecera personalizada */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Conecta al servidor */
  if (!smtp.connect(&session))
    return;

  /* Manda correo y cierra sesión */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
  digitalWrite(LEDMSJ,LOW);
}

void loop(){
  Estado1 = digitalRead(Pulsador); //Indicamos que la variable "Estado1"Sea igual a la lectura del "Pulsador"

  if(WiFi.status() == WL_CONNECTED){
    digitalWrite(LEDCONEX, HIGH);
  }
  else{
    digitalWrite(LEDCONEX, LOW);
  }
  
  if(Estado1 == HIGH){ //Si se presiona el botón e ingresa un 1 o HIGH "alto" cumplirá el siguiente bucle
  for(int i=0; i<10; i=i +1){ //Se enviarán 10 mensajes 
  digitalWrite(LEDMSJ,HIGH);
  /** Enable the debug via Serial port
   * none debug or 0
   * basic debug or 1
  */
  smtp.debug(1);

  /* Set the callback function to get the sending results */
  //smtp.callback(smtpCallback);

  /* Declare the session config data */
  ESP_Mail_Session session;


  /* Configura la sesión */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = AUTHOR_EMAIL;
  session.login.password = AUTHOR_PASSWORD;
  session.login.user_domain = "";

  /* Declara la clase del mensaje */
  SMTP_Message message;

  /* Configura cabecera del mensaje */
  message.sender.name = "Manuel Perea";
  message.sender.email = AUTHOR_EMAIL;
  message.subject = "Alerta";
  message.addRecipient("M&V Technologie", RECIPIENT_EMAIL);
 
  //Manda texto
  String textMsg = "Se ha presionado el botón de pánico por favor verificar cámaras de seguridad y enviar personal policial";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  /* Configura cabecera personalizada */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Conecta al servidor */
  if (!smtp.connect(&session))
    return;

  /* Manda correo y cierra sesiÃ³n */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
  digitalWrite(LEDMSJ,LOW);
}
}
delay(200);
}
