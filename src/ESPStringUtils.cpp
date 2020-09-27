#include "ESPStringUtils.h"

#include "esp_now.h"

void string_to_char_len(String str,uint8_t* text,uint16_t &length){
    length = str.length();
    memcpy(text, str.c_str(), length);
    text[length] = '\0';//clean ending for printing
}

void string_to_char_len(String str,uint8_t* text,uint8_t &length){
    length = str.length();
    memcpy(text, str.c_str(), length);
    text[length] = '\0';//clean ending for printing
}

void string_to_char(String str,uint8_t* text){
    memcpy(text, str.c_str(), str.length());
    text[str.length()] = '\0';
}

void string_to_hextab(const String &str,uint8_t *add_tab){
    int start = -1;
    int end;
    int before_last = ESP_NOW_ETH_ALEN-1;
    for(int i=0;i<before_last;i++){
        end = str.indexOf(':',start+1);
        String hex = str.substring(start+1,end);
        (*add_tab++) = (uint8_t)strtol(hex.c_str(), NULL, 16);
        start = end;
    }
    end = str.indexOf(':',start+1);
    String hex = str.substring(start+1);
    (*add_tab) = (uint8_t)strtol(hex.c_str(), NULL, 16);
}

void string_to_hextab(const String &str,mesh_addr_t &t){
    string_to_hextab(str,t.addr);
}

String hextab_to_string(uint8_t* add){
    String res;
    char hex_text[4];
    for(int i=0;i<5;i++){
        sprintf(hex_text,"%02x:",(*add++));
        res = res + String(hex_text);
    }
    sprintf(hex_text,"%02x",(*add));
    res = res + String(hex_text);
    return res;
}

void string_to_ip_port(String str,mesh_addr_t &add){
    int tp = str.indexOf(':');
    int p1 = str.indexOf('.');
    int p2 = str.indexOf('.',p1+1);
    int p3 = str.indexOf('.',p2+1);
    //Serial.printf("tp:%d p1,2,3:%d,%d,%d\n",tp,p1,p2,p3);

    uint16_t port = str.substring(tp+1).toInt();
    uint32_t ip1 = str.substring(0,p1).toInt();
    uint32_t ip2 = str.substring(p1+1,p2).toInt();
    uint32_t ip3 = str.substring(p2+1,p3).toInt();
    uint32_t ip4 = str.substring(p3+1,tp).toInt();
    //Serial.printf("port:%d ip1,2,3,4:%d,%d,%d,%d\n",port,ip1,ip2,ip3,ip4);

    add.mip.port = port;
    add.mip.ip4.addr = (ip1<<24) | (ip2<<16) | (ip3<<8) | (ip4);
    //Serial.printf("ip hex 0x%02x\n",add.mip.ip4.addr);
}

void ip_port_to_string(mesh_addr_t add,String &str){
    uint8_t u1 = (add.mip.ip4.addr>>24) & 0xff;
    uint8_t u2 = (add.mip.ip4.addr>>16) & 0xff;
    uint8_t u3 = (add.mip.ip4.addr>>8) & 0xff;
    uint8_t u4 =  add.mip.ip4.addr & 0xff;
    str = String(u1)+"."+String(u2)+"."+String(u3)+"."+String(u4)+":"+String(add.mip.port);
}

void print_mac(uint8_t* add){
    for(int i=0;i<5;i++){
        Serial.printf("%02X:",(*add++));
    }
    Serial.printf("%02X\n",(*add));
}

void print_ip(ip4_addr_t add){
    uint8_t u1 = (add.addr>>3) & 0xff;
    uint8_t u2 = (add.addr>>2) & 0xff;
    uint8_t u3 = (add.addr>>1) & 0xff;
    uint8_t u4 = add.addr & 0xff;
    Serial.printf("%d.%d.%d.%d\n",u1,u2,u3,u4);
}
