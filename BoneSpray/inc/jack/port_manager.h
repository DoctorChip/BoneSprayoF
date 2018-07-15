#pragma once

#include "jack/types.h"
#include "jack/ringbuffer.h"

#define MAX_MIDI_COUNT 64
#define RBSIZE 512

#ifndef MAX
#define MAX(a,b) ( (a) < (b) ? (b) : (a) )
#endif

static class port_manager
{

public:

	void activate();
	void create_midi_array(int count);
	void close();

private:
	
	int process(jack_nframes_t nframes, void* arg);
	void shutdown(void* arg);

	jack_port_t *in_port;
	int midi_port_count;
	jack_port_t **midi_ports;
	jack_client_t *client;
	jack_ringbuffer_t *rb = NULL;
	uint64_t monotonic_cnt = 0;

	typedef struct {
		uint8_t  buffer[128];
		uint32_t size;
		uint32_t tme_rel;
		uint64_t tme_mon;
	} midimsg;
};