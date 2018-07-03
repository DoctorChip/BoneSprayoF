#include "jack/jack.h"
#include "jack/types.h"
#include "jack/jack_interface.h"

namespace jack 
{
	jack_port_t *in_port;
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
		const char *IN_NAME = "BSIn1";
		jack_status_t *STATUS = {};

		client = jack_client_open(CLIENT_NAME, JackNullOption, STATUS);
		in_port = jack_port_register(client, IN_NAME, JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

		jack_nframes_t nframes = jack_get_buffer_size(client);

		jack_set_process_callback(client, process, 0);
		jack_on_shutdown(client, shutdown, 0);

		int activate = jack_activate(client);
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
