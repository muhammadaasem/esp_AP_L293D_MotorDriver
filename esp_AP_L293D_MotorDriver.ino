#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

class APManager {
public:
    void setupAP(const char* ssid, const char* password) {
        WiFi.softAP(ssid, password);
        IPAddress myIP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(myIP);
    }
};

class CarController {
private:
    int LED;
    int right_forward;
    int right_reverse;
    int left_forward;
    int left_reverse;

public:
    // Initialization with pin configuration
    void begin(int pinLED, int pinRightForward, int pinRightReverse, int pinLeftForward, int pinLeftReverse) {
        LED = pinLED;
        right_forward = pinRightForward;
        right_reverse = pinRightReverse;
        left_forward = pinLeftForward;
        left_reverse = pinLeftReverse;

        pinMode(LED, OUTPUT);
        pinMode(right_forward, OUTPUT);
        pinMode(right_reverse, OUTPUT);
        pinMode(left_forward, OUTPUT);
        pinMode(left_reverse, OUTPUT);
    }

    void controlCar(int v_dir) {
        String status;
        digitalWrite(LED, HIGH);
        
        // Implementing the direction logic
        if (v_dir == 0) {
            status = "Stop";
            Serial.println(status);
            digitalWrite(right_forward, LOW);
            digitalWrite(right_reverse, LOW);
            digitalWrite(left_forward, LOW);
            digitalWrite(left_reverse, LOW);
        } else if (v_dir == 1) {
            status = "Move Forward";
            Serial.println(status);
            digitalWrite(right_forward, HIGH);
            digitalWrite(right_reverse, LOW);
            digitalWrite(left_forward, HIGH);
            digitalWrite(left_reverse, LOW);
        } else if (v_dir == -1) {
            status = "Move backward";
            Serial.println(status);
            digitalWrite(right_forward, LOW);
            digitalWrite(right_reverse, HIGH);
            digitalWrite(left_forward, LOW);
            digitalWrite(left_reverse, HIGH);
        } else if (v_dir == 2) {
            status = "Turn Right";
            Serial.println(status);
            digitalWrite(right_forward, HIGH);
            digitalWrite(right_reverse, LOW);
            digitalWrite(left_forward, LOW);
            digitalWrite(left_reverse, LOW);
        } else if (v_dir == -2) {
            status = "Turn Left";
            Serial.println(status);
            digitalWrite(right_forward, LOW);
            digitalWrite(right_reverse, LOW);
            digitalWrite(left_forward, HIGH);
            digitalWrite(left_reverse, LOW);
        } else if (v_dir == 3) {
            status = "Turn sharp left";
            Serial.println(status);
            digitalWrite(right_forward, LOW);
            digitalWrite(right_reverse, HIGH);
            digitalWrite(left_forward, HIGH);
            digitalWrite(left_reverse, LOW);
        } else if (v_dir == 4) { // Changed from 3 to 4 for sharp right
            status = "Turn sharp right";
            Serial.println(status);
            digitalWrite(right_forward, HIGH);
            digitalWrite(right_reverse, LOW);
            digitalWrite(left_forward, LOW);
            digitalWrite(left_reverse, HIGH);
        }

        digitalWrite(LED, LOW);
    }
};

class WebServerManager {
    ESP8266WebServer server;
    CarController *carController; // Pointer to CarController

public:
    // Constructor to pass a reference to CarController
    WebServerManager(CarController &controller) : carController(&controller) {}

    void setupServer() {
        server.on("/", std::bind(&WebServerManager::handleRoot, this));
        server.on("/command", std::bind(&WebServerManager::handleCommand, this));
        server.begin();
        Serial.println("HTTP server started");
    }

    void handleClient() {
        server.handleClient();
    }

private:
    void handleRoot() {
        String page = "<html><head><script>"
                      "function sendCommand(command) {"
                      "var xhr = new XMLHttpRequest();"
                      "xhr.open('GET', '/command?move=' + command, true);"
                      "xhr.send();"
                      "}"
                      "</script></head><body>"
                      "<h1>Car Control</h1>"
                      "<button onclick=\"sendCommand('0')\">Stop</button>"
                      "<button onclick=\"sendCommand('1')\">Forward</button>"
                      "<button onclick=\"sendCommand('-1')\">Backward</button>"
                      "<button onclick=\"sendCommand('2')\">Turn Right</button>"
                      "<button onclick=\"sendCommand('-2')\">Turn Left</button>"
                      "<button onclick=\"sendCommand('3')\">Sharp Left</button>"
                      "<button onclick=\"sendCommand('4')\">Sharp Right</button>"
                      "</body></html>";
        server.send(200, "text/html", page);
    }

    void handleCommand() {
        if (server.hasArg("move")) {
            int moveCommand = server.arg("move").toInt();
            carController->controlCar(moveCommand);
        }
        server.send(200, "text/plain", "OK");
    }
};




APManager apManager;
CarController carController;
WebServerManager webServerManager(carController);


int LED_PIN = LED_BUILTIN;//D3;
int RF_PIN = D1;//IN1
int RR_PIN = D2;//IN2
int LF_PIN = D5;//IN3
int LR_PIN = D6;//IN4

void setup() {
    Serial.begin(9600);
    apManager.setupAP("ESP8266-Car1", "password123");
    carController.begin(LED_PIN, RF_PIN, RR_PIN, LF_PIN, LR_PIN);
    webServerManager.setupServer();
}

void loop() {
    webServerManager.handleClient();
}
