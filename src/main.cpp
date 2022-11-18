#include <Arduino.h>
#include <WiFi.h>
#include "distribute.hpp"
#include "loadcell.hpp"
#include "solenoid.hpp"
#include "pwd.hpp"

// WiFiServer server(80);

static int colBottle = 0;
static int putBottle = 0;

void setup()
{
  Serial.begin(9600);

  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // WiFi.begin(ssid, password);

  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(500);
  //   Serial.print(".");
  // }

  // Serial.println("");
  // Serial.println("WiFi connected.");
  // Serial.println("IP address: ");
  // Serial.println(WiFi.localIP());

  // server.begin();

  solenoid_init();
  loadcell_init();
  loadcell_reset();
}

void loop()
{
  colBottle = (int)(loadcell_read() / 18.3);
  distribute(colBottle, putBottle);
  putBottle = colBottle;

  Serial.println("==============");
  Serial.print("mass      :  ");
  Serial.print(loadcell_read());
  Serial.println(" [g]");
  Serial.print("colBottle :  ");
  Serial.println(colBottle);
  Serial.println("==============");

  // WiFiClient client = server.available(); // listen for incoming clients

  // if (client)
  // {                                // if you get a client,
  //   Serial.println("New Client."); // print a message out the serial port
  //   String currentLine = "";       // make a String to hold incoming data from the client
  //   while (client.connected())
  //   { // loop while the client's connected
  //     Serial.print("=");
  //     if (client.available())
  //     { // if there's bytes to read from the client,
  //       Serial.println(client.available());
  //       char c = client.read(); // read a byte, then
  //       Serial.write(c);        // print it out the serial monitor
  //       if (c == '\n')
  //       { // if the byte is a newline character
  //         // if the current line is blank, you got two newline characters in a row.
  //         // that's the end of the client HTTP request, so send a response:
  //         if (currentLine.length() == 0)
  //         {
  //           // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
  //           // and a content-type so the client knows what's coming, then a blank line:
  //           client.println("HTTP/1.1 200 OK");
  //           client.println("Content-type:text/html");
  //           client.println();

  //           // the content of the HTTP response follows the header:
  //           client.print("<a href=\"/S1\">Solenoid(Left)</a><br><br>");
  //           client.print("<a href=\"/S2\">Solenoid(Middle)</a><br><br>");
  //           client.print("<a href=\"/S3\">Solenoid(Right)</a><br><br>");
  //           client.print("<a href=\"/\">RESET</a><br><br>");
  //           Serial.println("==========write html==========");

  //           // The HTTP response ends with another blank line:
  //           client.println();
  //           // break out of the while loop:
  //           break;
  //         }
  //         else
  //         { // if you got a newline, then clear currentLine:
  //           currentLine = "";
  //         }
  //       }
  //       else if (c != '\r')
  //       {                   // if you got anything else but a carriage return character,
  //         currentLine += c; // add it to the end of the currentLine
  //       }

  //       // Check to see if the client request was "GET /H" or "GET /L":
  //       if (currentLine.endsWith("GET /S1"))
  //       {
  //         for (int i = 0; i < 5; i++)
  //         {
  //           solenoid(s1);
  //           Serial.print(".");
  //         }
  //       }
  //       if (currentLine.endsWith("GET /S2"))
  //       {
  //         for (int i = 0; i < 1; i++)
  //         {
  //           solenoid(s2);
  //           Serial.print(".");
  //         }
  //       }
  //       if (currentLine.endsWith("GET /S3"))
  //       {
  //         for (int i = 0; i < 6; i++)
  //         {
  //           solenoid(s3);
  //           Serial.print(".");
  //         }
  //       }
  //     }
  //   }
  //   // close the connection:
  //   client.stop();
  //   Serial.println("Client Disconnected.");
  // }
}