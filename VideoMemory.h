#ifndef VIDEOMEMORY_H
#define VIDEOMEMORY_H

#include <stdint.h>
#include <stdlib.h>

class VideoMemory {
	public:
		VideoMemory();		
		~VideoMemory();		

	private:
		uint8_t *video_bytes;

};

#endif
