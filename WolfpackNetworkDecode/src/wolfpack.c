#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>

//#include "wolfpack.h"

void print_packet_sf(const unsigned char * packet) {
  printf("%02x%02x%02x%02x%02x\n", packet[0], packet[1], packet[2], packet[3], packet[4]);
  printf("%02x%02x%02x%02x%02x\n", packet[5], packet[6], packet[7], packet[8], packet[9]);
  printf("%02x\n", packet[10]);
  printf("%02x\n", packet[11]);
  printf("%02x%02x%02x\n", packet[12], packet[13], packet[14]);
  printf("%02x%02x\n", packet[15], packet[16]);
  printf("%02x%02x%02x\n", packet[17], packet[18], packet[19]);
  printf("%02x%02x%02x%02x\n", packet[20], packet[21], packet[22], packet[23]);
  unsigned int length = (packet[17] << 16) | (packet[18] << 8) | packet[19];
  for (unsigned int i = 24; i < length; i++) {
    printf("%c", packet[i]);
  }
  printf("\n");

}

unsigned int checksum_sf(const unsigned char * packet) {

  unsigned long long source, destination, destinationPort, sourcePort, flags, fragmentOffset, lengthTotal = 0;
  unsigned long long sum = 0x0;

  source = 0;
  source |= ((long) packet[0]) << (32);
  source |= ((long) packet[1]) << (24);
  source |= ((long) packet[2]) << (16);
  source |= ((long) packet[3]) << (8);
  source |= ((long) packet[4]) << (0);
  //printf("The source is: %lx\n", source);

  destination = 0;
  destination |= ((long) packet[5]) << (32);
  destination |= ((long) packet[6]) << (24);
  destination |= ((long) packet[7]) << (16);
  destination |= ((long) packet[8]) << (8);
  destination |= ((long) packet[9]) << (0);
  //printf("The destination is: %lx\n", destination);

  sourcePort = packet[10];
  //printf("The sourcePort is: %lx\n", sourcePort);

  destinationPort = packet[11];
  //printf("The destinationPort is: %lx\n", destinationPort);

  fragmentOffset = (packet[14] | (packet[13] << 8) | (packet[12] << 16));
  //printf("The fragmentOffset is: %lx\n", fragmentOffset);

  flags = (packet[16] | (packet[15] << 8));
  //printf("The flags is: %lx\n", flags);

  lengthTotal = (packet[19] | (packet[18] << 8) | (packet[17] << 16));
  //printf("The lengthTotal is: %lx\n", lengthTotal);

  //printf("The sum is: %llx\n", sum);
  // sum = source;
  sum = source + destination + flags + destinationPort + sourcePort + fragmentOffset + lengthTotal;
  //destinationPort + sourcePort + lengthTotal + fragmentOffset;
  //printf("The sum is: %llx\n", sum);
  unsigned long value = (unsigned int)((sum) % ((long) pow(2, 32) - 1));
  //printf("modolo: %lx\n", value);
  return value;
}
unsigned int reconstruct_sf(unsigned char * packets[], unsigned int packets_len, char * message, unsigned int message_len) {
  unsigned long fragment_offset = 0;
  long payload_size = 0;
  unsigned long checksum = 0;
  unsigned long computed_checksum = 0;
  unsigned char * packet;
  int payloadwritten = 0;
  unsigned int maxfrag = 0;

  for (unsigned int i = 0; i < packets_len; i++) {

    packet = packets[i];
    fragment_offset = ((int) packet[12] << 16) | ((int) packet[13] << 8) | (int) packet[14];
    computed_checksum = checksum_sf(packet);
    checksum = packet[23] | (packet[22] << 8) | (packet[21] << 16) | (packet[20] << 24);
    unsigned int length = (packet[17] << 16) | (packet[18] << 8) | packet[19];
    payload_size = length - 24;

    //Checking Prints
    //printf("Packet: %x\n", packet);
    //printf("Offset:             %ld\n", fragment_offset);
    //printf("Computed Checksum = %lx\n", computed_checksum);
    //printf("Actual Checksum =   %lx\n", checksum);
    //for (int i = 24; i < length; i++) {
    //printf("%c", packet[i]);
    //}
    //printf("\nPayload Size: %ld\n", payload_size);
    //printf("\n\n");
    //printf("message len %d\n", message_len);

    if (computed_checksum != checksum) {
      continue;
    }
    if (maxfrag < fragment_offset) {
      maxfrag = fragment_offset + payload_size;
    }
    if (fragment_offset + payload_size <= message_len - 1) {
      for (int j = 0; j < payload_size; j++) {
        message[fragment_offset + j] = packet[24 + j];
      }
      payloadwritten++;
    } else if (fragment_offset + payload_size > message_len - 1) {
      payload_size = message_len - fragment_offset - 1;
      if (payload_size > 0) {
        payloadwritten++;
        for (int j = 0; j < payload_size; j++) {
          message[fragment_offset + j] = packet[24 + j];
        }
      }

      maxfrag = message_len - 1;
    }

  }
  message[maxfrag] = '\0';
  return payloadwritten;

}

unsigned int packetize_sf(const char * message, unsigned char * packets[], unsigned int packets_len, unsigned int max_payload,
  unsigned long src_addr, unsigned long dest_addr, unsigned short flags) {

  unsigned int payload_size = max_payload;
  unsigned int message_length = 0;
  while (message[message_length] != '\0') {
        message_length++;
  }
  //printf("Message Length: %d\n", message_length);
  
  unsigned int number_packets = (message_length + max_payload - 1) / max_payload;
  //printf("Number of Packets Need:  %d\n", number_packets);

  if (number_packets > packets_len) {
      number_packets = packets_len;
  }

  unsigned long source_add = src_addr;
  unsigned long first_source_add = (source_add >> 32) & 0xff;
  unsigned long second_source_add = (source_add >> 24) & 0xff;
  unsigned long third_source_add = (source_add >> 16) & 0xff;
  unsigned long fourth_source_add = (source_add >> 8) & 0xff;
  unsigned long fifth_source_add = source_add & 0xff;

  //printf("Source Add in Bits:      %02lx %02lx %02lx %02lx %02lx\n", first_source_add, second_source_add, third_source_add, fourth_source_add, fifth_source_add);

  unsigned long destination_add = dest_addr;
  unsigned long first_destination_add = (destination_add >> 32) & 0xff;
  unsigned long second_destination_add = (destination_add >> 24) & 0xff;
  unsigned long third_destination_add = (destination_add >> 16) & 0xff;
  unsigned long fourth_destination_add = (destination_add >> 8) & 0xff;
  unsigned long fifth_destination_add = destination_add & 0xff;

  //printf("Destination Add in Bits: %02lx %02lx %02lx %02lx %02lx\n", first_destination_add, second_destination_add, third_destination_add, fourth_destination_add, fifth_destination_add);
  
  unsigned long source_port = 32;
  //printf("Source_Port:             %02lx\n", source_port);
  unsigned long destination_port = 64;
  //printf("Destination_port:        %02lx\n", destination_port);
  
  unsigned long flag = flags;
  unsigned long first_flag = (flag >> 8) & 0xFF;
  unsigned long last_flag = flag & 0xFF;

  //printf("Flags:                   %02lx %02lx\n", first_flag,last_flag);


  unsigned long checksum = 0;
  unsigned long packetIndex = 0;
  


  for (unsigned int i = 0; i < number_packets; i++) {
    packets[i] = malloc(24+max_payload);
    //known standard values
    packets[i][0] = first_source_add;
    packets[i][1] = second_source_add; 
    packets[i][2] = third_source_add;
    packets[i][3] = fourth_source_add;
    packets[i][4] = fifth_source_add;
    packets[i][5] = first_destination_add;
    packets[i][6] = second_destination_add;
    packets[i][7] = third_destination_add;
    packets[i][8] = fourth_destination_add;
    packets[i][9] = fifth_destination_add;
    packets[i][10] = source_port;
    packets[i][11] = destination_port;  
    packets[i][15] = first_flag;
    packets[i][16] = last_flag;

    unsigned int payload_start = i * payload_size;
    unsigned int payload_end = payload_start + payload_size;
    
    if (payload_end > message_length) {
      payload_end = message_length;
    }
    
    unsigned int payload_len = payload_end - payload_start;
    unsigned int total_len = payload_len + 24;

    //fragment offset
    unsigned int payload_offset_calc = i*payload_size;
    packets[i][12] = (payload_offset_calc >> 16) & 0xFFF;
    packets[i][13] = (payload_offset_calc >> 8) & 0xFFF;
    packets[i][14] = (payload_offset_calc) & 0xFFF;
  
    //assigning length
    packets[i][17] = (total_len >> 16) & 0xFFFF;
    packets[i][18] = (total_len >> 8) & 0xFFFF;
    packets[i][19] = total_len & 0xFFFF;

    //checksum
    checksum = source_add + destination_add + payload_offset_calc + total_len + flags + destination_port + source_port;
    unsigned long value = (unsigned int)((checksum) % ((long) pow(2, 32) - 1));
    //printf("Checksum Print: %lx\n\n\n", value);
    packets[i][20] = (value >> 24) & 0xFF;
    packets[i][21] = (value >> 16) & 0xFF;
    packets[i][22] = (value >> 8) & 0xFF;
    packets[i][23] = value & 0xFF;

      
      for (unsigned int j = 0; j < payload_len; j++) {
          packets[i][j + 24] = message[payload_start + j];
        }

    packetIndex++;
  }


return packetIndex;
}



