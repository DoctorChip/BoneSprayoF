#pragma once

#include "jack/types.h"
#include "jack/ringbuffer.h"
#include "models/port.h"

#define MAX_MIDI_COUNT 64
#define RBSIZE 512

#ifndef MAX
#define MAX(a,b) ( (a) < (b) ? (b) : (a) )
#endif

static class port_manager
{

public:
	
	enum NOTE_EVENT { ON, OFF };

	typedef struct {
		NOTE_EVENT evt;
		int note;
		int velocity;
	} midi_port_event;

	typedef struct {
		jack_default_audio_sample_t *buffer;
	} audio_port_event;

	typedef struct {
		std::string name;
		int index;
		audio_port_event buffer;
		void add_event(audio_port_event evt) {
			buffer = evt;
		};
	} audio_port;

	typedef struct {
		std::string name;
		int index;
		midi_port_event buffer;
		void add_event(midi_port_event evt) {
			buffer = evt;
		};
	} midi_port;

	void activate();
	void create_midi_array(int count);
	int process(jack_nframes_t nframes, void* arg);
	void shutdown(void* arg);
	audio_port* find_audio_port(int index);
	midi_port* find_midi_port(int index);
	void close();

	static port_manager* obj;
	static int processCallback(jack_nframes_t nframes, void *arg) {
		return obj->process(nframes, arg);
	};

	static void shutdownCallback(void *arg) {
		obj->shutdown(arg);
	};


private:
	
	jack_port_t *in_port;
	int midi_port_count;
	jack_port_t **internal_midi_ports;
	jack_client_t *client;
	jack_ringbuffer_t *rb;
	uint64_t monotonic_cnt;

	// Our ports
	audio_port audio_ports[1];
	midi_port midi_ports[MAX_MIDI_COUNT];


	typedef struct {
		uint8_t  buffer[128];
		uint32_t size;
		uint32_t tme_rel;
		uint64_t tme_mon;
	} midimsg;
};