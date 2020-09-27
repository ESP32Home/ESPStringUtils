#include <Arduino.h>

#include "esp_mesh.h"

void string_to_char_len(String str,uint8_t* text,uint16_t &length);
void string_to_char_len(String str,uint8_t* text,uint8_t &length);
void string_to_char(String str,uint8_t* text);

void string_to_hextab(const String &str,mesh_addr_t &t);
void string_to_hextab(const String &str,uint8_t *t);
String hextab_to_string(uint8_t* add);

void string_to_ip_port(String str,mesh_addr_t &add);
void ip_port_to_string(mesh_addr_t add,String &str);

void print_mac(uint8_t* add);
void print_ip(ip4_addr_t add);
