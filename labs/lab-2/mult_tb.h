
#include "systemc.h"

SC_MODULE(MultTb){

  sc_in<bool>  clk;
  sc_out<int>  din1;
  sc_out<int>  din2;
  sc_in <int>  dout;

  void stim_gen();
  void check();

  SC_CTOR(MultTb){
   SC_THREAD(stim_gen);
   sensitive << clk.pos();
  }

};

void MultTb::stim_gen(){
  wait();
  din1 = 10;
  din2 = 10;
  wait();
  printf("[MON]:: %0d * %0d = %0d\n", din1.read(), din2.read(), dout.read());
  check();
  din1 = -10;
  din2 = 10;
  wait();
  printf("[MON]:: %0d * %0d = %0d\n", din1.read(), din2.read(), dout.read());
  check();

  sc_stop(); 
}

void MultTb::check() {
  if(dout.read() != din1.read()*din2.read())
    printf("ERROR, validation failed.\n");
  else
    printf("Verification successful.\n");
}
