#include <ESP8266WiFi.h>

const char* SSID = "Literally, Your WiFi Name";
const char* PASSPHRASE =  "PASSPHRASE of Your Wifi";
const char* PORT = "80";
IPAddress IP  (192,168,10,30);
IPAddress GW (192,168,10,1);
IPAddress SN  (255,255,255,0);
String temp;

char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<style>
table, th, td {
  border: 1px solid black;
  border-collapse: collapse;
}
th, td {
  padding: 5px;
  text-align: left;    
}
</style>
</head>
<body>
<h2>Cell that spans two rows</h2>
<p>To make a cell span more than one row, use the rowspan attribute.</p>
<table style="width:100%">
  <tr>
    <th>Name:</th>
    <td>Bill Gates</td>
  </tr>
  <tr>
    <th rowspan="2">Telephone:</th>
    <td>55577854</td>
  </tr>
  <tr>
    <td>55577855</td>
  </tr>
</table>

</body>
</html>
)=====";

WiFiServer server(80);

void setup() {
  // put your setup code here, to run once:

   Serial.begin(9600);
   Serial.println();

   Serial.printf("Connecting to the Wifi: %s", SSID);
   WiFi.begin(SSID, PASSPHRASE);


  while (WiFi.status() != WL_CONNECTED)
   {
     delay(500);
     Serial.print(".");
   }
  Serial.println(" Connected Successfully!");

  Serial.println("Starting Web Server...");

  server.begin();
  delay(3000);

  Serial.printf("Web server listenin at %s:%s \n", WiFi.localIP().toString().c_str(),PORT);
}

void loop()
{
 
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("\n[Client connected]");

    //======================================================================
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
       {
          
           char req = client.read();
           temp += req;
           Serial.print(req);
           if (req == '\n'){

               if(temp.length() > 2){
                Serial.println(temp.length());
                  temp = ""; 
                  
                
                } else{
                    Serial.println("End of Client Request...");
                    client.print(FPSTR(index_html));

//                   client.println("HTTP/1.1 200 OK");
//                   client.println("Content-Type: text/html");
//                   client.println("Connection: close");
//                   client.println();
//
//                  client.println("<!DOCTYPE html><html>");
//                  client.println("<body><h1>TEST123</h1>");
//                  client.println("</body></html>");
//                  client.println();
                  break;         
                    
                  }
               
            }
           
       }
    //=======================================================================
    
  }

    delay(1); // give the web browser time to receive the data
    // close the connection:
    client.stop();
    Serial.println("[Client disonnected]");
}


}
