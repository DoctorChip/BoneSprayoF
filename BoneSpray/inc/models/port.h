#pragma once

enum NOTE_EVENT { ON, OFF };

typedef struct {
	NOTE_EVENT evt;
	int note;
	int velocity;
} midi_port_event;

typedef struct {

} audio_port_event;

class audio_port
{
public:
	
	const char* name;
	int index;
	audio_port_event **buffer;

private:


};

class midi_port
{
public:
	
	const char* name;
	int index;
	midi_port_event **buffer;

private:


};
