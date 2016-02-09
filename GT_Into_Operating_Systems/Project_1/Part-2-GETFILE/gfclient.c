#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h> 
#include <netinet/in.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netdb.h>

#include "gfclient.h"


gfcrequest_t *gfc_create(){

}

void gfc_set_server(gfcrequest_t *gfr, char* server){
  
}

void gfc_set_path(gfcrequest_t *gfr, char* path){
  
}

void gfc_set_port(gfcrequest_t *gfr, unsigned short port){
  
}

void gfc_set_headerfunc(gfcrequest_t *gfr, void (*headerfunc)(void*, size_t, void *)){
  
}

void gfc_set_headerarg(gfcrequest_t *gfr, void *headerarg){
  
}

void gfc_set_writefunc(gfcrequest_t *gfr, void (*writefunc)(void*, size_t, void *)){
  
}

void gfc_set_writearg(gfcrequest_t *gfr, void *writearg){
  
}

int gfc_perform(gfcrequest_t *gfr){
  
}

gfstatus_t gfc_get_status(gfcrequest_t *gfr){

}

char* gfc_strstatus(gfstatus_t status){

}

size_t gfc_get_filelen(gfcrequest_t *gfr){

}

size_t gfc_get_bytesreceived(gfcrequest_t *gfr){

}

void gfc_cleanup(gfcrequest_t *gfr){

}

void gfc_global_init(){
}

void gfc_global_cleanup(){
}
