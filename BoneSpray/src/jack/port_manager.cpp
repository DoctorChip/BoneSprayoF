#include <string>
#include <iostream>
#include "jack/jack.h"
#include "jack/types.h"
#include "jack/ringbuffer.h"
#include "jack/midiport.h"
#include "jack/port_manager.h"

port_manager* port_manager::obj;

/*
 *	Callback process for JACK events - handles the audio data incoming
 */
int port_manager::process(jack_nframes_t nframes, void *arg)
{
	jack_default_audio_sample_t *audio_buffer;
	jack_default_audio_sample_t *midi_buffer;
	jack_nframes_t N;
	jack_nframes_t i;
	int c;
	int port_i;

	// Audio
	audio_buffer = (jack_default_audio_sample_t *) jack_port_get_buffer(in_port, nframes);

	// Midi
	for (c = 0; c < midi_port_count; c++)
	{
		jack_port_t* port = internal_midi_ports[c];
		midi_buffer = (jack_default_audio_sample_t *) jack_port_get_buffer(port, nframes);
		
		N = jack_midi_get_event_count(midi_buffer);
		for (i = 0; i < N; ++i) {

			midi_port ext_port;
			ext_port = midi_ports[c];

			jack_midi_event_t event;
			int r;
			r = jack_midi_event_get(&event, midi_buffer, i);

			if (r == 0 && jack_ringbuffer_write_space(rb) >= sizeof(midimsg)) {
				midimsg m;
				m.tme_mon = monotonic_cnt;
				m.tme_rel = event.time;
				m.size = event.size;
				memcpy(m.buffer, event.buffer, MAX(sizeof(m.buffer), event.size));
				jack_ringbuffer_write(rb, (const char*)&m, sizeof(midimsg));

				size_t j;

				midi_port_event evt;

				if (m.buffer[0] == 0x90) {
					evt.evt = ON;
				}
				else {
					evt.evt = OFF;
				}

				evt.note = m.buffer[1];
				evt.velocity = m.buffer[2];

				// Add event to our port's buffer
				ext_port.add_event(evt);
				midi_ports[c] = ext_port;
			}
		}
	}

	monotonic_cnt += nframes;

	// Add audio event to buffer
	audio_port_event evt;
	evt.buffer = audio_buffer;
	audio_port ext_audio_port;
	ext_audio_port = audio_ports[0];
	ext_audio_port.add_event(evt);
	
	return 0;
}

/*
 *	Callback process for JACK closing
 */
void port_manager::shutdown(void *arg)
{
	exit(1);
}

/*
 *	Setup process for JACK. Launch the server, open the channel, etc.
 */
void port_manager::activate()
{
	const char *CLIENT_NAME = "BS";
	const char *IN_NAME = "IN_0";
	jack_status_t *STATUS = {};

	rb = jack_ringbuffer_create(RBSIZE * sizeof(midimsg));
	client = jack_client_open(CLIENT_NAME, JackNullOption, STATUS);
	monotonic_cnt = 0;

	//Audio
	in_port = jack_port_register(client, IN_NAME, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
	
	audio_port audio;
	audio.name = IN_NAME;
	audio.index = 0;
	audio_ports[0] = audio;

	jack_nframes_t nframes = jack_get_buffer_size(client);

	port_manager::obj = this;
	jack_set_process_callback(client, &processCallback, 0);
	jack_on_shutdown(client, &shutdownCallback, 0);

	int activate = jack_activate(client);
}


/*
 *	Creates an array of MIDI channels, length of `count`.
 */
void port_manager::create_midi_array(int count)
{
	if (count > MAX_MIDI_COUNT) return;

	midi_port_count = count;
	internal_midi_ports = new jack_port_t*[MAX_MIDI_COUNT];

	for (int i = 0; i < count; i++)
	{
		std::string name ( "MIDI_" + std::to_string(i));
		jack_port_t *midi = jack_port_register(client, name.c_str(), JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
		internal_midi_ports[i] = midi;

		midi_port ext_port;
		ext_port.name = name.c_str();
		ext_port.index = i;
		midi_ports[i] = ext_port;
	}
}

port_manager::audio_port* port_manager::find_audio_port(int index)
{
	return &audio_ports[index];
}

port_manager::midi_port* port_manager::find_midi_port(int index)
{
	return &midi_ports[index];
}

/*
 *	Close the JACK server before exiting the app.
 */
void port_manager::close()
{
	jack_client_close(client);
	exit(0);
}