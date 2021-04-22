#include <HyperDeck.h>

// WiFi stuff
const char* ssid = "your-ssid";
const char* pwd = "your-password";
const IPAddress ip(192, 168, 0, 201);
const IPAddress gateway(192, 168, 0, 1);
const IPAddress subnet(255, 255, 255, 0);

// HyperDeck IP
const IPAddress host {192, 168, 0, 194};

HyperDeck::ControllerWiFi deck;

void setup() {
    Serial.begin(115200);
    delay(2000);

    // WiFi stuff
    WiFi.begin(ssid, pwd);
    WiFi.config(ip, gateway, subnet);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.print("WiFi connected, IP = ");
    Serial.println(WiFi.localIP());

    Serial.print("connecting to hyperdeck at ");
    Serial.print(host);
    Serial.print("... ");
    if (deck.connect(host)) {
        Serial.println("SUCCESS");
    } else {
        Serial.println("FAILED");
    }
}

void loop() {
    while (Serial.available()) {
        char c = Serial.read();
        if (c == 'p') {
            deck.play();
        } else if (c == 's') {
            deck.stop();
        } else if (c == 'n') {
            deck.goto_clip_forward(1);
        } else if (c == 'b') {
            deck.goto_clip_backward(1);
        } else if (c == 'm') {
            static HyperDeck::StopMode m {HyperDeck::StopMode::BLACK_SCREEN};
            if (m == HyperDeck::StopMode::BLACK_SCREEN)
                m = HyperDeck::StopMode::LAST_FRAME;
            else if (m == HyperDeck::StopMode::LAST_FRAME)
                m = HyperDeck::StopMode::NEXT_FRAME;
            else if (m == HyperDeck::StopMode::NEXT_FRAME)
                m = HyperDeck::StopMode::BLACK_SCREEN;
            deck.play_option(m);
        } else if (c == 'l') {
            static bool b {true};
            deck.play_loop(b);
            b = !b;
        } else if (c == 'c') {
            static bool b {true};
            deck.play_single_clip(b);
            b = !b;
        }
    }
}
