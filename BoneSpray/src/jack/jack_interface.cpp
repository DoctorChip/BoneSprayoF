#include <string>
#include <iostream>
#include "jack/jack.h"
#include "jack/types.h"
#include "jack/jack_interface.h"

#define MAX_MIDI_COUNT 64

namespace jack 
{
	jack_port_t *in_port;
	jack_port_t *midi_ports;
	jack_client_t *client;

	/*
	 *	Callback process for JACK events - handles the audio data incoming
	 */
	int process(jack_nframes_t nframes, void *arg)
	{
		jack_default_audio_sample_t *audio_in;
		audio_in = (jack_default_audio_sample_t *) jack_port_get_buffer(in_port, nframes);
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

		for (int i = 0; i < count; i++)
		{
			std::string name = "MIDI_" + std::to_string(i);
			jack_port_t *midi = jack_port_register(client, name.c_str(), JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
			ports[i] = midi;
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
