#pragma once
#ifndef ARDUINO_HYPERDECK_H
#define ARDUINO_HYPERDECK_H

#include <Arduino.h>
#include <Ethernet.h>

namespace arx {
namespace hyperdeck {

    enum class StopMode {
        LAST_FRAME,
        NEXT_FRAME,
        BLACK_SCREEN
    };
    enum class VideoInput {
        SDI,
        HDMI,
        COMPONENT
    };
    enum class AudioInput {
        EMBEDDED,
        XLR,
        RCA
    };
    enum class AudioCodec {
        PCM,
        AAC
    };
    enum class TimecodeInput {
        EXT,
        EMBEDDED,
        PRESET,
        CLIP
    };
    enum class RecordTrigger {
        NONE,
        RECORDBIT,
        TIMECODERUN
    };

    class Controller {
        EthernetClient tcp;
        static constexpr uint16_t HYPERDECK_PORT {9993};

    public:
        bool connect(const IPAddress& ip) {
            return tcp.connect(ip, HYPERDECK_PORT);
        }

        bool is_connected() {
            return tcp.connected();
        }

        void device_info() {}  // TODO: query

        void disk_list() {}  // TODO: query

        void disk_list(const size_t slot_id) {}  // TODO: query

        void quit() {
            tcp.println("quit");
        }

        void ping() {
            tcp.println("ping");
        }

        void preview(const bool b) {
            if (b)
                tcp.println("preview: enable: true");
            else
                tcp.println("preview: enable: false");
        }

        void play() {
            tcp.println("play");
        }

        void play(const int speed) {
            if ((speed >= -1600) && (speed <= 1600)) {
                tcp.println("play: speed:" + String(speed));
            } else {
                Serial.println("play speed must be from -1600 to 1600");
            }
        }

        void play_loop(const bool b) {
            if (b)
                tcp.println("play: loop: true");
            else
                tcp.println("play: loop: false");
        }

        void play_single_clip(const bool b) {
            if (b)
                tcp.println("play: single clip: true");
            else
                tcp.println("play: single clip: false");
        }

        void play_range() {}  // TODO: query

        void play_range(const size_t clip_id) {
            tcp.println("playrange set: " + String(clip_id));
        }

        void play_range(const String& tc_in, const String& tc_out) {
            tcp.println("playrange set: in: " + tc_in + " out: " + tc_out);
        }

        void play_range(const size_t frame_in, const size_t frame_out) {
            tcp.println("playrange set: timeline in: " + String(frame_in) + " timeline out: " + String(frame_out));
        }

        void play_range_clear() {
            tcp.println("playrange clear");
        }

        void play_on_startup() {}  // TODO: query

        void play_on_startup(const bool b) {
            if (b)
                tcp.println("play on startup: enable true");
            else
                tcp.println("play on startup: enable false");
        }

        void play_on_startup_single_clip(const bool b) {
            if (b)
                tcp.println("play on startup: single clip: true");
            else
                tcp.println("play on startup: single clip: false");
        }

        void play_option() {}  // TODO: query

        void play_option(const StopMode mode) {
            if (mode == StopMode::LAST_FRAME)
                tcp.println("play option: stop mode: lastframe");
            else if (mode == StopMode::NEXT_FRAME)
                tcp.println("play option: stop mode: nextframe");
            else if (mode == StopMode::BLACK_SCREEN)
                tcp.println("play option: stop mode: black");
        }

        void record() {
            tcp.println("record");
        }

        void record(const String& name) {
            tcp.println("record:name:" + name);
        }

        void record_spill() {
            tcp.println("record spill");
        }

        void record_spill(const size_t slot_id) {
            tcp.println("record spill: slot id: " + String(slot_id));
        }

        void stop() {
            tcp.println("stop");
        }

        void clips_count() {}  // TODO: query

        void clips_get() {}  // TODO: query

        void clips_get(const size_t clip_id) {}  // TODO: query

        void clips_get(const size_t clip_id, const size_t count) {}  // TODO: query

        void clips_get_version(const size_t version) {}  // TODO: query

        void clips_add(const String& name) {
            tcp.println("clips add: name: " + name);
        }

        void clips_add(const size_t clip_id, const String& name) {
            tcp.println("clips add: clip id: " + String(clip_id) + " name: " + name);
        }

        void clips_add(const String& tc_in, const String& tc_out, const String& name) {
            tcp.println("clips add: in: " + tc_in + " out: " + tc_out + " name: " + name);
        }

        void clips_remove(const size_t clip_id) {
            tcp.println("clips remove: clip id: " + String(clip_id));
        }

        void clips_clear() {
            tcp.println("clips clear");
        }

        void transport_info() {}  // TODO: query

        void slot_info() {}  // TODO: query

        void slot_info(const size_t slot_id) {}  // TODO: query

        void slot_select(const size_t slot_id) {
            tcp.println("slot select: slot id: " + String(slot_id));
        }

        void slot_select() {}  // TODO:

        void slot_unblock() {
            tcp.println("slot unclock");
        }

        void slot_unblock(const size_t slot_id) {
            tcp.println("slot unclock: slot id: " + String(slot_id));
        }

        void dynamic_range() {}  // TODO: query

        void notify() {}  // TODO: query

        void notify_remote(const bool b) {
            if (b)
                tcp.println("notify: remote: true");
            else
                tcp.println("notify: remote: false");
        }

        void notify_transport(const bool b) {
            if (b)
                tcp.println("notify: transport: true");
            else
                tcp.println("notify: transport: false");
        }

        void notify_slot(const bool b) {
            if (b)
                tcp.println("notify: slot: true");
            else
                tcp.println("notify: slot: false");
        }

        void notify_configuration(const bool b) {
            if (b)
                tcp.println("notify: configuration: true");
            else
                tcp.println("notify: configuration: false");
        }

        void notify_drop_frames(const bool b) {
            if (b)
                tcp.println("notify: dropped frames: true");
            else
                tcp.println("notify: dropped frames: false");
        }

        void notify_display_timecode(const bool b) {
            if (b)
                tcp.println("notify: display timecode: true");
            else
                tcp.println("notify: display timecode: false");
        }

        void notify_timeline_position(const bool b) {
            if (b)
                tcp.println("notify: timeline position: true");
            else
                tcp.println("notify: timeline position: false");
        }

        void notify_playrange(const bool b) {
            if (b)
                tcp.println("notify: playrange: true");
            else
                tcp.println("notify: playrange: false");
        }

        void notify_dynamic_range(const bool b) {
            if (b)
                tcp.println("notify: dynamic range: true");
            else
                tcp.println("notify: dynamic range: false");
        }

        void goto_clip_start() {
            tcp.println("goto: clip id: start");
        }

        void goto_clip_end() {
            tcp.println("goto: clip id: end");
        }

        void goto_clip(const size_t n) {
            tcp.println("goto: clip id: " + String(n));
        }

        void goto_clip_forward(const size_t n) {
            tcp.println("goto: clip id: +" + String(n));
        }

        void goto_clip_backward(const size_t n) {
            tcp.println("goto: clip id: -" + String(n));
        }

        void goto_timeline_start() {
            tcp.println("goto: timeline: start");
        }

        void goto_timeline_end() {
            tcp.println("goto: timeline: end");
        }

        void goto_timeline(const size_t n) {
            tcp.println("goto: timeline: " + String(n));
        }

        void goto_timeline_forward(const size_t n) {
            tcp.println("goto: timeline: +" + String(n));
        }

        void goto_timeline_backward(const size_t n) {
            tcp.println("goto: timeline: -" + String(n));
        }

        void goto_timecode(const String& tc) {
            tcp.println("goto: timecode: " + tc);
        }

        void goto_timecode_forward(const String& tc) {
            tcp.println("goto: timecode: +" + tc);
        }

        void goto_timecode_backward(const String& tc) {
            tcp.println("goto: timecode: -" + tc);
        }

        void goto_slot(const size_t slot_id) {
            tcp.println("goto: slot id: " + String(slot_id));
        }

        void jog_timecode(const String& tc) {
            tcp.println("jog: timecode: " + tc);
        }

        void jog_timecode_forward(const String& tc) {
            tcp.println("jog: timecode: +" + tc);
        }

        void jog_timecode_backward(const String& tc) {
            tcp.println("jog: timecode: -" + tc);
        }

        void shuttle(const int speed) {
            if ((speed >= -1600) && (speed <= 1600)) {
                tcp.println("shuttle: speed: " + String(speed));
            } else {
                Serial.println("shuttle speed must be from -1600 to 1600");
            }
        }

        void remote() {}  // TODO: query

        void remote(const bool b) {
            if (b)
                tcp.println("remote: enable: true");
            else
                tcp.println("remote: enable: false");
        }

        void remote_override(const bool b) {
            if (b)
                tcp.println("remote: override: true");
            else
                tcp.println("remote: override: false");
        }

        void configuration() {}  // TODO: query

        void config_video_input(const VideoInput v_in) {
            switch (v_in) {
                case VideoInput::SDI:
                    tcp.println("configuration: video input: SDI");
                    break;
                case VideoInput::HDMI:
                    tcp.println("configuration: video input: HDMI");
                    break;
                case VideoInput::COMPONENT:
                    tcp.println("configuration: video input: component");
                    break;
            }
        }

        void config_audio_input(const AudioInput a_in) {
            switch (a_in) {
                case AudioInput::EMBEDDED:
                    tcp.println("configuration: audio input: embedded");
                    break;
                case AudioInput::XLR:
                    tcp.println("configuration: audio input: XLR");
                    break;
                case AudioInput::RCA:
                    tcp.println("configuration: audio input: RCA");
                    break;
            }
        }

        void config_file_format() {}  // TODO:

        void config_audio_codec(const AudioCodec codec) {
            switch (codec) {
                case AudioCodec::PCM:
                    tcp.println("configuration: audio codec: PCM");
                    break;
                case AudioCodec::AAC:
                    tcp.println("configuration: audio codec: AAC");
                    break;
            }
        }

        void config_timecode_input(const TimecodeInput t_in) {
            switch (t_in) {
                case TimecodeInput::EXT:
                    tcp.println("configuration: timecode input: external");
                    break;
                case TimecodeInput::EMBEDDED:
                    tcp.println("configuration: timecode input: embedded");
                    break;
                case TimecodeInput::PRESET:
                    tcp.println("configuration: timecode input: preset");
                    break;
                case TimecodeInput::CLIP:
                    tcp.println("configuration: timecode input: clip");
                    break;
            }
        }

        void config_timecode_preset(const String& tc) {
            tcp.println("configuration: timecode preset: " + tc);
        }

        void config_audio_input_channels(const size_t ch) {
            tcp.println("configuration: audio input channels: " + String(ch));
        }

        void config_record_trigger(const RecordTrigger trig) {
            switch (trig) {
                case RecordTrigger::NONE:
                    tcp.println("configuration: record trigger: none");
                    break;
                case RecordTrigger::RECORDBIT:
                    tcp.println("configuration: record trigger: recordbit");
                    break;
                case RecordTrigger::TIMECODERUN:
                    tcp.println("configuration: record trigger: timecoderun");
                    break;
            }
        }

        void config_record_prefix(const String& name) {
            tcp.println("configuration: record prefix: " + name);
        }

        void config_append_timestamp(const bool b) {
            if (b)
                tcp.println("configuration: append timestamp: true");
            else
                tcp.println("configuration: append timestamp: false");
        }

        void uptiem() {}  // TODO: query

        void format_prepare() {}  // TODO:

        void format_confirm() {}  // TODO:

        void identify(const bool b) {
            if (b)
                tcp.println("identify: enable: true");
            else
                tcp.println("identify: enable: false");
        }

        void watchdog_period(const size_t sec) {
            tcp.println("watchdog: period: " + String(sec));
        }
    };

}  // namespace hyperdeck
}  // namespace arx

namespace HyperDeck = arx::hyperdeck;

#endif  // ARDUINO_HYPERDECK_H
