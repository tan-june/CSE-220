#include "wolfpack.h"

unsigned char packet[] =         "\x38\x91\x8a\x27\x31\x1e\x82\xca\xb0\x29\x20\x40\x00\x00\x18\x03\x1f\x00\x00\x24\x14\x54\xdb\x6c\x69\x74\x65\x20\x65\x72\x72\x6f\x72\x2d\x66\x72";

int main() {
    print_packet_sf(packet);
}