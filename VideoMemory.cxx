#include "VideoMemory.h"

VideoMemory::VideoMemory() {
	video_bytes = (uint8_t*) malloc(65536 * sizeof(uint8_t)); 
}

VideoMemory::~VideoMemory() {
	free(video_bytes);
}
