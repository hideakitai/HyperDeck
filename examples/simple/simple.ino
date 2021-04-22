#include <HyperDeck.h>

// Ethernet stuff
uint8_t mac[] = {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45};
const IPAddress ip (192, 168, 0, 201);
// Ethernet with useful options
// const IPAddress dnss (192, 168, 0, 1);
// const IPAddress gateway (192, 168, 0, 1);
// const IPAddress subnet (255, 255, 255, 0);

// HyperDeck IP
const IPAddress host {192, 168, 0, 194};

HyperDeck::Controller deck;

void setup() {
    Serial.begin(115200);
    delay(2000);

    // Ethernet stuff
    Ethernet.begin(mac, ip);

    // Ethernet with useful options
    // Ethernet.begin(mac, ip, dnss, gateway, subnet); // full
    // Ethernet.setRetransmissionCount(4); // default: 8[times]
    // Ethernet.setRetransmissionTimeout(50); // default: 200[ms]

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
