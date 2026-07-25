#include <WiFi.h> ;
const char* ssid     = "N" ;
const char* password = "1234567890" ;
WiFiServer server(80) ;
String header;
String output5State = "off" ;
String output21State = "off";
const int output5 = 5;
const int output21 = 21;
unsigned long currentTime = millis();
unsigned long previousTime = 0; //unsigned long is datatype for miliseconds and microseconds
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(output5, OUTPUT);
  pinMode(output21, OUTPUT);
  digitalWrite(output5, LOW);
  digitalWrite(output21, LOW);
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
  delay(500) ;
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
    WiFiClient client = server.available();   // WiFiClient is a funtion enabling connection to a network as a client, client is a name, server is the earlier declared name of WifiServer
  if (client) {       //if client=true (bool value), the loop runs                     
    Serial.println("New Client.");          
    String currentLine = "";  // empty string will accumulate HTTP request characters as they arrive              
    currentTime = millis();
    previousTime = currentTime; //honestly idk how necessary these two lines are
    while (client.connected()) { //loop while client connected = true
  if (client.available()) { // client available tells number of bytes waiting to arrive from the client, if it's greater than 0 the statement runs
  char c = client.read(); //reads one byte (one character) of data incoming from the client and removes it form the buffer
  Serial.write(c); //serial.write is used to display binary and raw byte data, watching the HTTP request raw as it arrives
  header += c; //string variable, which is enlarged by new characters of c, header shall contain the raw http text
  if (c == '\n'){ //if there is an end of line, each eline ends in '\n', very last line of the request is EMPTY
  if (currentLine.length() == 0){ //very last line of the request is EMPTY
  client.println("HTTP/1.1 200 OK"); // ESP writes its response to the browser: 200 OK means "success" (status line),
  client.println("Content-type:text/html"); // tells the browser "what follows is an HTML page"
  client.println("Connection: close"); // tells the browser this connection will close after this response.
  client.println(); // blank line - mandatory in HTTP
  if (header.indexOf("GET /21/on") >= 0){ // indexOf is a function that searches for a character in the HTTP request, if it finds s substring telling it to turn on gpio21 (returns a position
// being a value of 0 or above) the if statement runs, if it does not find such request it returns a negative value, meaning that the if statement does not run. "GET /21/on" is the name of
//the request sent by the browser when we want to turn on a gpio.
  Serial.println("GPIO 21 on");
  output21State = "on";
  digitalWrite(output21, HIGH);
  } else if (header.indexOf("GET /21/off") >= 0) {
  Serial.println("GPIO 21 off");
  output21State = "off";
  digitalWrite(output21, LOW);
  } else if (header.indexOf("GET /5/on") >= 0) {
  Serial.println("GPIO 5 on");
  output5State = "on";
  digitalWrite(output5, HIGH);
  } else if (header.indexOf("GET /5/off") >= 0) {
  Serial.println("GPIO 5 off");
  output5State = "off";
  digitalWrite(output5, LOW);
}
client.println("<!DOCTYPE html><html>"); // letting the browser know the document format (HTML)
client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"); // render page on phones with correct format instead of zoomed out
client.println("<link rel=\"icon\" href=\"data:,\">");
client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
client.println(".button2 {background-color: #555555;}</style></head>"); //CSS styling of HTML document
client.println("<body><h1>ESP32 Web Server</h1>"); // opens page body with a heading
client.println("<p>GPIO 21 - State " + output21State + "</p>"); //c++ meachanic: since output21state is a string, the + merges them into one string
if (output21State=="off") {
  client.println("<p><a href=\"/21/on\"><button class=\"button\">ON</button></a></p>");
} else {
  client.println("<p><a href=\"/21/off\"><button class=\"button button2\">OFF</button></a></p>"); //decides which button to show, green ON or grey OFF
}
client.println("<p>GPIO 5 - State " + output5State + "</p>");
if (output5State=="off") {
client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
} else {
client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
} // the same thing for gpio 5
client.println("</body></html>");
client.println(); //closes HTML response
break;
  } else{
    currentLine = ""; //this is an else to "if (currentLine.length() == 0)", if current line is not empty, clear it and make it empty
  }
  } else if (c != '\r') {
  currentLine += c;
} // the else for if (c == '\n'), if checked character is not a new line, it's checked whether it's a carriage return ('/r'), which moves the cursor to the beginning of the current line
// if it is so, it adds characters from currentLine to c
  }
}
// Clear the header variable
header = "";
// Close the connection
client.stop();
Serial.println("Client disconnected.");
Serial.println("");
} //cleanup code
}
