#include <string>
#include <iostream>
#include "jack/jack.h"
#include "jack/types.h"
#include "jack/ringbuffer.h"
#include "jack/midiport.h"
#include "jack/jack_interface.h"

#define MAX_MIDI_COUNT 64
#define RBSIZE 512

#ifndef MAX
#define MAX(a,b) ( (a) < (b) ? (b) : (a) )
#endif

namespace jack 
{
	typedef struct {
		uint8_t  buffer[128];
		uint32_t size;
		uint32_t tme_rel;
		uint64_t tme_mon;
	} midimsg;

	jack_port_t *in_port;
	jack_port_t *midi_ports;
	jack_port_t *midi_ports_out;
	jack_client_t *client;
	jack_ringbuffer_t *rb = NULL;
	uint64_t monotonic_cnt = 0;

	/*
	 *	Callback process for JACK events - handles the audio data incoming
	 */
	int process(jack_nframes_t nframes, void *arg)
	{
		jack_default_audio_sample_t *buffer;
		jack_nframes_t N;
		jack_nframes_t i;

		// Audio
		buffer = (jack_default_audio_sample_t *) jack_port_get_buffer(in_port, nframes);

		// Midi
		N = jack_midi_get_event_count(buffer);
		for (i = 0; i < N; ++i) {

			jack_midi_event_t event;
			int r;
			r = jack_midi_event_get(&event, buffer, i);

			if (r == 0 && jack_ringbuffer_write_space(rb) >= sizeof(midimsg)) {
				midimsg m;
				m.tme_mon = monotonic_cnt;
				m.tme_rel = event.time;
				m.size = event.size;
				memcpy(m.buffer, event.buffer, MAX(sizeof(m.buffer), event.size));
				jack_ringbuffer_write(rb, (const char*)&m, sizeof(midimsg));

				size_t j;
				for (j = 0; j < m.size && j < sizeof(m.buffer); ++j) {
					printf(" %02x", m.buffer[j]);
				}
			}
		}

		monotonic_cnt += nframes;

		//std::cout << *buffer << std::endl;
		return 0;
	}

	/*
	 *	Callback process for JACK closing
	 */
	void shutdown(void *arg)
	{
		exit(1);
	}

	/*
	 *	Setup process for JACK. Launch the server, open the channel, etc.
	 */
	void activate()
	{
		const char *CLIENT_NAME = "BS";
		const char *IN_NAME = "IN_0";
		jack_status_t *STATUS = {};

		rb = jack_ringbuffer_create(RBSIZE * sizeof(midimsg));
		client = jack_client_open(CLIENT_NAME, JackNullOption, STATUS);
		in_port = jack_port_register(client, IN_NAME, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

		jack_nframes_t nframes = jack_get_buffer_size(client);

		jack_set_process_callback(client, process, 0);
		jack_on_shutdown(client, shutdown, 0);

		int activate = jack_activate(client);
	}

	/*
	 *	Creates an array of MIDI channels, length of `count`.
	 */
	void create_midi_array(int count)
	{
		if (count > MAX_MIDI_COUNT)
		{
			return;
		}

		jack_port_t *ports[MAX_MIDI_COUNT];
		for (int i = 0; i < MAX_MIDI_COUNT; i++) ports[i] = NULL;
		midi_ports = *ports;

		jack_port_t *ports_out[MAX_MIDI_COUNT];
		for (int i = 0; i < MAX_MIDI_COUNT; i++) ports_out[i] = NULL;
		midi_ports_out = *ports_out;

		for (int i = 0; i < count; i++)
		{
			std::string name = "MIDI_" + std::to_string(i);
			std::string name_out = "MIDI_OUT_" + std::to_string(i);
			jack_port_t *midi = jack_port_register(client, name.c_str(), JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
			jack_port_t *midi_out = jack_port_register(client, name_out.c_str(), JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
			ports[i] = midi;
			ports_out[i] = midi_out;
		}
	}

	/*
	 *	Close the JACK server before exiting the app.
	 */
	void close()
	{
		jack_client_close(client);
		exit(0);
	}
}
