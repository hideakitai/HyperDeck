# HyperDeck

[BlackMagic Design HyperDeck](https://www.blackmagicdesign.com/jp/products/hyperdeckstudiomini) controller for Arduino via TCP


## Usage

``` C++
#include <HyperDeck.h>

// Ethernet stuff
uint8_t mac[] = {0xAB, 0xCD, 0xEF, 0x01, 0x23, 0x45};
const IPAddress ip (192, 168, 0, 201);

// HyperDeck IP
const IPAddress hyperdeck_ip{192, 168, 0, 194};

HyperDeck::Controller deck;

void setup() {
    Serial.begin(115200);
    delay(2000);

    // Ethernet stuff
    Ethernet.begin(mac, ip);

    deck.connect(hyperdeck_ip);
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
        }
    }
}
```


## APIs

``` C++
bool connect(const IPAddress& ip);
bool is_connected();

// void device_info(); // TODO: query
// void disk_list(); // TODO: query
// void disk_list(const size_t slot_id); // TODO: query
void quit();
void ping();
void preview(const bool b);
void play();
void play(const int speed);
void play_loop(const bool b);
void play_single_clip(const bool b);
// void play_range(); // TODO: query
void play_range(const size_t clip_id);
void play_range(const String& tc_in, const String& tc_out);
void play_range(const size_t frame_in, const size_t frame_out);
void play_range_clear();
// void play_on_startup(); // TODO: query
void play_on_startup(const bool b);
void play_on_startup_single_clip(const bool b);
// void play_option(); // TODO: query
void play_option(const StopMode mode);
void record();
void record(const String& name);
void record_spill();
void record_spill(const size_t slot_id);
void stop();
// void clips_count(); // TODO: query
// void clips_get(); // TODO: query
// void clips_get(const size_t clip_id); // TODO: query
// void clips_get(const size_t clip_id, const size_t count); // TODO: query
// void clips_get_version(const size_t version); // TODO: query
void clips_add(const String& name);
void clips_add(const size_t clip_id, const String& name);
void clips_add(const String& tc_in, const String& tc_out, const String& name);
void clips_remove(const size_t clip_id);
void clips_clear();
// void transport_info(); // TODO: query
// void slot_info(); // TODO: query
// void slot_info(const size_t slot_id); // TODO: query
void slot_select(const size_t slot_id);
// void slot_select(); // TODO:
void slot_unblock();
void slot_unblock(const size_t slot_id);
// void dynamic_range(); // TODO: query
// void notify(); // TODO: query
void notify_remote(const bool b);
void notify_transport(const bool b);
void notify_slot(const bool b);
void notify_configuration(const bool b);
void notify_drop_frames(const bool b);
void notify_display_timecode(const bool b);
void notify_timeline_position(const bool b);
void notify_playrange(const bool b);
void notify_dynamic_range(const bool b);
void goto_clip_start();
void goto_clip_end();
void goto_clip(const size_t n);
void goto_clip_forward(const size_t n);
void goto_clip_backward(const size_t n);
void goto_timeline_start();
void goto_timeline_end();
void goto_timeline(const size_t n);
void goto_timeline_forward(const size_t n);
void goto_timeline_backward(const size_t n);
void goto_timecode(const String& tc);
void goto_timecode_forward(const String& tc);
void goto_timecode_backward(const String& tc);
void goto_slot(const size_t slot_id);
void jog_timecode(const String& tc);
void jog_timecode_forward(const String& tc);
void jog_timecode_backward(const String& tc);
void shuttle(const int speed);
// void remote(); // TODO: query
void remote(const bool b);
void remote_override(const bool b);
// void configuration(); // TODO: query
void config_video_input(const VideoInput v_in);
void config_audio_input(const AudioInput a_in);
// void config_file_format(); // TODO:
void config_audio_codec(const AudioCodec codec);
void config_timecode_input(const TimecodeInput t_in);
void config_timecode_preset(const String& tc);
void config_audio_input_channels(const size_t ch);
void config_record_trigger(const RecordTrigger trig);
void config_record_prefix(const String& name);
void config_append_timestamp(const bool b);
// void uptiem(); // TODO: query
// void format_prepare(); // TODO:
// void format_confirm(); // TODO:
void identify(const bool b);
void watchdog_period(const size_t sec);
```


## Configurations

``` C++
namespace HyperDeck {
    enum class StopMode { LAST_FRAME, NEXT_FRAME, BLACK_SCREEN };
    enum class VideoInput { SDI, HDMI, COMPONENT };
    enum class AudioInput { EMBEDDED, XLR, RCA };
    enum class AudioCodec { PCM, AAC };
    enum class TimecodeInput { EXT, EMBEDDED, PRESET, CLIP };
    enum class RecordTrigger { NONE, RECORDBIT, TIMECODERUN};
}
```


## Refernce

- [HyperDeck Studio Disk Recorders Manual](https://documents.blackmagicdesign.com/UserManuals/HyperDeckManual.pdf)


## License

MIT
